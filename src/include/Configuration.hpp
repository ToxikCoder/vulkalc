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
 * \file Configuration.hpp
 * \brief Contains Configuration class declaration
 * \author Lev Sizov
 * \date 31.05.2017
 */

#pragma once

#ifndef VULKALC_LIBRARY_CONFIGURATION_H
#define VULKALC_LIBRARY_CONFIGURATION_H

#include "Export.hpp"
#include "Utilities.hpp"

#include <vulkan/vulkan.h>
#include <string>
#include <vector>
#include <iostream>
#include <memory>

/*!
 * \copydoc Vulkalc
 */
namespace Vulkalc
{
    /*!
     * \class Configuration
     * \brief Configuration class contains various information for Application.
     *
     * Configuration class is a container of various information used to configure VkInstance.
     */
    class VULKALC_API Configuration
    {
    public:
        /*!
         * \brief Name of the application, which uses Vulkalc library. Feel free to change.
         */
        const char* applicationName = "Vulkalc Application";

        /*!
         * \brief Version of application. Feel free to change
         */
        uint32_t applicationVersion = VK_MAKE_VERSION(1, 0, 0);

        /*!
         * \brief Engine name. Feel free to change.
         */
        const char* engineName = "Vulkalc";

        /*!
         * \brief Engine version. Feel free to change.
         */
        uint32_t engineVersion = VK_MAKE_VERSION(1, 0, 0);

        /*!
         * \brief Vulkan API version. Don't change until you know what you are doing.
         * \warning apiVersion must be equal to Vulkan SDK version.
         */
        uint32_t apiVersion = VK_MAKE_VERSION(1, 0, 39);

        /*!
         * \brief Vector of names of enabled Vulkan Layers. Feel free to add or remove them.
         */
        std::vector<const char*> enabledLayersNames = std::vector<const char*>();

        /*!
         * \brief Vector of names of enabled Vulkan extensions. Feel free to add or remove them.
         */
        std::vector<const char*> enabledExtensionsNames = std::vector<const char*>();

        /*!
         * \brief Boolean flag for general logging. Enabled by default.
         */
        bool isLoggingEnabled = true;

        /*!
         * \brief Boolean flag for error logging. Enabled by default.
         * \note This setting is ignored if isLoggingEnabled set to false.
         */
        bool isErrorLoggingEnabled = true;

        /*!
         * \brief Shared pointer to output stream for general logging.
         */
        SharedIOStream logStream;

        /*!
         * \brief Shared pointer to output stream for error logging.
         */
        SharedIOStream errorStream;

        /*!
         * \brief Configuration constructor
         */
        Configuration() {};

        /*!
         * \brief Configuration destructor
         */
        ~Configuration()
        {
            if(logStream)
            {
                logStream.reset();
                logStream = nullptr;
            }
            if(errorStream)
            {
                errorStream.reset();
                errorStream = nullptr;
            }
        };
    };

    typedef std::shared_ptr<Configuration> SharedConfiguration;
}

#endif //VULKALC_LIBRARY_CONFIGURATION_H
