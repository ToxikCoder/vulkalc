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
 * \file Runner.cpp
 * \brief This file contains Runner class definition
 * \author Lev Sizov
 * \date 09.06.2017
 */

#include "include/Runner.hpp"
#include "include/Task.hpp"
#include <cstring>

using namespace Vulkalc;


Runner::~Runner() {
    if(m_spQueue)
        m_spQueue.reset();

    if(m_spLastTask)
        m_spLastTask.reset();
}

void Runner::queueTask(const SharedTask task) throw(Exception) {
    if(task == nullptr)
        throw Exception("Task is NULL");

    m_spLastTask = task;

    VkDescriptorPoolSize descriptorPoolSize = {VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 3};
    VkDescriptorPoolCreateInfo descriptorPoolCreateInfo = {
            VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO, 0, 0, 1, 1, &descriptorPoolSize
    };
    VkDescriptorPool descriptorPool;
    VkResult result = vkCreateDescriptorPool(*(task->_getDevice()->getVkDevice()),
                                             &descriptorPoolCreateInfo, nullptr, &descriptorPool);
    if(result != VK_SUCCESS) {
        throw Exception("Failed to create DescriptorPool");
    }

    VkDescriptorSetAllocateInfo descriptorSetAllocateInfo = {
            VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO, 0, descriptorPool, 1, task->_getDescriptorSetLayout().get()
    };

    //creating set of descriptors
    VkDescriptorSet descriptorSet;
    result = vkAllocateDescriptorSets(*(task->_getDevice()->getVkDevice()), &descriptorSetAllocateInfo, &descriptorSet);
    if(result != VK_SUCCESS) {
        throw Exception("Failed to create DescriptorSet for Task");
    }

    //allocating memory and creating buffers
    VkPhysicalDeviceMemoryProperties properties;

    vkGetPhysicalDeviceMemoryProperties(*(task->_getDevice()->getPhysicalDevice()->getVkPhysicalDevice()), &properties);

    const uint32_t bufferLength = task->_getTaskBuffers().buffer_size;
    const uint32_t bufferSize = sizeof(int32_t) * bufferLength;
    const VkDeviceSize memorySize = bufferSize * 3;

    // set memoryTypeIndex to an invalid entry in the properties.memoryTypes array
    uint32_t memoryTypeIndex = VK_MAX_MEMORY_TYPES;

    for(uint32_t k = 0; k < properties.memoryTypeCount; k++) {
        if((VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT & properties.memoryTypes[k].propertyFlags) &&
           (VK_MEMORY_PROPERTY_HOST_COHERENT_BIT & properties.memoryTypes[k].propertyFlags) &&
           (memorySize < properties.memoryHeaps[properties.memoryTypes[k].heapIndex].size)) {
            memoryTypeIndex = k;
            break;
        }
    }

    result = memoryTypeIndex == VK_MAX_MEMORY_TYPES ? VK_ERROR_OUT_OF_HOST_MEMORY : VK_SUCCESS;
    if(result != VK_SUCCESS)
        throw Exception("Failed to find big enough memory chunk in device heap");

    const VkMemoryAllocateInfo memoryAllocateInfo = {
            VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
            0,
            memorySize / 3,
            memoryTypeIndex
    };

    //memory for first input data
    VkDeviceMemory inputMemory1;
    result = vkAllocateMemory(*(task->_getDevice()->getVkDevice()), &memoryAllocateInfo, nullptr, &inputMemory1);
    if(result != VK_SUCCESS)
        throw Exception("Failed to allocate memory on device");
    int32_t *payload;
    result = vkMapMemory(*(task->_getDevice()->getVkDevice()), inputMemory1, 0, memorySize / 3, 0, (void **) &payload);
    if(result != VK_SUCCESS)
        throw Exception("Failed to map memory for first input buffer");
    memcpy(payload, task->_getTaskBuffers().in_buffer1, bufferLength);
    vkUnmapMemory(*(task->_getDevice()->getVkDevice()), inputMemory1);

    //memory for second input data
    VkDeviceMemory inputMemory2;
    result = vkAllocateMemory(*(task->_getDevice()->getVkDevice()), &memoryAllocateInfo, nullptr, &inputMemory2);
    if(result != VK_SUCCESS)
        throw Exception("Failed to allocate memory on device");
    result = vkMapMemory(*(task->_getDevice()->getVkDevice()), inputMemory2, 0, memorySize / 3, 0, (void **) &payload);
    if(result != VK_SUCCESS)
        throw Exception("Failed to map memory for first input buffer");
    memcpy(payload, task->_getTaskBuffers().in_buffer1, bufferLength);
    vkUnmapMemory(*(task->_getDevice()->getVkDevice()), inputMemory2);

    //memory with results
    VkDeviceMemory outputMemory;
    result = vkAllocateMemory(*(task->_getDevice()->getVkDevice()), &memoryAllocateInfo, nullptr, &outputMemory);
    if(result != VK_SUCCESS)
        throw Exception("Failed to allocate memory on device");

    m_spLastTaskOutMemory = std::make_shared<VkDeviceMemory>(outputMemory);

    //creating memory buffers
    VkBufferCreateInfo bufferCreateInfo = {
            VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO, 0, 0, bufferSize / 3, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT,
            VK_SHARING_MODE_EXCLUSIVE, 1, &m_queueFamilyIndex
    };
    VkBuffer in_buffer1;
    result = vkCreateBuffer(*(task->_getDevice()->getVkDevice()), &bufferCreateInfo, 0, &in_buffer1);
    if(result != VK_SUCCESS)
        throw Exception("Failed to create VkBuffer for first set of input data");
    result = vkBindBufferMemory(*(task->_getDevice()->getVkDevice()), in_buffer1, inputMemory1, 0);
    if(result != VK_SUCCESS)
        throw Exception("Failed to bind device memory to buffer");

    VkBuffer in_buffer2;
    result = vkCreateBuffer(*(task->_getDevice()->getVkDevice()), &bufferCreateInfo, 0, &in_buffer2);
    if(result != VK_SUCCESS)
        throw Exception("Failed to create VkBuffer for second set of input data");
    result = vkBindBufferMemory(*(task->_getDevice()->getVkDevice()), in_buffer2, inputMemory2, 0);
    if(result != VK_SUCCESS)
        throw Exception("Failed to bind device memory to buffer");

    VkBuffer out_buffer;
    result = vkCreateBuffer(*(task->_getDevice()->getVkDevice()), &bufferCreateInfo, 0, &out_buffer);
    if(result != VK_SUCCESS)
        throw Exception("Failed to create VkBuffer for output data");
    result = vkBindBufferMemory(*(task->_getDevice()->getVkDevice()), out_buffer, outputMemory, 0);
    if(result != VK_SUCCESS)
        throw Exception("Failed to bind device memory to output buffer");

    VkDescriptorBufferInfo input1BufferInfo = {
            in_buffer1, 0, VK_WHOLE_SIZE
    };

    VkDescriptorBufferInfo input2BufferInfo = {
            in_buffer2, 0, VK_WHOLE_SIZE
    };

    VkDescriptorBufferInfo outputBufferInfo = {
            out_buffer, 0, VK_WHOLE_SIZE
    };

    VkWriteDescriptorSet writeDescriptorSets[3] = {
            {VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET, 0, descriptorSet, 0, 0, 1,
                    VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 0, &input1BufferInfo, 0},
            {VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET, 0, descriptorSet, 1, 0, 1,
                    VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 0, &input2BufferInfo, 0},
            {VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET, 0, descriptorSet, 2, 0, 1,
                    VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 0, &outputBufferInfo, 0}
    };
    vkUpdateDescriptorSets(*(task->_getDevice()->getVkDevice()), 3, writeDescriptorSets, 0, 0);

    VkCommandPoolCreateInfo commandPoolCreateInfo = {
            VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO, 0, 0, m_queueFamilyIndex
    };
    VkCommandPool commandPool;
    result = vkCreateCommandPool(*(task->_getDevice()->getVkDevice()), &commandPoolCreateInfo, 0, &commandPool);
    if(result != VK_SUCCESS)
        throw Exception("Failed to create command pool");

    VkCommandBufferAllocateInfo commandBufferAllocateInfo = {
            VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO, 0, commandPool, VK_COMMAND_BUFFER_LEVEL_PRIMARY, 1
    };
    VkCommandBuffer commandBuffer;
    result = vkAllocateCommandBuffers(*(task->_getDevice()->getVkDevice()), &commandBufferAllocateInfo, &commandBuffer);
    if(result != VK_SUCCESS)
        throw Exception("Failed to allocate command buffers");

    VkCommandBufferBeginInfo commandBufferBeginInfo = {
            VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO, 0, VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT, 0
    };
    result = vkBeginCommandBuffer(commandBuffer, &commandBufferBeginInfo);
    if(result != VK_SUCCESS)
        throw Exception("Failed to begin command buffer");

    //pushing size of array to shader
    vkCmdPushConstants(commandBuffer, *(task->_getPipelineLayout()), VK_SHADER_STAGE_COMPUTE_BIT, 0, sizeof(uint32_t),
                       &bufferLength);

    vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE, *(task->_getPipeline()));
    vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_COMPUTE,
                            *(task->_getPipelineLayout()), 0, 1, &descriptorSet, 0, 0);

    vkCmdDispatch(commandBuffer, 1, 1, 1);

    VkSubmitInfo submitInfo = {VK_STRUCTURE_TYPE_SUBMIT_INFO, 0, 0, 0, 0, 1, &commandBuffer, 0, 0};
    vkQueueSubmit(*m_spQueue, 1, &submitInfo, 0);
}

TaskResult Runner::getLastTaskResult() {
    vkQueueWaitIdle(*m_spQueue);
    TaskResult taskResult;
    int32_t *payload;
    uint32_t memorySize = m_spLastTask->_getTaskBuffers().buffer_size * sizeof(int32_t);
    VkResult result = vkMapMemory(*(m_spLastTask->_getDevice()->getVkDevice()),
                                  *m_spLastTaskOutMemory, 0, memorySize / 3, 0, (void **) &payload);
    if(result != VK_SUCCESS)
        throw Exception("Failed to map output device memory");

    memcpy(taskResult.out_buffer, payload, memorySize);
    taskResult.buffer_size = m_spLastTask->_getTaskBuffers().buffer_size;
    return taskResult;
}

Task Runner::createTaskForShader(const VerifiedShader& shader) const
{
    return Task(shader.getDevice(), shader);
}
