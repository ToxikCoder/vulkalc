/*
* The MIT License (MIT)
*
* Copyright (c) 2017 Lev Sizov
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

/*!
 * \file Application.cpp
 * \brief Contains Application class implementation
 * \author Lev Sizov
 * \date 28.05.2017
 */

#include "include/Application.hpp"

using namespace Vulkalc;

void Application::init()
{
    if (m_isInitialized)
        return;

    m_isInitialized = true;
	m_isLoggingEnabled = false;
	m_isErrorLoggingEnabled = false;
    m_spConfigurator = std::make_shared<Configurator>();
    m_spErrorStream = nullptr;
    m_spLogStream = nullptr;
    m_spVkApplicationInfo = nullptr;
    m_spVkInstanceCreateInfo = nullptr;
}

void Application::configure(bool reconfigure) throw(ApplicationNotInitializedException, HostMemoryAllocationException)
{
    if (!m_isInitialized)
        throw ApplicationNotInitializedException();

    //allowing reconfiguring only if reconfigure flag is true
    if(!reconfigure && m_isConfigured)
        return;

    configure();
}

void Application::configure() throw(HostMemoryAllocationException)
{
    m_isConfigured = true;
    auto configuration = m_spConfigurator->getConfiguration();
    m_spLogStream = configuration->logStream;
    m_spErrorStream = configuration->errorStream;
    m_isLoggingEnabled = configuration->isLoggingEnabled;
    m_isErrorLoggingEnabled = configuration->isErrorLoggingEnabled;

    //filling in VkApplicationInfo
    prepareVulkanApplicationInfo();
    if(m_spVkApplicationInfo == nullptr)
        throw HostMemoryAllocationException("Failed to allocate memory for VkApplicationInfo");
    //filling in VkInstanceCreateInfo
    prepareVulkanInstanceInfo();
    if(m_spVkInstanceCreateInfo == nullptr)
        throw HostMemoryAllocationException("Failed to allocate memory for VkInstanceCreateInfo");
}

void Application::release()
{
    m_isInitialized = false;
    m_isConfigured = false;
    if(m_spConfigurator)
    {
        m_spConfigurator.reset();
        m_spConfigurator = nullptr;
    }
    if(m_spVkApplicationInfo)
    {
        m_spVkApplicationInfo.reset();
        m_spVkApplicationInfo = nullptr;
    }
    if(m_spVkInstanceCreateInfo)
    {
        m_spVkInstanceCreateInfo.reset();
        m_spVkInstanceCreateInfo = nullptr;
    }
    if(m_spLogStream)
    {
        m_spLogStream.reset();
        m_spLogStream = nullptr;
    }
    if(m_spErrorStream)
    {
        m_spErrorStream.reset();
        m_spErrorStream = nullptr;
    }
}

Application::Application() throw(HostMemoryAllocationException)
{
    init();
}

Application::~Application()
{
    release();
}

void Application::log(const char* message, Application::LOG_LEVEL level)
{
    if (!m_isInitialized)
        throw ApplicationNotInitializedException();
    if (!m_isConfigured)
        throw ApplicationNotConfiguredException();
    if (!m_isLoggingEnabled)
        return;

    if(m_spErrorStream == nullptr)
		return;
    if(m_spLogStream == nullptr)
		return;

    switch (level)
    {
        case LOG_INFO:
            *m_spLogStream << m_spVkApplicationInfo->pApplicationName << " from " << m_spVkApplicationInfo->pEngineName
                           <<
                           " at " << getCurrentTimeString() << " INFO: " << message << std::endl;
            (*m_spLogStream).flush();
            break;
        case LOG_WARN:
            *m_spLogStream << m_spVkApplicationInfo->pApplicationName << " from " << m_spVkApplicationInfo->pEngineName
                           <<
                           " at " << getCurrentTimeString() << " WARNING: " << message << std::endl;
            (*m_spLogStream).flush();
            break;
        case LOG_ERROR:
            if (!m_isErrorLoggingEnabled)
                break;

            *m_spErrorStream << m_spVkApplicationInfo->pApplicationName << " from "
                             << m_spVkApplicationInfo->pEngineName <<
                             " at " << getCurrentTimeString() << " ERROR: " << message << std::endl;
            (*m_spErrorStream).flush();
            break;
    }
}

void Application::prepareVulkanApplicationInfo()
{
    try
    {
        m_spVkApplicationInfo = std::make_shared<VkApplicationInfo>();
    }
    catch(bad_alloc&)
    {
        m_spVkApplicationInfo = nullptr;
        return;
    }

    auto configuration = m_spConfigurator->getConfiguration();
    m_spVkApplicationInfo->apiVersion = configuration->apiVersion;
    m_spVkApplicationInfo->engineVersion = configuration->engineVersion;
    m_spVkApplicationInfo->applicationVersion = configuration->applicationVersion;
    m_spVkApplicationInfo->pApplicationName = configuration->applicationName;
    m_spVkApplicationInfo->pEngineName = configuration->engineName;
    m_spVkApplicationInfo->pNext = nullptr;
    m_spVkApplicationInfo->sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
}

void Application::prepareVulkanInstanceInfo()
{
    try
    {
        m_spVkInstanceCreateInfo = std::make_shared<VkInstanceCreateInfo>();
    }
    catch(bad_alloc&)
    {
        m_spVkInstanceCreateInfo = nullptr;
        return;
    }
    auto configuration = m_spConfigurator->getConfiguration();
    m_spVkInstanceCreateInfo->sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    m_spVkInstanceCreateInfo->pNext = nullptr;
    m_spVkInstanceCreateInfo->flags = 0;
    m_spVkInstanceCreateInfo->enabledExtensionCount = static_cast<uint32_t>(configuration->enabledExtensionsNames
            .size());
    m_spVkInstanceCreateInfo->enabledLayerCount = static_cast<uint32_t>(configuration->enabledLayersNames.size());
    m_spVkInstanceCreateInfo->pApplicationInfo = m_spVkApplicationInfo.get();

    if(configuration->enabledExtensionsNames.size() > 0)
        m_spVkInstanceCreateInfo->ppEnabledExtensionNames = &configuration->enabledExtensionsNames[0];
    else
        m_spVkInstanceCreateInfo->ppEnabledExtensionNames = nullptr;

    if(configuration->enabledLayersNames.size() > 0)
        m_spVkInstanceCreateInfo->ppEnabledLayerNames = &configuration->enabledLayersNames[0];
    else
        m_spVkInstanceCreateInfo->ppEnabledLayerNames = nullptr;
}
