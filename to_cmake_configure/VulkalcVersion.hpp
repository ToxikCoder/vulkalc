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
#define VULKALC_MAJOR_VERSION @VULKALC_MAJOR@

/*!
 * Minor version of Vulkalc
 */
#define VULKALC_MINOR_VERSION @VULKALC_MINOR@

/*!
 * Patch version of Vulkalc
 */
#define VULKALC_PATCH_VERSION @VULKALC_PATCH@
#ifdef __MINGW32_VERSION
/*!
 * This Vulkalc version macros declaration is specific for MinGW and contains full semantic version as a string
 */
#define VULKALC_VERSION "@VULKALC_MAJOR@.@VULKALC_MINOR@.@VULKALC_PATCH@"
#endif

#endif //VULKALC_LIBRARY_VULKALCVERSION_H
