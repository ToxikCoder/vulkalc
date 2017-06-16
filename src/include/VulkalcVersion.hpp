/*!
 * \file VulkalcVersion.hpp
 * \brief This file contains Vulkalc version macros declarations
 * \author Lev Sizov
 * \date 08.06.2017
 */

#ifndef VULKALC_LIBRARY_VULKALCVERSION_H
#define VULKALC_LIBRARY_VULKALCVERSION_H

/*!
 * Major version of Vulkalc
 */
#define VULKALC_MAJOR_VERSION 0

/*!
 * Minor version of Vulkalc
 */
#define VULKALC_MINOR_VERSION 1

/*!
 * Patch version of Vulkalc
 */
#define VULKALC_PATCH_VERSION 2
#ifdef __MINGW32_VERSION
/*!
 * This Vulkalc version macros declaration is specific for MinGW and contains full semantic version as a string
 */
#define VULKALC_VERSION "0.1.2"
#endif

#endif //VULKALC_LIBRARY_VULKALCVERSION_H
