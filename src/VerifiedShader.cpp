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
 * \file VerifiedShader.cpp
 * \brief This file contains VerifiedShader class definition
 * \author Lev Sizov
 * \date 05.06.2017
 */

#include <cstdlib>
#include <fstream>
#include "include/VerifiedShader.hpp"

using namespace Vulkalc;


VerifiedShader::VerifiedShader(const SharedDevice& device, const Shader& shader) : m_shader(shader)
{
    m_spDevice = device;
    VkShaderModule shaderModule;
    m_spVkShaderModule = std::make_shared<VkShaderModule>(shaderModule);
}

VerifiedShader::~VerifiedShader()
{
    if(m_spVkShaderModule) {
        VkShaderModule module = *m_spVkShaderModule;
        m_spVkShaderModule.reset();
        vkDestroyShaderModule(*(m_spDevice->getVkDevice()), module, 0);
    }

    if(m_spDevice)
        m_spDevice.reset();
}

bool VerifiedShader::_tryCompile()
{
    std::string compileCommand =
            "glslangValidator -V " + m_shader.getShaderFullName() + " " + m_shader.getShaderFullName() + ".spv";
    std::system(compileCommand.c_str());
    std::ifstream shaderFile;
    shaderFile.open(m_shader.getShaderFullName(), std::ios::binary | std::ios::in | std::ios::ate);
    if(!shaderFile.is_open())
    {
        m_isCompiled = false;
        return m_isCompiled;
    }

    size_t size = shaderFile.tellg();
    shaderFile.seekg(0, std::ios::beg);
    char* code = new char[size];
    shaderFile.read(code, size);
    shaderFile.close();

    VkShaderModuleCreateInfo createInfo;
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.pNext = nullptr;
    createInfo.flags = 0;
    createInfo.codeSize = size;
    createInfo.pCode = (uint32_t*) code;

    VkShaderModule module;
    VkResult result = vkCreateShaderModule(*(m_spDevice->getVkDevice()), &createInfo, nullptr, &module);
    if(result == VK_SUCCESS)
    {
        m_isCompiled = true;
        m_spVkShaderModule = std::make_shared<VkShaderModule>(module);
    }

    delete[] code;

    return m_isCompiled;
}
