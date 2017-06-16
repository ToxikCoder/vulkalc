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
 * \file Task.hpp
 * \brief Contains compute task Task class definition
 * \author Lev Sizov
 * \date 09.06.2017
 */

#pragma once

#ifndef VULKALC_LIBRARY_TASK_HPP
#define VULKALC_LIBRARY_TASK_HPP

#include "Export.hpp"
#include "VerifiedShader.hpp"
#include "Exceptions.hpp"
#include "Utilities.hpp"
#include "Device.hpp"
#include "Task.hpp"
#include <memory>

namespace Vulkalc
{

    /*!
     * \class Task
     *
     * Compute task, with bound shader and data
     */
    class VULKALC_API Task {
    public:

        /*!
         * Task constructor. Prepares device for computing with specified shader. Do not use it to create Task,
         * use Runner::createTaskForShader() instead.
         * \param m_spDevice device to use for computing
         * \param shader compute shader to use
         */
        Task(const SharedDevice m_spDevice, const VerifiedShader &shader) throw(Exception);

        /*!
         * This struct is example of data container for matrix summation
         */
        typedef struct {
            uint32_t buffer_size;
            int32_t* in_buffer1;
            int32_t* in_buffer2;
        } TaskBuffers;

        /*!
         * Sets input data buffers
         * \param buffers TaskBuffers containing input data buffers
         */
        void setData(TaskBuffers &buffers) { m_buffers = buffers; };

        /*!
         * Task constructor. Do not use it to create Task, use Runner::createTaskForShader() instead.
         */
        Task() {};

        /*!
         * Task destructor
         */
        virtual ~Task();

    private:
        friend class Runner;

        TaskBuffers _getTaskBuffers() const { return m_buffers; };

        const SharedDevice _getDevice() const { return m_spDevice; };

        const SharedPipeline _getPipeline() const { return m_spPipeline; };

        const SharedPipelineLayout _getPipelineLayout() const { return m_spPipelinelayout; };

        const SharedDescriptorSetlayout _getDescriptorSetLayout() { return m_spDescriptorSetLayout; };

        TaskBuffers m_buffers;
        SharedDevice m_spDevice;
        SharedPipeline m_spPipeline;
        SharedPipelineLayout m_spPipelinelayout;
        SharedDescriptorSetlayout m_spDescriptorSetLayout;

    };

    /*!
     * Shorter form for shared pointer to Task
     */
    typedef std::shared_ptr<Task> SharedTask;

    /*!
     * Contains computing results
     */
    typedef struct
    {
        uint32_t buffer_size;
        int32_t* out_buffer;
        Task* task;
    } TaskResult;
}

#endif //VULKALC_LIBRARY_TASK_HPP
