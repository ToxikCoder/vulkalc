# Vulkalc

![Logo](./resources/logo.png)

[![Build status](https://travis-ci.org/ToxikCoder/vulkalc.svg?branch=stable)](https://travis-ci.org/ToxikCoder/vulkalc)
[![Build status](https://ci.appveyor.com/api/projects/status/yf76nw83o321q9pk/branch/dev?svg=true)](https://ci.appveyor.com/project/ToxikCoder/vulkalc/branch/stable)
[![Releases](http://github-release-version.herokuapp.com/github/ToxikCoder/vulkalc/release.svg?style=flat)](https://github.com/ToxikCoder/vulkalc/releases)
[![CII Best Practices](https://bestpractices.coreinfrastructure.org/projects/1015/badge)](https://bestpractices.coreinfrastructure.org/projects/1015)

**Vulkalc** is a cross-platform proof-of-concept library for easy GPU calculations with the use of **Vulkan**(developed by [Khronos Group](https://www.khronos.org/)).

**Vulkalc** eliminates the need to configure **Vulkan** manually and lets you concentrate on your calculations 
by providing C++ API for fast and easy **Vulkan** configuration.

## How to use

**This software is still under heavy development and not recommended for use yet.**

**First usable version will be available under v1.0.0 tag.**

### How to download

- Download desired version of Vulkalc as zip
- Download stable release of Vulkalc from [Releases](https://github.com/ToxikCoder/vulkalc/releases) page
- Clone desired branch with git `git clone -b stable https://github.com/ToxikCoder/vulkalc.git`

### How to build

1. **Install Vulkan SDK**

    Install Vulkan SDK, preferrably [1.0.39.1](https://vulkan.lunarg.com/sdk/download/1.0.39.1/windows/VulkanSDK-1.0.39.1-Installer.exe), 
    export `VULKAN_SDK` environment variable, add `VULKAN_SDK/bin` to `PATH`. 

    See Getting started for [Windows](https://vulkan.lunarg.com/doc/sdk/1.0.51.0/windows/getting_started.html) and
    [Linux](https://vulkan.lunarg.com/doc/sdk/1.0.51.0/linux/getting_started.html).

2. **Configure with CMake and generate project**

    Vulkalc project contains documentation, library, unit tests and sample project.
    
    - `src/` and `src/include/` - library source code and headers
    - `doc/generated` - documentation
    - `vulkalc-tests` - **Vulkalc** unit tests
    - `vulkalc-sample` - **Vulkalc** sample project
    - `shaders` - **Vulkalc** example compute shader
    
    | CMake variable | Variable meaning | Default value |
    |----------------|------------------|---------------|
    | *VULKALC_BUILD_VULKALC* | Build library or not | 1 - build library |
    | *VULKALC_BUILD_STATIC* | Static or dynamic library to build | 1 - static |
    | *VULKALC_INCLUDE_TESTS* | Add unit tests build target or  not | 1 - add target |
    | *VULKALC_INCLUDE_SAMPLE* | Add sample project build target or not | 1 - add target |
    | *VULKALC_GENERATE_DOC* | Add "generate documentatiob" target or not | 1 - add target |
    | *VULKALC_GENERATE_HTML* | Generate documentation in HTML format | 1 - generate |
    | *VULKALC_GENERATE_PDF* | Generate documentation in PDF format | 0 - do not generate |
    | *VULKALC_GENERATE_LATEX* | Generate documentation in LaTeX format | 0 - do not generate |
    | *VULKALC_GENERATE_MAN* | Generate documentation in Linux man pages format | 0 - do not generate |
    | *VULKALC_GENERATE_RTF* | Generate documentation in RTF format | 0 - do not generate |
    
    To generate project in `build` directory with dynamic library, documentation, tests and sample target run:
    
    - For Microsoft Visual Studio 2015 x64 - `cmake -DVULKALC_BUILD_STATIC=0 -G "Visual Studio 14 2015 Win64" -H. -Bbuild`
    - For MinGW - `cmake -DVULKALC_BUILD_STATIC=0 -G "MinGW Makefiles" -H. -Bbuild`
    - For  JetBrains CLion on Windows(you still should have MinGW installed) - `cmake -DVULKALC_BUILD_STATIC=0 -G "CodeBlocks - MinGW Makefiles -H. -Bbuild"`
    - For Linux - `cmake -DVULKALC_BUILD_STATIC=0 -G "Unix Makefiles" -H. -Bbuild`
    - For other options - see CMake [documentation](https://cmake.org/cmake/help/v3.0/manual/cmake-generators.7.html)

3. **Build desired targets**

    - For Microfost Visual Studio 2015 x64 - Open generated solution in `build` directory and build desired target
    - For JetBrains CLion - you don't have to generate project at all, just import project by selecting CMakeLists.txt 
    in project root, then run desired targets
    - For Linux - run make target - all, vulkalc, vulkalc-test, vulkalc-sample, doc.
    
4. **Run executables**

    In **Vulkalc** library tests and sample project are compiled and placed into corresponding directory in project directory.
    If build directory is `build`, then executables are placed in:
    
    - `build/vulkalc-sample/` -  Executable `vulkalc-sample` or `vulkalc-sample.exe` 
    - `build/vulkalc-tests` - Executable `vulkalc-test` or `vulkalc-test.exe`
    
    **P.S.** If executables are compiled with Microsoft Visual Studio, then executables are placed in Build Type directory. 
    For example, compiling vulkalc-tests in Release will put executable in `build/vulkalc-tests/Release/vulkalc-test.exe`

## Dependencies

- [Vulkan SDK](https://vulkan.lunarg.com/)
- [Catch](https://github.com/philsquared/Catch) testing framework.
- [Doxygen](http://doxygen.org) for generating documentation(optional).

## Contribution

See [Contributing](CONTRIBUTING.md)

## Authors and contributors

Author:
- Lev Sizov a.k.a. ToxikCoder

## Logo credentials

Silhouette graphic by <a href="http://www.flaticon.com/authors/ocha">ocha</a> from <a href="http://www.flaticon.com/">Flaticon</a> is licensed under <a href="http://creativecommons.org/licenses/by/3.0/" title="Creative Commons BY 3.0">CC BY 3.0</a>.

Logo is created with <a href="http://logomakr.com" title="Logo Maker">LogoMaker.com</a>