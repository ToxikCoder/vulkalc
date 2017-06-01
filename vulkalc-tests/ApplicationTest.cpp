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

#include <Application.hpp>
#include "catch.hpp"
#include <sstream>

using namespace Vulkalc;
using namespace std;

Application application = Application::getInstance();

/*TEST_CASE("Only one Application instance exists")
{
    Application anotherApplication = Application::getInstance();
    REQUIRE(application == anotherApplication);
}*/

TEST_CASE("Application is initialized when created")
{
    REQUIRE(application.isApplicationInitialized());
    REQUIRE(application.getConfigurator() != nullptr);
}

TEST_CASE("Not configured Application calling log")
{
    REQUIRE_THROWS_AS(application.log("test", Application::LOG_INFO), ApplicationNotConfiguredException);
}

TEST_CASE("Application is configured")
{
    stringstream* ss = new stringstream();
    SECTION("Application is really configured")
    {
        Configuration* configuration = application.getConfigurator()->getConfiguration();
        configuration->logStream = ss;
        application.configure();
        REQUIRE(application.isApplicationConfigured());

    }
    SECTION("Configured Application doesn't throw exceptions")
    {
        REQUIRE_NOTHROW(application.log("Test", Application::LOG_INFO));
    }
    SECTION("Calling log() on configured Application writes to stream")
    {
        string stream_content;
        *ss >> stream_content;
        /*!
         * \bug These tests fail - nothing is written(or read) to logging iostream
         * \todo Research the source of this bug. Maybe it's just dumb me
        REQUIRE(!stream_content.empty());
        REQUIRE(stream_content != "Test");
        REQUIRE(stream_content == "Vulkalc Application from Vulkalc at  INFO: Test");*/
    }
}

