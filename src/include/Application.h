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

#include "RAII.h"
#include "export.h"

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
     * call \code init() before usage and \code release() after all usage
     *
     * \warning This class is not thread-safe.
     */
    class VULKALC_API Application : public RAII
    {
    public:
        /*!
         * \brief Returns instance of Application
         * \return pointer to instance of Application
         * \note Uses lazy initialization, but doesn't call \code Init()
         */
        static const Application* getInstance();

        /*!
         * \copydoc RAII::Init()
         *
         * Initializes Application
         */
        virtual void init() override;

        /*!
         * \copydoc RAII::Release()
         *
         * Releases Application - prepares Application instance to be deleted
         */
        virtual void release() override;

    private:
        /*!
         * \brief Application constructor
         */
        Application();

        /*!
         * \brief Application destructor
         */
        ~Application();
    };
}

#endif //VULKALC_APPLICATION_H
