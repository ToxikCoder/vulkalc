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
 * \file Sample.cpp
 * \brief 
 * \author Lev Sizov
 * \date 05.06.2017
 */

#include <Application.hpp>

using namespace Vulkalc;
using namespace std;

int main()
{
    //creating and configuring Application
    Application* application = new Application();
    SharedConfiguration configuration = application->getConfigurator()->getConfiguration();
    configuration->isErrorLoggingEnabled = false;
    configuration->applicationName = "Vulkalc sample";
    shared_ptr<stringstream> ss = make_shared<stringstream>();
    configuration->logStream = ss;
    application->configure(false);
    //choosing device
    auto devices = application->enumeratePhysicalDevices();
    application->setPhysicalDevice(devices[0]);
    //compiling shaders
    SharedShaderProvider shaderProvider = application->getShaderProvider();
    vector<Shader> shaders = shaderProvider->loadShaders("../shaders/");
    vector<VerifiedShader> verifiedShaders = shaderProvider->tryCompileShaders(shaders);
    SharedTask task = make_shared<Task>(application->getRunner()->createTaskForShader(verifiedShaders[0]));
    //settings data
    Task::TaskBuffers buffer;
    buffer.buffer_size = 5;
    int32_t array1[5] = {0, 1, 2, 3, 4};
    int32_t array2[5] = {5, 6, 7, 8, 9};
    buffer.in_buffer1 = array1;
    buffer.in_buffer2 = array2;
    task->setData(buffer);
    //running task
    application->getRunner()->queueTask(task);
    //getting task
    TaskResult result = application->getRunner()->getLastTaskResult();
    for(uint32_t i = 0; i < result.buffer_size; ++i)
        cout << result.out_buffer[i] << " ";
    cout << endl;
    devices.clear();
    configuration.reset();
    delete application;
    return 0;
}
