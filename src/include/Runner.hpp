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
 * \file Runner.hpp
 * \brief Contains Runner class
 * \author Lev Sizov
 * \date 09.06.2017
 */

#pragma once

#ifndef VULKALC_LIBRARY_RUNNER_HPP
#define VULKALC_LIBRARY_RUNNER_HPP

#include "Export.hpp"
#include "Task.hpp"
#include "TaskResult.hpp"
#include "Utilities.hpp"

/*!
 * \copydoc Vulkalc
 */
namespace Vulkalc
{
    class VULKALC_API Runner
    {
    public:

        Runner();

        const SharedTask createNewTask() const;

        void queueTask(const SharedTask task);

        const SharedTaskResult getLastTaskResult() const { return m_spTaskResult; };

        virtual ~Runner();

    private:
        friend class Application;

        void _configure(const SharedQueue);

        SharedTaskResult m_spTaskResult;
    };
}

#endif //VULKALC_LIBRARY_RUNNER_HPP
