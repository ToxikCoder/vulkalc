/*
* MIT License
*
* Copyright (c) 2017 Lev Sizov a.k.a "ToxikCoder"
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
 * \file Configurator.h
 * \brief This file contains Configurator class declaration
 * \author Lev Sizov
 * \date 30.05.2017
 */

#ifndef VULKALC_LIBRARY_CONFIGURATOR_H
#define VULKALC_LIBRARY_CONFIGURATOR_H

#include "Export.hpp"
#include "Configuration.hpp"

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
     */
    class VULKALC_API Configurator
    {
    public:
        inline const Configuration* getConfiguration() { return m_spConfiguration; };

        Configurator();

        ~Configurator();

    private:
        Configuration* m_spConfiguration;
    };
}


#endif //VULKALC_LIBRARY_CONFIGURATOR_H
