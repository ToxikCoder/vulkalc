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
 * \file Verifier.hpp
 * \brief Verifier class which provides interface to verify various things
 * \author Lev Sizov
 * \date 28.05.17
 *
 * This file contains Verifier class which provides interface to verify Vulkan installation, library tools and shaders
 *
 */

#ifndef VULKALC_LIBRARY_VERIFIER_H
#define VULKALC_LIBRARY_VERIFIER_H

#include "RAII.hpp"
#include "Export.hpp"

/*!
 * \copydoc Vulkalc
 */
namespace Vulkalc
{
    /*!
     * \class Verifier
     * \brief Provides interface for specific verifiers
     * \extends RAII
     *
     * \note Verifier class uses RAII pattern. Call \code init() before usage and \code release() after usage
     *
     * \warning This class is not thread-safe.
     */
    class VULKALC_API Verifier : public RAII
    {

    };
}

#endif //VULKALC_LIBRARY_VERIFIER_H
