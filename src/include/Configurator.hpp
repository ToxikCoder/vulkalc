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
 * \file Configurator.hpp
 * \brief This file contains Configurator class declaration
 * \author Lev Sizov
 * \date 30.05.2017
 */

#pragma once

#ifndef VULKALC_LIBRARY_CONFIGURATOR_H
#define VULKALC_LIBRARY_CONFIGURATOR_H

#include "Export.hpp"
#include "Configuration.hpp"
#include "Exceptions.hpp"

/*!
 * \copydoc Vulkalc
 */
namespace Vulkalc
{
    /*!
     * \class Configurator
     * \extends RAII
     * \brief Configurator class for configuring Application with Configuration.
     * \warning This class is not thread-safe.
     * \warning Do not create or destroy Configurator object by hands
     */
    class VULKALC_API Configurator
    {
    public:
        /*!
         * \brief Returns constant shared pointer to Configuration
         * \return constant shared pointer to Configuration
         */
        const SharedConfiguration getConfiguration() { return m_spConfiguration; };

        /*!
         * \brief Resets Configuration to default values
         */
        inline void resetConfiguration()
        {
            m_spConfiguration.reset();
            m_spConfiguration = std::make_shared<Configuration>();
        }

        /*!
         * \brief Configurator constructor
         * \throws HostHostMemoryAllocationException - thrown if failed to allocate memory in heap for Configuration
         */
        Configurator()
        {
            try
            {
                m_spConfiguration = std::make_shared<Configuration>();
            }
            catch(std::bad_alloc&)
            {
                throw HostMemoryAllocationException("Failed to allocate Configuration in Configurator");
            }
        };

        ~Configurator()
        {
            if (m_spConfiguration)
            {
                m_spConfiguration.reset();
                m_spConfiguration = nullptr;
            }
        };
    private:
        SharedConfiguration m_spConfiguration;
    };

    typedef std::shared_ptr<Configurator> SharedConfigurator;
}


#endif //VULKALC_LIBRARY_CONFIGURATOR_H
