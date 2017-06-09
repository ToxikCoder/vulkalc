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
 * \file Task.cpp
 * \brief Contains Task class definition
 * \author Lev Sizov
 * \date 09.06.2017
 */

#include "include/Task.hpp"

using namespace Vulkalc;


Task::Task(const SharedDevice device, const VerifiedShader &shader) throw(Exception)
{
    if(m_spDevice == nullptr || !shader.isCompiled())
        throw Exception("VkDevice pointer is NULL or shader is not compiled");

    m_spDevice = device;

    VkDescriptorSetLayoutBinding layoutBinding[3] = {
            {0, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1, VK_SHADER_STAGE_COMPUTE_BIT, 0},
            {1, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1, VK_SHADER_STAGE_COMPUTE_BIT, 0},
            {2, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1, VK_SHADER_STAGE_COMPUTE_BIT, 0}
    };
    VkDescriptorSetLayoutCreateInfo layoutCreateInfo = {
            VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO, 0, 0, 3, layoutBinding
    };
    VkDescriptorSetLayout descriptorSetLayout;
    VkResult result = vkCreateDescriptorSetLayout(*(m_spDevice->getVkDevice()), &layoutCreateInfo, nullptr,
                                                  &descriptorSetLayout);
    if(result != VK_SUCCESS)
        throw ("Failed to initialize DescriptorSet layout");

    m_spDescriptorSetLayout = std::make_shared<VkDescriptorSetLayout>(descriptorSetLayout);

    VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo = {
            VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO, 0, 0, 1, &descriptorSetLayout, 0, 0
    };

    VkPipelineLayout pipelineLayout;
    result = vkCreatePipelineLayout(*(m_spDevice->getVkDevice()), &pipelineLayoutCreateInfo, nullptr, &pipelineLayout);
    if(result != VK_SUCCESS)
        throw ("Failed to create pipeline layout");

    m_spPipelinelayout = std::make_shared<VkPipelineLayout>(pipelineLayout);

    VkComputePipelineCreateInfo computePipelineCreateInfo = {
            VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO, 0, 0,
            {
                    VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
                    0,
                    0,
                    VK_SHADER_STAGE_COMPUTE_BIT,
                    *(shader.getVkShaderModule()),
                    "main",
                    nullptr
            }, pipelineLayout, 0, 0
    };

    VkPipeline pipeline;
    result = vkCreateComputePipelines(*(m_spDevice->getVkDevice()), 0, 1, &computePipelineCreateInfo, nullptr,
                                      &pipeline);
    if(result != VK_SUCCESS)
        throw Exception("Failed to create compute pipeline");

    m_spPipeline = std::make_shared<VkPipeline>(pipeline);
}

Task::~Task()
{
    if(m_spPipeline) {
        VkPipeline pipeline = *m_spPipeline;
        m_spPipeline.reset();
        vkDestroyPipeline(*(m_spDevice->getVkDevice()), pipeline, 0);
    }

    if(m_spPipelinelayout) {
        VkPipelineLayout layout = *m_spPipelinelayout;
        m_spPipelinelayout.reset();
        vkDestroyPipelineLayout(*(m_spDevice->getVkDevice()), layout, 0);
    }

    if(m_spDescriptorSetLayout) {
        VkDescriptorSetLayout descriptorSetLayout = *m_spDescriptorSetLayout;
        m_spDescriptorSetLayout.reset();
        vkDestroyDescriptorSetLayout(*(m_spDevice->getVkDevice()), descriptorSetLayout, 0);
    }

    if(m_spDevice)
        m_spDevice.reset();
}
