/*
* MIT License
*
* Copyright (c) 2017 Lev Sizov a.k.a "ToxikCoder"
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

#include "include/Application.hpp"
#include "include/Utilities.h"

using namespace Vulkalc;

const Application& Application::getInstance()
{
    static const Application application;
    return application;
}

void Application::init()
{
    if (m_isInitialized)
        return;

    m_isInitialized = true;
    m_pConfigurator = new Configurator();
    m_pVkApplicationInfo = nullptr;
    m_pVkInstanceCreateInfo = nullptr;
}

void Application::configure()
{
    if (!m_isInitialized)
        throw ApplicationNotInitializedException();
    if (m_isConfigured)
        return;

    m_isConfigured = true;
    auto configuration = m_pConfigurator->getConfiguration();
    m_pLogStream = configuration->logStream;
    m_isLoggingEnabled = configuration->isLoggingEnabled;
    m_isErrorLoggingEnabled = configuration->isErrorLoggingEnabled;

    //filling in VkApplicationInfo
    m_pVkApplicationInfo = new VkApplicationInfo();
    m_pVkApplicationInfo->apiVersion = configuration->apiVersion;
    m_pVkApplicationInfo->engineVersion = configuration->engineVersion;
    m_pVkApplicationInfo->applicationVersion = configuration->applicationVersion;
    m_pVkApplicationInfo->pApplicationName = configuration->applicationName.c_str();
    m_pVkApplicationInfo->pEngineName = configuration->engineName.c_str();
    m_pVkApplicationInfo->pNext = nullptr;
    m_pVkApplicationInfo->sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    //filling in VkInstanceCreateInfo
    m_pVkInstanceCreateInfo = new VkInstanceCreateInfo();
    m_pVkInstanceCreateInfo->sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    m_pVkInstanceCreateInfo->pNext = nullptr;
    m_pVkInstanceCreateInfo->flags = 0;
    m_pVkInstanceCreateInfo->enabledExtensionCount = configuration->enabledExtensionsNames.size();
    m_pVkInstanceCreateInfo->enabledLayerCount = configuration->enabledLayersNames.size();
    m_pVkInstanceCreateInfo->pApplicationInfo = m_pVkApplicationInfo;

    if (configuration->enabledExtensionsNames.size() > 0)
        m_pVkInstanceCreateInfo->ppEnabledExtensionNames = &configuration->enabledExtensionsNames[0];
    else
        m_pVkInstanceCreateInfo->ppEnabledExtensionNames = nullptr;

    if (configuration->enabledLayersNames.size() > 0)
        m_pVkInstanceCreateInfo->ppEnabledLayerNames = &configuration->enabledLayersNames[0];
    else
        m_pVkInstanceCreateInfo->ppEnabledLayerNames = nullptr;

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
            *m_pLogStream << m_pVkApplicationInfo->pApplicationName << "from" << m_pVkApplicationInfo->pEngineName <<
                          " at " << getCurrentTimeString() << " INFO: " << message;
            break;
        case LOG_WARN:
            *m_pLogStream << m_pVkApplicationInfo->pApplicationName << "from" << m_pVkApplicationInfo->pEngineName <<
                          " at " << getCurrentTimeString() << " WARNING: " << message;
            break;
        case LOG_ERROR:
            if (!m_isErrorLoggingEnabled)
                break;

            *m_pLogStream << m_pVkApplicationInfo->pApplicationName << "from" << m_pVkApplicationInfo->pEngineName <<
                          " at " << getCurrentTimeString() << " ERROR: " << message;
            break;
    }
}

const char* Application::ApplicationNotInitializedException::what() const
{
    return "An instance of Application is not initialized. Call Application::init() first";
}

const char* Application::ApplicationNotConfiguredException::what() const
{
    return "An instance of Application is not configured. Edit Configuration instance, then call Application::configure()";
}
