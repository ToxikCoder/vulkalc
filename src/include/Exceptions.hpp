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
 * \file Exceptions.hpp
 * \brief Contains exceptions definitions
 * \author Lev Sizov
 * \date 01.06.2017
 */

#pragma once

#ifndef VULKALC_LIBRARY_EXCEPTIONS_H
#define VULKALC_LIBRARY_EXCEPTIONS_H

#include "Export.hpp"
#include <string>

namespace Vulkalc
{
    /*!
     * \class Excpetion
     * \brief General exception is Vulkalc application
     */
    class VULKALC_API Exception
    {
    public:
        /*!
         * \brief Exception constructor
         */
        Exception() : m_message(nullptr) {};

        /*!
         * \brief Exception constructor with exception message
         * \param message message of exception
         */
        explicit Exception(const char* message);

        virtual ~Exception() {};

        /*!
        * Returns the message of exception
        * \return C-way string with exception message
        */
        virtual const char* what() const;

    protected:
        const char* m_message;
        std::string m_exception_message = "Exception in Vulkalc Application";
    };

    /*!
     * \class ApplicationNotInitializedException
     * \brief This exception is thrown, when Application is not initialized, but used.
     * \extends Exception
     *
     * \note There is not constructor with message parameter.
     */
    class VULKALC_API ApplicationNotInitializedException : public Exception
    {
    public:
        /*!
         * \brief ApplicationNotInitializedException constructor
         */
        ApplicationNotInitializedException() : Exception("An instance of Application is not initialized. "
                                                                 "Call Application::init() first")
        {
            m_exception_message = "ApplicationNotInitializedException in Vulkalc Application";
        };

        virtual ~ApplicationNotInitializedException() {};

    };

    /*!
     * \class ApplicationNotConfiguredException
     * \brief This exception is thrown, when Application is not configured
     * \extends Exception
     *
     * Some Application functions require instance to be configured. If it's not, this exception is thrown.
     * \note There is not constructor with message parameter.
     */
    class VULKALC_API ApplicationNotConfiguredException : public Exception
    {
    public:
        /*!
         * \brief ApplicationNotConfiguredException constructor
         */
        ApplicationNotConfiguredException() : Exception("An instance of Application is not configured. "
                                                                "Edit Configuration instance, then call "
                                                                "Application::configure()")
        {
            m_exception_message = "ApplicationNotConfiguredException in Vulkalc Application";
        };

        virtual ~ApplicationNotConfiguredException() {};

    };

    /*!
     * \class HostMemoryAllocationException
     * \brief This exception is thrown, when failed to allocate memory in host Vulkalc application
     * \extends Exception
     */
    class VULKALC_API HostMemoryAllocationException : public Exception
    {
    public:
        /*!
         * \brief HostMemoryAllocationException constructor
         */
        HostMemoryAllocationException()
        {
            m_exception_message = "Failed to allocate memory in host application";
        };

        virtual ~HostMemoryAllocationException() {};

        /*!
         * \brief HostMemoryAllocationException constructor with message parameter
         * \param message exception message
         */
        explicit HostMemoryAllocationException(const char *message) : Exception(message) {
            m_exception_message = "Failed to allocate memory in host application";
        };

    };

    /*!
     * \class VulkanOperationException
     * \extends Exception
     * \brief Thrown when Vulkan API calls return error code
     */
    class VULKALC_API VulkanOperationException : public Exception
    {
    public:
        /*!
         * VulkanOperationException constructor
         */
        VulkanOperationException()
        {
            m_exception_message = "Vulkan API command failed: ";
        };

        virtual ~VulkanOperationException() {};

        /*!
         * \brief VulkanOperationException constructor with message parameter
         * \param message exception message
         */
        explicit VulkanOperationException(const char* message) : Exception(message) {};

    };
}

#endif //VULKALC_LIBRARY_EXCEPTIONS_H
