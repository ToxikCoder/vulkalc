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
 * \file Utilities.hpp
 * \brief Contains utility functions
 * \author Lev Sizov
 * \date 31.05.2017
 */

#ifndef VULKALC_LIBRARY_UTILITIES_H
#define VULKALC_LIBRARY_UTILITIES_H

#include "Export.hpp"
#include <chrono>
#include <time.h>

using namespace std;

/*!
 * \copydoc Vulkalc
 */
namespace Vulkalc
{
    /*!
     * Returns string representation of current date and time
     * \return current date and time as C string.
     */
    VULKALC_API const char* getCurrentTimeString()
    {
        auto now = chrono::system_clock::now();
        auto now_time_t = chrono::system_clock::to_time_t(now);
#ifdef _MSC_VER
        char time[26];
        ctime_s(time, sizeof(time), &now_time_t);
        return time;
#else
        return ctime(&now_time_t);
#endif
    }
}

#endif //VULKALC_LIBRARY_UTILITIES_H
