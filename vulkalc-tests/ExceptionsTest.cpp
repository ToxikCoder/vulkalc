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

#include <Exceptions.hpp>
#include "catch.hpp"
#include <cstring>

using namespace Vulkalc;
using namespace std;

TEST_CASE("Exception message is concatenated")
{
    try
    {
        throw Exception("test");
    }
    catch(Exception& e)
    {
        REQUIRE(strcmp(e.what(), "Exception in Vulkalc Application: test") == 0);
    }
}

TEST_CASE("Exception messages are polymorphic")
{
    SECTION("ApplicationNotInitializedException")
    {
        try
        {
            throw ApplicationNotInitializedException();
        }
        catch(ApplicationNotInitializedException& e)
        {
            REQUIRE(strcmp(e.what(), "ApplicationNotInitializedException in Vulkalc Application: "
                    "An instance of Application is not initialized. Call Application::init() first"));
        }
    }

    SECTION("ApplicationNotConfiguredException")
    {
        try
        {
            throw ApplicationNotConfiguredException();
        }
        catch(ApplicationNotConfiguredException& e)
        {
            REQUIRE(strcmp(e.what(), "ApplicationNotConfiguredException in Vulkalc Application: "
                    "An instance of Application is not configured. "
                    "Edit Configuration instance, then call Application::configure()"));
        }
    }

    SECTION("HostMemoryAllocationException")
    {
        try
        {
            throw HostMemoryAllocationException();
        }
        catch(HostMemoryAllocationException& e)
        {
            REQUIRE(strcmp(e.what(), "Failed to allocate memory in host application") == 0);
        }
        try
        {
            throw HostMemoryAllocationException("test");
        }
        catch(HostMemoryAllocationException& e)
        {
            REQUIRE(strcmp(e.what(), "Failed to allocate memory in host application: test"));
        }
    }
}
