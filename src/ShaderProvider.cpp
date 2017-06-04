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
 * \file ShaderProvider.cpp
 * \brief 
 * \author Lev Sizov
 * \date 04.06.2017
 */

#include "include/ShaderProvider.hpp"
#include <sstream>
#include <fstream>

using namespace Vulkalc;


std::vector<Shader> ShaderProvider::loadShaders(const char* directory)
{
    std::vector<Shader> shaders;
    return std::vector<Shader>();
}

std::vector<VerifiedShader> ShaderProvider::compileShaders(const std::vector<Shader>& shaders)
{
    return std::vector<VerifiedShader>();
}

ShaderProvider::ShaderProvider()
{

}

ShaderProvider::~ShaderProvider()
{

}

std::vector<std::string> ShaderProvider::_discoverShaders(const char* directory)
{
    std::vector<std::string> shaderNames;
#ifdef _MSC_VER
    std::stringstream ss;
    //listing file names in directory to file
    ss << "dir \"" << directory << "\" /b > files";
    std::string command;
    getline(ss, command);
    std::system(command.c_str());
    //reading files
    std::ifstream file = std::ifstream("files");
    std::string buf;
    while (!file.eof())
    {
        std::getline(file, buf);
        int extPos = buf.find(".comp");
        if (extPos != std::string::npos)
        {
            //check that ".comp" is extension, not part of the name
            std::string fileName = buf.substr(0, extPos); //it should be name, without extension
            fileName.append(".comp"); //if buf is test.comp.test, then fileName will be test.comp
            if (fileName == buf) //and this check will fail
                shaderNames.push_back(buf);
        }
    }
    file.close();
    std::system("del test");
#else

#endif
    return shaderNames;
}


