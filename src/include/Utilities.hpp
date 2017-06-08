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
 * \file Utilities.hpp
 * \brief Contains utility functions
 * \author Lev Sizov
 * \date 31.05.2017
 */

#pragma once

#ifndef VULKALC_LIBRARY_UTILITIES_H
#define VULKALC_LIBRARY_UTILITIES_H

#include "Export.hpp"
#include <chrono>
#include <time.h>
#include <iostream>
#include <memory>
#include <vulkan/vulkan.h>

using namespace std;

/*!
 * \copydoc Vulkalc
 */
namespace Vulkalc
{
    typedef std::shared_ptr<std::iostream> SharedIOStream;
    typedef std::shared_ptr<VkApplicationInfo> SharedVkApplicationInfo;
    typedef std::shared_ptr<VkInstanceCreateInfo> SharedInstanceCreateInfo;
    typedef std::shared_ptr<VkPhysicalDevice> SharedVkPhysicalDevice;
    typedef std::shared_ptr<VkDevice> SharedDevice;
    typedef std::shared_ptr<VkPhysicalDeviceProperties> SharedPhysicalDeviceProperties;
    typedef std::shared_ptr<VkPhysicalDeviceFeatures> SharedPhysicalDeviceFeatures;
    typedef std::shared_ptr<VkShaderModule> SharedShaderModule;
    typedef std::shared_ptr<VkQueue> SharedQueue;

    /*!
     * Returns string representation of current date and time
     * \return current date and time as C string.
     */
    VULKALC_API const char* getCurrentTimeString();

    /*!
     * Checks if extension is really extension in fileName, not part of the name
     * \param fileName just a string with name of file
     * \param extenstion string without dot, which specifies extension
     * \return is extension really extension in fileName, not part of the name.
     * Returns false, if any of parameters is empty
     * \note this function doesn't read any files, just works with strings
     */
    VULKALC_API bool checkFileNameExtension(std::string fileName, std::string extension);
}

#endif //VULKALC_LIBRARY_UTILITIES_H
