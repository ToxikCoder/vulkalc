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
#include "Device.hpp"
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
        VerifiedShader()
        {};

        /*!
         * VerifiedShader constructor
         * \param shader Shader to verify and compile
         *
         * Creating object with this constructor calls glslangValidator to try and compile specified shader.
         * If compilation was successful, isCompiled would return true
         */
        explicit VerifiedShader(const SharedDevice& device, const Shader& shader);

        /*!
         * Checks if bind shader is successfully compiled and ready to use
         * \return is shader compiled
         */
        bool isCompiled() const
        { return m_isCompiled; };

        /*!
         * \brief Returns VkShaderModule, created from compiled shader
         * \return shared pointer to VkShaderModule
         */
        const SharedShaderModule getVkShaderModule() const
        { return m_spVkShaderModule; };

        /*!
         * \brief Returns bound Shader, which should be verified
         * \return binded Shader
         */
        const Shader& getBoundShader() const
        { return m_shader; };

        /*!
         * \copydoc Shader::getShaderName()
         * \return string containing shader name
         */
        std::string getShaderName() const
        { return m_shader.getShaderName(); };

        /*!
         * \copydoc Shader::getShaderPath()
         * \return string containing path to shader
         */
        std::string getShaderPath() const
        { return m_shader.getShaderPath(); };

        /*!
         * \copydoc Shader::getShaderFullName()
         * \return string containing full path to shader
         */
        std::string getShaderFullName() const
        { return m_shader.getShaderFullName(); };

        /*!
         * \brief VerifiedShader destructor
         */
        virtual ~VerifiedShader();

    private:
        friend class ShaderProvider;

        bool _tryCompile(const SharedDevice device);

        bool m_isCompiled = false;
        SharedDevice m_spDevice;
        SharedShaderModule m_spVkShaderModule;
        Shader m_shader;
    };
}

#endif //VULKALC_LIBRARY_VERIFIEDSHADER_H
