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
 * \file Application.hpp
 * \brief Vulkalc entry point class
 * \author Lev Sizov
 * \date 28.05.17
 *
 * This file contains Application class definition which is the entry point for the Vulkalc library
 */

#pragma once

#ifndef VULKALC_APPLICATION_H
#define VULKALC_APPLICATION_H

#define VULKALC_MAJOR_VERSION @PROJECT_VERSION_MAJOR@
#define VULKALC_MINOR_VERSION @PROJECT_VRESION_MINOR@
#define VULKALC_PATCH_VERSION @PROJECT_VERSION_PATCH@

#include "RAII.hpp"
#include "Export.hpp"
#include "Configurator.hpp"
#include "Exceptions.hpp"
#include "Utilities.hpp"

#include <vulkan/vulkan.hpp>


/*!
 * \namespace Vulkalc
 * \brief Vulkalc namespace that contains all Vulkalc classes
 *
 * Vulkalc namespace that contains all Vulkalc classes.
 */
namespace Vulkalc
{
    /*!
     * \class Application
     * \extends RAII
     * \brief Vulkalc entry point class
     *
     * Application class is the entry point for Vulkalc library. It contains and gives access to all Vulkalc
     * classes and functions.
     *
     * \note Application class uses RAII and Singleton patterns. Call \code getInstance() to get pointer,
     * call \code init() before usage and \code release() after usage.
     *
     * \warning This class is not thread-safe.
     */
    class VULKALC_API Application : private RAII
    {
    public:

        /*!
         * \brief constructor of Application.
         * \throws HostMemoryAllocationException - is thrown if Application fails to allocate memory in heap
         */
        Application() throw(HostMemoryAllocationException);

        /*!
         * \brief Checks if Application is initialized with init().
         * \return is initialized flag.
         */
        inline bool isApplicationInitialized() { return m_isInitialized; };

        /*!
         * \brief Checks if Application is configured.
         * \return is configured flag.
         */
        inline bool isApplicationConfigured() { return m_isConfigured; };

        /*!
         * \brief Configures Application.
         *
         * Configures Application with Configuration, fetched from Configurator.
         * \param reconfigure flag for allowing or not allowing to reconfigure Application
         * \note You should explicitly call \code configure() after creating Application and before anything else.
         * \note This method uses Configuration available at the moment. So you have to change your Configuration
         * before-hand, otherwise default values will be used.
         * \warning calling configure(true) recreates almost everything inside Application
         * \throws ApplicationNotInitializedException - thrown if Application instance is not initialized
         * \throws HostMemoryAllocationException - thrown if failed to allocate memory in heap
         */
        void configure(bool reconfigure) throw(ApplicationNotInitializedException, HostMemoryAllocationException);

        /*!
         * \brief Enumeration for logging levels
         */
        enum LOG_LEVEL { LOG_INFO, LOG_WARN, LOG_ERROR };

        /*!
         * \brief Writes message to logging stream, which depends on logging level
         * \param message message to write
         * \param level logging level
         * \throws ApplicationNotInitializedException - thrown if Application instance is not initialized
         * \throws ApplicationNotConfiguredException - thrown if Application is not explicitly configured by
         * calling \code Application::configure()
         */
        void log(const char* message, LOG_LEVEL level);

        /*!
         * \brief Returns shared pointer to Configurator
         *
         * Returns shared pointer to Configurator, which should be used to acquire Configuration
         * and configure Application before calling \code Application::configure()
         * \return shared pointer to Configurator
         */
        const SharedConfigurator getConfigurator() { return m_spConfigurator; }

        /*!
         * \brief Returns shared pointer to logging stream.
         * \return shared pointer to logging stream
         *
         * \note This stream is equal to Configuration.logStream after calling \code Application::configure()
         */
        const SharedIOStream getLoggingStream() { return m_spLogStream; }

        /*!
         * \brief Returns constant shared pointer to error logging stream.
         * \return constant shared pointer to error logging stream
         *
         * \note This stream is equal to Configuration.errorStream after calling \code Application::configure()
         */
        const SharedIOStream getErrorStream() { return m_spErrorStream; }

        virtual ~Application();

    private:
        virtual void init() override;
        virtual void release() override;

        void prepareVulkanApplicationInfo();
        void prepareVulkanInstanceInfo();

        void configure() throw(HostMemoryAllocationException);

        bool m_isInitialized = false;
        bool m_isConfigured = false;

        bool m_isLoggingEnabled;
        bool m_isErrorLoggingEnabled;
        SharedConfigurator m_spConfigurator;
        SharedIOStream m_spLogStream;
        SharedIOStream m_spErrorStream;
        SharedVkApplicationInfo m_spVkApplicationInfo;
        SharedInstanceCreateInfo m_spVkInstanceCreateInfo;
        SharedVkInstance m_spVkInstance;
    };
}

#endif //VULKALC_APPLICATION_H
