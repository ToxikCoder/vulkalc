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
 * \file PhysicalDevice.cpp
 * \brief 
 * \author Lev Sizov
 * \date 03.06.2017
 */

#include "include/PhysicalDevice.hpp"

using namespace Vulkalc;

PhysicalDevice::PhysicalDevice(const VkPhysicalDevice& device)
{
    m_spDevice = std::make_shared<VkPhysicalDevice>(device);
    VkPhysicalDeviceProperties properties;
    vkGetPhysicalDeviceProperties(*m_spDevice, &properties);
    m_spProperties = std::make_shared<VkPhysicalDeviceProperties>(properties);
    VkPhysicalDeviceFeatures features;
    vkGetPhysicalDeviceFeatures(*m_spDevice, &features);
    m_spFeatures = std::make_shared<VkPhysicalDeviceFeatures>(features);
}

bool PhysicalDevice::isSuitableForComputing() const
{
    return m_spProperties->deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU;
}

PhysicalDevice::~PhysicalDevice()
{
    if(m_spFeatures)
        m_spFeatures.reset();

    if(m_spProperties)
        m_spProperties.reset();

    if(m_spDevice)
        m_spDevice.reset();
}

std::string PhysicalDevice::getDeviceName() const
{
    std::string name;
    name = m_spProperties->deviceName;
    return name;
}


