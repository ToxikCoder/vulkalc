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
 *
 * Contains Configuration class declaration. Object of this class is used to configure Application. See sample project
 * for usage example.
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
         *
         * Specifies the name of Application. Used in VkApplicationInfo.
         */
        const char* applicationName = "Vulkalc Application";

        /*!
         * \brief Version of application. Feel free to change
         *
         * Specifies the version of application to be used in VkApplicationInfo
         */
        uint32_t applicationVersion = VK_MAKE_VERSION(1, 0, 0);

        /*!
         * \brief Engine name. Feel free to change.
         *
         * Specifies engine name, if there is any. Default value is "Vulkalc". Used in VkApplicationInfo
         */
        const char* engineName = "Vulkalc";

        /*!
         * \brief Engine version. Feel free to change.
         *
         * Specifies the version of engine to be used in VkApplicationInfo
         */
        uint32_t engineVersion = VK_MAKE_VERSION(1, 0, 0);

        /*!
         * \brief Vulkan API version. Don't change until you know what you are doing.
         * \warning apiVersion must be equal to Vulkan SDK version.
         *
         * Specifies used Vulkan API version. Change only if you have SDK version higher, than 1.0.39.1
         */
        uint32_t apiVersion = VK_MAKE_VERSION(1, 0, 39);

        /*!
         * \brief Vector of names of enabled Vulkan Layers. Feel free to add or remove them.
         *
         * This vector contains the names of Vulkan layers. VkInstance tries to enable them for latter usage.
         */
        std::vector<const char*> enabledLayersNames = std::vector<const char*>();

        /*!
         * \brief Vector of names of enabled Vulkan extensions. Feel free to add or remove them.
         *
         * This vector contains the names of Vulkan extensions. Some of them can be unsupported by physical device.
         */
        std::vector<const char*> enabledExtensionsNames = std::vector<const char*>();

        /*!
         * \brief Boolean flag for general logging.
         *
         * This flag enables or disables logging inside the Vulkalc library. Enabled by default
         *
         * \note Reserved for future usage
         */
        bool isLoggingEnabled = true;

        /*!
         * \brief Boolean flag for error logging. Enabled by default.
         * \note This setting is ignored if isLoggingEnabled set to false.
         * \note Reserved for future usage
         *
         * This flag enables or disables loggin inside the Vulkalc library. Enabled by default
         */
        bool isErrorLoggingEnabled = true;

        /*!
         * \brief Shared pointer to output stream for general logging.
         *
         * Shared pointer to logging iostream. Vulkalc writes logs to this stream, if isLoggingEnabled is true
         * \note Reserved for future usage
         */
        SharedIOStream logStream;

        /*!
         * \brief Shared pointer to output stream for error logging.
         * Shared pointer to logging iostream. Vulkalc writes error to this stream, if isLoggingEnabled and isErrorLoggingEnabled are true
         * \note Reserved for future usage
         */
        SharedIOStream errorStream;

        /*!
         * \brief Configuration constructor
         * Configuration constructor. Please, do not use it to create Configuration object, use Configurator::getConfiguration()
         */
        Configuration() {};

        /*!
         * \brief Configuration destructor
         *
         * Configuration destructor
         */
        virtual ~Configuration()
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

    /*!
     * Shorter form of shared pointer to Configuration
     */
    typedef std::shared_ptr<Configuration> SharedConfiguration;
}

#endif //VULKALC_LIBRARY_CONFIGURATION_H
