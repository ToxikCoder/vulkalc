/*
* MIT License
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
 * \file RAII.hpp
 * \brief RAII pattern interface
 * \author Lev Sizov
 * \date 28.05.17
 *
 * This file contains RAII class which plays as interface for RAII pattern.
 */

#ifndef VULKALC_RAII_H
#define VULKALC_RAII_H

#include "Export.hpp"

/*!
 * \copydoc Application
 */
namespace Vulkalc
{
    /*!
     * \brief RAII class which plays as interface for RAII pattern
     *
     * Abstract class RAII, which plays as interface to implement RAII pattern
     */
    class VULKALC_API RAII
    {
    protected:
        /*!
         * \brief Initializes a resource
         */
        virtual void init() = 0;

        /*!
         * \brief Releases a resource
         */
        virtual void release() = 0;
    };
}

#endif //VULKALC_RAII_H
