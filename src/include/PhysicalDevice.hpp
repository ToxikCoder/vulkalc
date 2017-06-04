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
 * \file PhysicalDevice.h
 * \brief 
 * \author Lev Sizov
 * \date 03.06.2017
 */

#pragma once

#ifndef VULKALC_LIBRARY_PHYSICALDEVICE_H
#define VULKALC_LIBRARY_PHYSICALDEVICE_H

#include "Export.hpp"
#include "Utilities.hpp"
#include <vulkan/vulkan.h>

/*!
 * \copydoc Vulkalc
 */
namespace Vulkalc
{
    /*!
     * \class PhysicalDevice
     * \brief Data structure containing Vulkan physical device, properties and features
     */
    class VULKALC_API PhysicalDevice
    {
    public:
        /*!
         * \brief Checks if this physical device is suitable for computing
         * \return is suitable for computing flag
         *
         * Checks if this physical device is suitable for computing by checking if GPU is discrete
         */
        bool isSuitableForComputing() const;

        /*!
         * \brief Returns properties of this device
         * \return data structure with properties of this devices
         */
        const SharedPhysicalDeviceProperties getPhysicalDeviceProperties() const { return m_spProperties; };

        /*!
         * \brief Returns features of this device
         * \return data structure with features of this devices
         */
        const SharedPhysicalDeviceFeatures getPhysicalDeviceFeatures() const { return m_spFeatures; };

        /*!
         * \brief Returns VkPhysicalDevice for internal use
         * \return shared pointer to VkPhysicalDevice
         */
        const SharedVkPhysicalDevice getVkPhysicalDevice() const { return m_spDevice; };

        /*!
         * \brief Returns C-style string with a name of this GPU
         * \return C-style string with the name of this GPU
         */
        std::string getDeviceName() const;

        /*!
         * \brief PhysicalDevice constructor
         * \param physicalDevice Vulkan physical device to use
         */
        PhysicalDevice(const VkPhysicalDevice& physicalDevice);

        /*!
         * \brief PhysicalDevice destructor
         */
        virtual ~PhysicalDevice();

    private:
        SharedVkPhysicalDevice m_spDevice;
        SharedPhysicalDeviceProperties m_spProperties;
        SharedPhysicalDeviceFeatures m_spFeatures;

    };

    typedef std::shared_ptr<PhysicalDevice> SharedPhysicalDevice;
}

#endif //VULKALC_LIBRARY_PHYSICALDEVICE_H
