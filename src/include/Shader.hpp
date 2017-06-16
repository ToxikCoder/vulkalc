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
 * \file Shader.hpp
 * \brief Contains Shader class
 * \author Lev Sizov
 * \date 02.06.2017
 */

#pragma once

#ifndef VULKALC_LIBRARY_SHADER_H
#define VULKALC_LIBRARY_SHADER_H

#include "Export.hpp"
#include <string>

namespace Vulkalc
{
    /*!
     * \class Shader
     * \brief Shader class represents 1 compute shader on disk in specified directory
     *
     * Shader objects are created by calling ShaderProvider::loadShaders(). Do not use contructors
     */
    class VULKALC_API Shader
    {
    public:

        /*!
         * Default Shader constructor. Do not use it to create Shader object, use ShaderProvider::loadShaders().
         */
        Shader() {};

        /*!
         * Shader constructor. Do not use it to create Shader object, use ShaderProvider::loadShaders()
         * \param name name of shader file
         * \param path path to shader file
         */
        Shader(const std::string& name, const std::string& path);

        /*!
         * Returns shader name
         * \return string containing shader name
         */
        std::string getShaderName() const { return m_name; }

        /*!
         * Returns path to shader
         * \return string containing path to shader
         */
        std::string getShaderPath() const { return m_path; }

        /*!
         * Returns full path to shader
         * \return string containing full path to shader
         */
        std::string getShaderFullName() const;

        /*!
         * Shader destructor
         */
        virtual ~Shader() {};

    private:
        std::string m_name;
        std::string m_path;

    };
}

#endif //VULKALC_LIBRARY_SHADER_H
