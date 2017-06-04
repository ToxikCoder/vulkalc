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

using namespace Vulkalc;
using namespace std;

TEST_CASE("Application doesn't throw anything on init()")
{
	Application* application = nullptr;
    REQUIRE_NOTHROW(application = new Application());
	delete application;
	application = nullptr;
}

TEST_CASE("Every Application instance is unique")
{
	Application* application = new Application();
    Application* anotherApplication = nullptr;
    REQUIRE_NOTHROW(anotherApplication = new Application());
    REQUIRE(application != anotherApplication);
    delete anotherApplication;
    anotherApplication = nullptr;
    REQUIRE(application != nullptr);
	delete application;
    application = nullptr;
}

TEST_CASE("Application is initialized")
{
	Application* application = new Application();
	SECTION("Application is initialized when created")
	{
		REQUIRE(application->isApplicationInitialized());
		REQUIRE(application->getConfigurator() != nullptr);
	}
	SECTION("Configurator, Configuration are created on init()")
	{
		REQUIRE(application->getConfigurator() != nullptr);
		REQUIRE(application->getConfigurator()->getConfiguration() != nullptr);
	}
	SECTION("Calling log throws exception")
	{
		REQUIRE_THROWS_AS(application->log("test", Application::LOG_INFO), ApplicationNotConfiguredException);
	}
	SECTION("Initialized Application is destroyed without exceptions")
	{
		REQUIRE_NOTHROW(delete application);
        application = nullptr; //-V773
	}
}

TEST_CASE("Application is configured")
{
	Application* application = new Application();
    shared_ptr<stringstream> ss = make_shared<stringstream>();
    SharedConfiguration configuration = application->getConfigurator()->getConfiguration();
    configuration->logStream = ss;
	configuration->errorStream = ss;
    SECTION("Calling configure() doesn't throw exception")
    {
        REQUIRE_NOTHROW(application->configure(false));
        REQUIRE(application->isApplicationConfigured());
    }
	SECTION("Streams are not NULL after configuring")
	{
        application->configure(false);
		REQUIRE(application->getLoggingStream() != nullptr);
		REQUIRE(application->getErrorStream() != nullptr);
	}
    SECTION("Configured Application doesn't throw exceptions")
    {
        application->configure(false);
        REQUIRE_NOTHROW(application->log("Test", Application::LOG_INFO));
    }
    SECTION("Calling log() on configured Application writes to stream")
    {
        application->configure(false);
		application->log("Test", Application::LOG_INFO);
        string stream_content;
        getline(*ss, stream_content);
        REQUIRE(!stream_content.empty());
        REQUIRE(stream_content != "Test");
		string str = stream_content.substr(0, 35);
        REQUIRE(str == "Vulkalc Application from Vulkalc at");
    }
    SECTION("Resetting Configuration resets Configuration")
    {
        configuration.reset();
        application->getConfigurator()->resetConfiguration();
        configuration = application->getConfigurator()->getConfiguration();
        REQUIRE(configuration->logStream == nullptr);
        REQUIRE(configuration->errorStream == nullptr);
    }
    SECTION("Calling configure(false) doesn't change configuration")
    {
        configuration->logStream = ss;
        configuration->errorStream = ss;
        application->configure(false);
        configuration->logStream.reset();
        application->configure(false);
        REQUIRE(application->getLoggingStream() != nullptr);
    }
    SECTION("Calling configure(true) changes configuration")
    {
        configuration->logStream = ss;
        configuration->errorStream = ss;
        application->configure(false);
        configuration->logStream.reset();
        configuration->errorStream.reset();
        application->configure(true);
        REQUIRE(application->getLoggingStream() == nullptr);
        REQUIRE(application->getErrorStream() == nullptr);
    }
	SECTION("Configured Application is safely destroyed")
	{
        application->configure(false);
		REQUIRE_NOTHROW(delete application);
	}
    configuration.reset();
    application = nullptr; //-V773
    ss.reset();
}

//This test expects at least one GPU to be installed
TEST_CASE("Creating Device")
{
    Application* application = new Application();
    SharedConfiguration configuration = application->getConfigurator()->getConfiguration();
    shared_ptr<stringstream> ss = make_shared<stringstream>();
    configuration->logStream = ss;
    configuration->errorStream = ss;
    application->configure(false);
    std::vector<SharedPhysicalDevice> devices = application->enumeratePhysicalDevices();
    REQUIRE(devices.size() != 0);
    for(uint32_t i = 0; i < devices.size(); ++i)
    {
        cout << "Device " << i << ": " << devices[i]->getDeviceName() << endl;
    }
    REQUIRE_NOTHROW(application->setPhysicalDevice(devices[0]));
    REQUIRE(application->getVkDevice() != nullptr);
    devices.clear();
    ss.reset();
    configuration.reset();
    delete application;
}
