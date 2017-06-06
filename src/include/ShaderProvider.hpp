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
 * \file ShaderProvider.h
 * \brief This file contains ShaderProvider class declaration
 * \author Lev Sizov
 * \date 02.06.2017
 */

#pragma once

#ifndef VULKALC_LIBRARY_SHADERPROVIDER_H
#define VULKALC_LIBRARY_SHADERPROVIDER_H

#include "Export.hpp"
#include "Shader.hpp"
#include "VerifiedShader.hpp"
#include <vector>
#include <string>

/*!
 * \copydoc Vulkalc
 */
namespace Vulkalc
{
    /*!
     * \class ShaderProvider
     * \brief Provides interface for loading and compiling shaders from disk
     */
    class VULKALC_API ShaderProvider
    {
    public:
        /*!
         * \brief Loads compute shaders from directory
         * \param directory where to search shaders
         * \return loaded compute shaders
         */
        std::vector<Shader> loadShaders(const char* directory = "shaders") const;

        /*!
         * \brief Tries to compile provided shaders with glslangValidator from Vulkan SDK
         * \param shaders list of shaders to try and compile
         * \return compiled and loaded shaders
         */
        std::vector<VerifiedShader> tryCompileShaders(const VkDevice& device, const std::vector<Shader>& shaders) const;

        /*!
         * \brief tries to compile one shader
         * \param shader shader to compile
         * \return VerifiedShader object
         */
        VerifiedShader tryCompile(const VkDevice& device, const Shader& shader) const;

        ShaderProvider();

        virtual ~ShaderProvider();

    private:
        std::vector<std::string> _discoverShaders(const char* directory) const;
    };
}

#endif //VULKALC_LIBRARY_SHADERPROVIDER_H
