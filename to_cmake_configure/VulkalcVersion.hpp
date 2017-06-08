/*!
 * \file VulkalcVersion.hpp
 * \brief 
 * \author Lev Sizov
 * \date 08.06.2017
 */

#ifndef VULKALC_LIBRARY_VULKALCVERSION_H
#define VULKALC_LIBRARY_VULKALCVERSION_H

#define VULKALC_MAJOR_VERSION @VULKALC_MAJOR@
#define VULKALC_MINOR_VERSION @VULKALC_MINOR@
#define VULKALC_PATCH_VERSION @VULKALC_PATCH@
#ifdef __MINGW32_VERSION
#define VULKALC_VERSION "@VULKALC_MAJOR@.@VULKALC_MINOR@.@VULKALC_PATCH@"
#endif

#endif //VULKALC_LIBRARY_VULKALCVERSION_H
