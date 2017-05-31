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

/*!
 * \file Application.h
 * \brief Vulkalc entry point class
 * \author Lev Sizov
 * \date 28.05.17
 *
 * This file contains Application class definition which is the entry point for the Vulkalc library
 */

#ifndef VULKALC_APPLICATION_H
#define VULKALC_APPLICATION_H

#include "RAII.hpp"
#include "Export.hpp"
#include "Configurator.hpp"
#include <vulkan.hpp>
#include <exception>

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
         * \brief Returns instance of Application.
         * \return pointer to instance of Application.
         * \note Uses lazy initialization, but doesn't call \code Init().
         */
        static const Application& getInstance();

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
         * \note You should explicitly call \code configure() after \code init() and before anything else.
         * \note This method would use Configuration available at the moment. So you have to change your Configuration
         * before-hand, otherwise default values will be used.
         * \throws ApplicationNotInitializedException - thrown if Application instance is not initialized
         */
        void configure();

        /*!
         * \brief Enumeration for logging levels
         */
        enum LOG_LEVEL { LOG_INFO, LOG_WARN, LOG_ERROR };

        /*!
         * \brief Writes message to logging stream, which depends on logging level
         * \param message message to write
         * \param level logging level
         * \throws ApplicationNotInitializedException - thrown if Application instance is not initialized
         * \throws ApplicationNotConfiguredException - thrown if Application is not explicitly configured by calling
         * \code Application::configure()
         */
        void log(const char* message, LOG_LEVEL level);

        /*!
         * \brief This exception is thrown, when Application is not initialized, but used.
         */
        class VULKALC_API ApplicationNotInitializedException
        {
        public:
            ApplicationNotInitializedException() {};

            /*!
             * Returns the message of exception
             * \return C-way string with exception message
             */
            const char* what() const;
        };

        /*!
         * \brief This exception is thrown, when Application is not configured
         *
         * Some Application functions require instance to be configured. If it's not, this exception is thrown.
         */
        class VULKALC_API ApplicationNotConfiguredException
        {
        public:
            ApplicationNotConfiguredException() {};

            /*!
             * Returns the message of exception
             * \return C-way string with exception message
             */
            const char* what() const;
        };

        ~Application();

    private:
        virtual void init() override;

        virtual void release() override;

        bool m_isInitialized = false;
        bool m_isConfigured = false;

        //hiding constructors and destructor
        Application();

        bool m_isLoggingEnabled;
        bool m_isErrorLoggingEnabled;
        Configurator* m_pConfigurator;
        std::ostream* m_pLogStream;
        std::ostream* m_pErrorStream;
        VkApplicationInfo* m_pVkApplicationInfo;
        VkInstanceCreateInfo* m_pVkInstanceCreateInfo;
    };
}

#endif //VULKALC_APPLICATION_H
