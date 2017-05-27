#
# MIT License
#
# Copyright (c) 2017 Lev Sizov a.k.a "ToxikCoder"
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#

project(vulkalc-doc)

find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(DOC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
    set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)
    configure_file(${ROOT_DIR}/GeneratedDoxyfile ${DOC_DIR} COPYONLY)
    configure_file(${ROOT_DIR}/README.MD ${DOC_DIR} COPYONLY)

    if(VULKALCDOC_GENERATE_HTML)
        file(APPEND ${DOC_DIR}/GeneratedDoxyfile "GENERATE_HTML          = YES\n")
    endif(VULKALCDOC_GENERATE_HTML)
    if(VULKALCDOC_GENERATE_PDF)
        file(APPEND ${DOC_DIR}/GeneratedDoxyfile "GENERATE_PDF          = YES\n")
    endif(VULKALCDOC_GENERATE_PDF)
    if(VULKALCDOC_GENERATE_LATEX)
        file(APPEND ${DOC_DIR}/GeneratedDoxyfile "GENERATE_LATEX          = YES\n")
    endif(VULKALCDOC_GENERATE_LATEX)
    if(VULKALCDOC_GENERATE_MAN)
        file(APPEND ${DOC_DIR}/GeneratedDoxyfile "GENERATE_MAN          = YES\n")
    endif(VULKALCDOC_GENERATE_MAN)
    if(VULKALCDOC_GENERATE_RTF)
        file(APPEND ${DOC_DIR}/GeneratedDoxyfile "GENERATE_RTF          = YES\n")
    endif(VULKALCDOC_GENERATE_RTF)
    add_custom_target(doc COMMAND ${DOXYGEN_EXECUTABLE} ${DOC_DIR}/GeneratedDoxyfile
            WORKING_DIRECTORY ${ROOT_DIR})
else()
    message(FATAL_ERROR "Doxygen is required to build documentation")
endif(DOXYGEN_FOUND)