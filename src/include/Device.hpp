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
 * \file Device.hpp
 * \brief Contains Device class declaration
 * \author Lev Sizov
 * \date 09.06.17
 */

#pragma once

#ifndef VULKALC_LIBRARY_DEVICE_H
#define VULKALC_LIBRARY_DEVICE_H

#include "Export.hpp"
#include "PhysicalDevice.hpp"
#include <vulkan/vulkan.h>
#include <memory>

/*!
 * \copydoc Vulkalc
 */
namespace Vulkalc {
    /*!
     * \class Device
     *
     * Container for both PhysicalDevice and VkDevice
     */
    class VULKALC_API Device {
    public:

        Device(const SharedPhysicalDevice physicalDevice, const SharedVkDevice device) :
                m_pPhysicalDevice(physicalDevice), m_pDevice(device) {};

        const SharedPhysicalDevice getPhysicalDevice() const { return m_pPhysicalDevice; }

        const SharedVkDevice getVkDevice() const { return m_pDevice; };

        virtual ~Device() {
            m_pDevice.reset();
            m_pPhysicalDevice.reset();
        };

    private:
        SharedPhysicalDevice m_pPhysicalDevice;
        SharedVkDevice m_pDevice;
    };

    typedef std::shared_ptr<Device> SharedDevice;
}

#endif //VULKALC_LIBRARY_DEVICE_H
