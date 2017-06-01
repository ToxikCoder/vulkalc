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
 * \file Export.hpp
 * \brief Defines platform-specific export
 * \author Lev Sizov
 * \date 28.05.17
 *
 * This file contains defines that specify platform specific way to export classes and functions
 */

#ifndef VULKALC_EXPORT_H
#define VULKALC_EXPORT_H

#if defined(_WIN32) || defined(__CYGWIN__)
#ifdef __GNUC__
#define VULKALC_API __attribute__ ((dllexport))
#else
#define VULKALC_API __declspec( dllexport )
#endif
#define VULKALC_LOCAL
#else
#if __GNUC__ >= 4
#define VULKALC_API __attribute__ ((visibility ("default")))
#define VULKALC_LOCAL __attribute__ ((visibility ("hidden")))
#else
#define VULKALC_API
#define VULKALC_LOCAL
#endif
#endif

#endif