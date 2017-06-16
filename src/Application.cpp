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
 * \brief Contains Application class definition
 * \author Lev Sizov
 * \date 28.05.2017
 */

#include "include/Application.hpp"
#include "include/VulkalcVersion.hpp"
#include <string>
#include <stdlib.h>
#include <cstring>

using namespace Vulkalc;

Application::Application() throw(HostMemoryAllocationException)
{
    if (m_isInitialized)
        return;

    m_isInitialized = true;
    m_isLoggingEnabled = false;
    m_isErrorLoggingEnabled = false;
    m_spConfigurator = std::make_shared<Configurator>();
}

Application::~Application()
{
    m_isInitialized = false;
    m_isConfigured = false;
    if(m_spConfigurator)
        m_spConfigurator.reset();

    if(m_spRunner)
        m_spRunner.reset();

    if(m_spVkApplicationInfo)
        m_spVkApplicationInfo.reset();

    if(m_spVkInstanceCreateInfo)
        m_spVkInstanceCreateInfo.reset();

    if(m_spLogStream)
        m_spLogStream.reset();

    if(m_spErrorStream)
        m_spErrorStream.reset();

    if(m_spPhysicalDevice)
        m_spPhysicalDevice.reset();

    if(m_spQueue)
        m_spQueue.reset();

    if(m_spDevice)
    {
        VkDevice device = *(m_spDevice->getVkDevice());
        m_spDevice.reset();
        vkDestroyDevice(device, nullptr);
    }

    //this should be last
    if(isApplicationConfigured())
        vkDestroyInstance(m_VkInstance, nullptr);
}

void Application::configure(bool reconfigure)
throw(ApplicationNotInitializedException,
HostMemoryAllocationException,
VulkanOperationException)
{
    if (!m_isInitialized)
        throw ApplicationNotInitializedException();

    //allowing reconfiguring only if reconfigure flag is true
    if(!reconfigure && m_isConfigured)
        return;

    _configure();
}

void Application::_configure() throw(HostMemoryAllocationException, VulkanOperationException)
{
    auto configuration = m_spConfigurator->getConfiguration();
    m_spLogStream = configuration->logStream;
    m_spErrorStream = configuration->errorStream;
    m_isLoggingEnabled = configuration->isLoggingEnabled;
    m_isErrorLoggingEnabled = configuration->isErrorLoggingEnabled;

    //filling in VkApplicationInfo
    _prepareVulkanApplicationInfo();
    if(m_spVkApplicationInfo == nullptr)
        throw HostMemoryAllocationException("Failed to allocate memory for VkApplicationInfo");

    _checkAvailableExtensions();

    //filling in VkInstanceCreateInfo
    _prepareVulkanInstanceInfo();
    if(m_spVkInstanceCreateInfo == nullptr)
        throw HostMemoryAllocationException("Failed to allocate memory for VkInstanceCreateInfo");

    //creating VkInstance
    VkResult result;
    result = vkCreateInstance(m_spVkInstanceCreateInfo.get(), nullptr, &m_VkInstance);
    if(result != VK_SUCCESS)
        throw VulkanOperationException("Failed to create VkInstance");

    m_isConfigured = true;
}

void Application::log(const char* message, Application::LOG_LEVEL level) const throw(
ApplicationNotInitializedException,
ApplicationNotConfiguredException
)
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

    *m_spLogStream << m_spVkApplicationInfo->pApplicationName
                   << " from "
                   << m_spVkApplicationInfo->pEngineName
                   << " at "
                   << getCurrentTimeString();
    switch (level)
    {
        case LOG_INFO:
            *m_spLogStream << " INFO: "
                           << message
                           << std::endl;
            m_spLogStream->flush();
            break;
        case LOG_WARN:
            *m_spLogStream << " WARNING: "
                           << message
                           << std::endl;
            m_spLogStream->flush();
            break;
        case LOG_ERROR:
            if (!m_isErrorLoggingEnabled)
                break;

            *m_spErrorStream << " ERROR: "
                             << message
                             << std::endl;
            m_spErrorStream->flush();
            break;
    }
}

void Application::_prepareVulkanApplicationInfo()
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

void Application::_prepareVulkanInstanceInfo()
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

void Application::_checkAvailableExtensions()
{
    auto configuration = m_spConfigurator->getConfiguration();
    if(configuration->enabledExtensionsNames.size() == 0)
        return; //no extensions are enabled, so nothing to check

    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    std::vector<VkExtensionProperties> extensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
    auto it = configuration->enabledExtensionsNames.begin();
    for(const VkExtensionProperties extension : extensions)
    {
        for(; it != configuration->enabledExtensionsNames.end(); ++it)
        {
            if(strcmp(*it, extension.extensionName) != 0)
            {
                configuration->enabledExtensionsNames.erase(it);
                std::string message = "Extension removed as unsupported - ";
                message.append(*it);
                log(message.c_str(), LOG_INFO);
            }
        }
    }
}

std::vector<SharedPhysicalDevice> Application::enumeratePhysicalDevices()
{
    if(m_VkInstance == nullptr)
        throw ApplicationNotConfiguredException();
    std::vector<SharedPhysicalDevice> physicalDevices;
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(m_VkInstance, &deviceCount, nullptr);
    if(deviceCount == 0)
        return physicalDevices;

    m_devices = std::vector<VkPhysicalDevice>(deviceCount);
    vkEnumeratePhysicalDevices(m_VkInstance, &deviceCount, m_devices.data());
    for(VkPhysicalDevice device : m_devices)
    {
        SharedPhysicalDevice physicalDevice = std::make_shared<PhysicalDevice>(device);
        physicalDevices.push_back(physicalDevice);
    }
    return physicalDevices;
}

VkResult Application::_vkGetBestTransferQueueNPH(VkPhysicalDevice* physicalDevice, uint32_t* queueFamilyIndex)
{
    uint32_t queueFamilyPropertiesCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(*physicalDevice, &queueFamilyPropertiesCount, 0);

    VkQueueFamilyProperties* const queueFamilyProperties = (VkQueueFamilyProperties*) malloc(
            sizeof(VkQueueFamilyProperties) * queueFamilyPropertiesCount);

    vkGetPhysicalDeviceQueueFamilyProperties(*physicalDevice, &queueFamilyPropertiesCount, queueFamilyProperties);

    // first try and find a queue that has just the transfer bit set
    for(uint32_t i = 0; i < queueFamilyPropertiesCount; i++)
    {
        // mask out the sparse binding bit that we aren't caring about (yet!)
        const VkQueueFlags maskedFlags = (~VK_QUEUE_SPARSE_BINDING_BIT & queueFamilyProperties[i].queueFlags);

        if(!((VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT) & maskedFlags) &&
           (VK_QUEUE_TRANSFER_BIT & maskedFlags))
        {
            *queueFamilyIndex = i;
            return VK_SUCCESS;
        }
    }

    // otherwise we'll prefer using a compute-only queue,
    // remember that having compute on the queue implicitly enables transfer!
    for(uint32_t i = 0; i < queueFamilyPropertiesCount; i++)
    {
        // mask out the sparse binding bit that we aren't caring about (yet!)
        const VkQueueFlags maskedFlags = (~VK_QUEUE_SPARSE_BINDING_BIT & queueFamilyProperties[i].queueFlags);

        if(!(VK_QUEUE_GRAPHICS_BIT & maskedFlags) && (VK_QUEUE_COMPUTE_BIT & maskedFlags))
        {
            *queueFamilyIndex = i;
            return VK_SUCCESS;
        }
    }

    // lastly get any queue that'll work for us (graphics, compute or transfer bit set)
    for(uint32_t i = 0; i < queueFamilyPropertiesCount; i++)
    {
        // mask out the sparse binding bit that we aren't caring about (yet!)
        const VkQueueFlags maskedFlags = (~VK_QUEUE_SPARSE_BINDING_BIT & queueFamilyProperties[i].queueFlags);

        if((VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT | VK_QUEUE_TRANSFER_BIT) & maskedFlags)
        {
            *queueFamilyIndex = i;
            return VK_SUCCESS;
        }
    }

    return VK_ERROR_INITIALIZATION_FAILED;
}

VkResult Application::_vkGetBestComputeQueueNPH(VkPhysicalDevice* physicalDevice, uint32_t* queueFamilyIndex)
{
    uint32_t queueFamilyPropertiesCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(*physicalDevice, &queueFamilyPropertiesCount, 0);

    VkQueueFamilyProperties* const queueFamilyProperties = (VkQueueFamilyProperties*) malloc(
            sizeof(VkQueueFamilyProperties) * queueFamilyPropertiesCount);

    vkGetPhysicalDeviceQueueFamilyProperties(*physicalDevice, &queueFamilyPropertiesCount, queueFamilyProperties);

    // first try and find a queue that has just the compute bit set
    for(uint32_t i = 0; i < queueFamilyPropertiesCount; i++)
    {
        // mask out the sparse binding bit that we aren't caring about (yet!) and the transfer bit
        const VkQueueFlags maskedFlags = (~(VK_QUEUE_TRANSFER_BIT | VK_QUEUE_SPARSE_BINDING_BIT) &
                                          queueFamilyProperties[i].queueFlags);

        if(!(VK_QUEUE_GRAPHICS_BIT & maskedFlags) && (VK_QUEUE_COMPUTE_BIT & maskedFlags))
        {
            *queueFamilyIndex = i;
            return VK_SUCCESS;
        }
    }

    // lastly get any queue that'll work for us
    for(uint32_t i = 0; i < queueFamilyPropertiesCount; i++)
    {
        // mask out the sparse binding bit that we aren't caring about (yet!) and the transfer bit
        const VkQueueFlags maskedFlags = (~(VK_QUEUE_TRANSFER_BIT | VK_QUEUE_SPARSE_BINDING_BIT) &
                                          queueFamilyProperties[i].queueFlags);

        if(VK_QUEUE_COMPUTE_BIT & maskedFlags)
        {
            *queueFamilyIndex = i;
            return VK_SUCCESS;
        }
    }

    return VK_ERROR_INITIALIZATION_FAILED;
}

void Application::_continueConfiguring()
{
    _createDevice();

    VkQueue computeQueue;
    vkGetDeviceQueue(*(getDevice()->getVkDevice()), m_queueFamilyIndex, 0, &computeQueue);
    m_spQueue = std::make_shared<VkQueue>(computeQueue);
    m_spRunner = std::make_shared<Runner>(m_spQueue, m_queueFamilyIndex);
    m_spShaderProvider = std::make_shared<ShaderProvider>(m_spDevice);
}

void
Application::setPhysicalDevice(const SharedPhysicalDevice& physicalDevice) throw(Exception, VulkanOperationException)
{
    if(physicalDevice == nullptr || m_spPhysicalDevice != nullptr)
        throw Exception("Passed physical device is null or PhysicalDevice is already configured");

    m_spPhysicalDevice = physicalDevice;
    _continueConfiguring();
}

void Application::_createDevice()
{
    const float queuePriority = 1.0f;
    VkResult result = _vkGetBestComputeQueueNPH(m_spPhysicalDevice->getVkPhysicalDevice().get(), &m_queueFamilyIndex);
    if(result != VK_SUCCESS)
        throw VulkanOperationException("Failed to find QueueFamily suitable for computing");

    VkDeviceQueueCreateInfo vkDeviceQueueCreateInfo;
    vkDeviceQueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    vkDeviceQueueCreateInfo.pNext = nullptr;
    vkDeviceQueueCreateInfo.queueFamilyIndex = m_queueFamilyIndex;
    vkDeviceQueueCreateInfo.pQueuePriorities = &queuePriority;
    vkDeviceQueueCreateInfo.queueCount = 1;
    vkDeviceQueueCreateInfo.flags = 0;

    SharedConfiguration configuration = getConfigurator()->getConfiguration();
    VkDeviceCreateInfo deviceCreateInfo;
    deviceCreateInfo.flags = 0;
    deviceCreateInfo.pNext = nullptr;
    deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceCreateInfo.enabledLayerCount = static_cast<uint32_t>(configuration->enabledLayersNames.size());
    if(configuration->enabledLayersNames.size() > 0)
        deviceCreateInfo.ppEnabledLayerNames = &(configuration->enabledLayersNames[0]);
    else
        deviceCreateInfo.ppEnabledLayerNames = nullptr;

    deviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(configuration->enabledExtensionsNames.size());
    if(configuration->enabledExtensionsNames.size() > 0)
        deviceCreateInfo.ppEnabledExtensionNames = &(configuration->enabledExtensionsNames[0]);
    else
        deviceCreateInfo.ppEnabledExtensionNames = nullptr;

    deviceCreateInfo.queueCreateInfoCount = 1;
    deviceCreateInfo.pEnabledFeatures = getPhysicalDevice()->getPhysicalDeviceFeatures().get();
    deviceCreateInfo.pQueueCreateInfos = &vkDeviceQueueCreateInfo;

    VkDevice device;
    result = vkCreateDevice(*(getPhysicalDevice()->getVkPhysicalDevice()), &deviceCreateInfo, nullptr,
                            &device);
    if(result != VK_SUCCESS)
        throw VulkanOperationException("Failed to create VkDevice");

    m_spDevice = std::make_shared<Device>(m_spPhysicalDevice, std::make_shared<VkDevice>(device));
}

std::string Application::getVulkalcVersion() const
{
#ifndef __MINGW32_VERSION
    std::string version =   std::to_string(VULKALC_MAJOR_VERSION) + "." +
                            std::to_string(VULKALC_MINOR_VERSION) + "." +
                            std::to_string(VULKALC_PATCH_VERSION);
#else
    std::string version = VULKALC_VERSION;
#endif
    return version;
}
