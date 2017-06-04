/*!
 * \file Shader
 * \brief 
 * \author whyami
 * \date 02.06.2017
 *
 * 
 */

#pragma once

#ifndef VULKALC_LIBRARY_SHADER_H
#define VULKALC_LIBRARY_SHADER_H

#include "Export.hpp"
#include <string>

namespace Vulkalc
{
    class VULKALC_API Shader
    {
    public:
        Shader(std::string name, std::string path);

        virtual ~Shader();
    private:

    };
}

#endif //VULKALC_LIBRARY_SHADER_H
