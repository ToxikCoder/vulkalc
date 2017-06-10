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

#ifdef __GNUC__

#include <dirent.h>

#endif

using namespace Vulkalc;

std::vector<Shader> ShaderProvider::loadShaders(const char* directory) const
{
    std::vector<std::string> shaderNames = _discoverShaders(directory);
    std::vector<Shader> shaders = std::vector<Shader>(shaderNames.size());
    for(std::string name : shaderNames)
    {
        Shader shader(name, directory);
        shaders.push_back(shader);
    }

    return shaders;
}

std::vector<VerifiedShader>
ShaderProvider::tryCompileShaders(const std::vector<Shader>& shaders) const
{
    std::vector<VerifiedShader> verifiedShaders = std::vector<VerifiedShader>(shaders.size());
    for(Shader shader : shaders)
    {
        VerifiedShader verifiedShader = this->tryCompile(shader);
        verifiedShaders.push_back(verifiedShader);
    }
    return verifiedShaders;
}

std::vector<std::string> ShaderProvider::_discoverShaders(const char* directory) const
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
        if(checkFileNameExtension(buf, ".comp"))
            shaderNames.push_back(buf);
    }
    file.close();
    std::system("del test");
#else
    DIR* d;
    struct dirent* dir;
    d = opendir(directory);
    if(d)
    {
        while((dir = readdir(d)) != NULL)
        {
            std::string fileName = dir->d_name;
            if(checkFileNameExtension(fileName, ".comp"))
                shaderNames.push_back(fileName);
        }

        closedir(d);
    }
#endif
    return shaderNames;
}

VerifiedShader ShaderProvider::tryCompile(const Shader shader) const
{
    VerifiedShader verifiedShader(m_spDevice, shader);
    verifiedShader._tryCompile();
    return verifiedShader;
}


