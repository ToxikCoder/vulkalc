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
#include "include/Utilities.h"

using namespace Vulkalc;

const Application& Application::getInstance() throw(HostMemoryAllocationException)
{
    static const Application application;
    return application;
}

void Application::init()
{
    if (m_isInitialized)
        return;

    m_isInitialized = true;
    try
    {
        m_pConfigurator = new Configurator();
    }
    catch(bad_alloc& e)
    {
        throw HostMemoryAllocationException("Failed to allocate memory for Configurator");
    }
    m_pVkApplicationInfo = nullptr;
    m_pVkInstanceCreateInfo = nullptr;
}

void Application::configure() throw(ApplicationNotInitializedException, HostMemoryAllocationException)
{
    if (!m_isInitialized)
        throw ApplicationNotInitializedException();
    if (m_isConfigured)
        return;

    m_isConfigured = true;
    auto configuration = m_pConfigurator->getConfiguration();
    m_pLogStream = configuration->logStream;
    m_pErrorStream = configuration->errorStream;
    m_isLoggingEnabled = configuration->isLoggingEnabled;
    m_isErrorLoggingEnabled = configuration->isErrorLoggingEnabled;

    //filling in VkApplicationInfo
    prepareVulkanApplicationInfo();
    if(m_pVkApplicationInfo == nullptr)
        throw HostMemoryAllocationException("Failed to allocate memory for VkApplicationInfo");
    //filling in VkInstanceCreateInfo
    prepareVulkanInstanceInfo();
    if(m_pVkInstanceCreateInfo == nullptr)
        throw new HostMemoryAllocationException("Failed to allocate memory for VkInstanceCreateInfo");
}

void Application::release()
{
    m_isInitialized = false;
    m_isConfigured = false;
    if (m_pConfigurator)
    {
        delete m_pConfigurator;
        m_pConfigurator = nullptr;
    }
    if (m_pVkApplicationInfo)
    {
        delete m_pVkApplicationInfo;
        m_pVkApplicationInfo = nullptr;
    }
    if (m_pVkInstanceCreateInfo)
    {
        delete m_pVkInstanceCreateInfo;
        m_pVkInstanceCreateInfo = nullptr;
    }
    if (m_pLogStream)
    {
        m_pLogStream = nullptr;
    }
    if (m_pErrorStream)
    {
        m_pErrorStream = nullptr;
    }
}

Application::Application()
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

    switch (level)
    {
        case LOG_INFO:
            *m_pLogStream << m_pVkApplicationInfo->pApplicationName << " from " << m_pVkApplicationInfo->pEngineName <<
                          " at " << getCurrentTimeString() << " INFO: " << message;
            break;
        case LOG_WARN:
            *m_pLogStream << m_pVkApplicationInfo->pApplicationName << " from " << m_pVkApplicationInfo->pEngineName <<
                          " at " << getCurrentTimeString() << " WARNING: " << message;
            break;
        case LOG_ERROR:
            if (!m_isErrorLoggingEnabled)
                break;

            *m_pLogStream << m_pVkApplicationInfo->pApplicationName << " from " << m_pVkApplicationInfo->pEngineName <<
                          " at " << getCurrentTimeString() << " ERROR: " << message;
            break;
    }
}

void Application::prepareVulkanApplicationInfo()
{
    try
    {
        m_pVkApplicationInfo = new VkApplicationInfo();
    }
    catch(bad_alloc& e)
    {
        m_pVkApplicationInfo = nullptr;
        return;
    }

    auto configuration = m_pConfigurator->getConfiguration();
    m_pVkApplicationInfo->apiVersion = configuration->apiVersion;
    m_pVkApplicationInfo->engineVersion = configuration->engineVersion;
    m_pVkApplicationInfo->applicationVersion = configuration->applicationVersion;
    m_pVkApplicationInfo->pApplicationName = configuration->applicationName;
    m_pVkApplicationInfo->pEngineName = configuration->engineName;
    m_pVkApplicationInfo->pNext = nullptr;
    m_pVkApplicationInfo->sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
}

void Application::prepareVulkanInstanceInfo()
{
    try
    {
        m_pVkInstanceCreateInfo = new VkInstanceCreateInfo();
    }
    catch(bad_alloc& e)
    {
        m_pVkInstanceCreateInfo = nullptr;
        return;
    }
    auto configuration = m_pConfigurator->getConfiguration();
    m_pVkInstanceCreateInfo->sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    m_pVkInstanceCreateInfo->pNext = nullptr;
    m_pVkInstanceCreateInfo->flags = 0;
    m_pVkInstanceCreateInfo->enabledExtensionCount = static_cast<uint32_t>(configuration->enabledExtensionsNames
            .size());
    m_pVkInstanceCreateInfo->enabledLayerCount = static_cast<uint32_t>(configuration->enabledLayersNames.size());
    m_pVkInstanceCreateInfo->pApplicationInfo = m_pVkApplicationInfo;

    if(configuration->enabledExtensionsNames.size() > 0)
        m_pVkInstanceCreateInfo->ppEnabledExtensionNames = &configuration->enabledExtensionsNames[0];
    else
        m_pVkInstanceCreateInfo->ppEnabledExtensionNames = nullptr;

    if(configuration->enabledLayersNames.size() > 0)
        m_pVkInstanceCreateInfo->ppEnabledLayerNames = &configuration->enabledLayersNames[0];
    else
        m_pVkInstanceCreateInfo->ppEnabledLayerNames = nullptr;
}
