/*!
 * \file VerifiedShader.hpp
 * \brief Contains VerifiedShader class declaration
 * \author Lev Sizov
 * \date 02.06.2017
 */

#pragma once

#ifndef VULKALC_LIBRARY_VERIFIEDSHADER_H
#define VULKALC_LIBRARY_VERIFIEDSHADER_H

#include "Export.hpp"
#include "Utilities.hpp"
#include "Shader.hpp"
#include <vulkan/vulkan.h>

/*!
 * \copydoc Vulkalc
 */
namespace Vulkalc
{
    /*!
     * \class VerifiedShader
     * \brief Represents compiled compute shader
     */
    class VULKALC_API VerifiedShader
    {
    public:
        /*!
         * VerifiedShader constructor
         * \param shader Shader to verify and compile
         *
         * Creating object with this constructor calls glslangValidator to try and compile specified shader.
         * If compilation was successful, isCompiled would return true
         */
        VerifiedShader(const Shader& shader);

        /*!
         * Checks if bind shader is successfully compiled and ready to use
         * \return is shader compiled
         */
        bool isCompiled() const { return m_isCompiled; };

        /*!
         * \brief VerifiedShader destructor
         */
        virtual ~VerifiedShader();

    private:
        bool m_isCompiled = false;
        SharedShaderModule m_spVkShaderModule;

        VerifiedShader() {};
    };
}

#endif //VULKALC_LIBRARY_VERIFIEDSHADER_H
