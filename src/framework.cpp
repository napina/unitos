/*=============================================================================

Copyright (c) 2010 Ville Ruusutie

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is furnished
to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
IN THE SOFTWARE.

=============================================================================*/
#include "unitos/unitos.h"

namespace unitos {

Framework::Framework()
    : suiteCount(0)
    , outputCount(0)
{
}

Framework::~Framework()
{
}

void Framework::RunAllTests()
{
    *this << unitos::String("========== Running Unit Tests =========\n");

    __int64 startTime = unitos::getSystemTime();
    int testedCount = 0;
    int passedCount = 0;
    for(int i = 0; i < this->suiteCount; ++i) {
        Suite* suite = this->suites[i];
        suite->RunTests();
        testedCount += suite->TestedCount();
        passedCount += suite->PassedCount();
    }
    __int64 endTime = unitos::getSystemTime();

    *this << unitos::String("========== End of Unit Tests ==========\n");
    if(testedCount != passedCount) {
        unitos::String message(128);
        message << "   ";
        message << passedCount;
        message << " / ";
        message << testedCount;
        message << " tests passed in time ";
        message << ((endTime - startTime) / 1000000);
        message << "s\n";
        message.Terminate();
        *this << message;
    } else {
        unitos::String message(128);
        message << "  all ";
        message << passedCount;
        message << " tests passed in time ";
        message << ((endTime - startTime) / 1000000);
        message << "s\n";
        message.Terminate();
        *this << message;
    }
    *this << unitos::String("=======================================\n");
}

void Framework::RunSuiteTests(char const* name)
{
    unitos::Suite* suite = FindSuite(name);
    if(suite) {
        suite->RunTests();
    }
}
    
void Framework::RegisterOutput(unitos::Output* output)
{
    this->outputs[this->outputCount] = output;
    ++(this->outputCount);
}

void Framework::RegisterSuite(unitos::Suite* suite)
{
    // todo better list
    this->suites[this->suiteCount] = suite;
    ++(this->suiteCount);
}
    
unitos::Suite* Framework::FindSuite(char const* name)
{
    for(int i = 0; i < this->suiteCount; ++i) {
        /*if(strcmp(this->suites[i]->GetName(), name) == 0) */{
            return this->suites[i];
        }
    }
    return 0;
}
    
void Framework::operator<<(String const& text)
{
    for(int i = 0; i < this->outputCount; ++i) {
        *(this->outputs[i]) << text;
    }
}

Framework& Framework::Get()
{
    static Framework framework;
    return framework;
}

SuiteRegistrator::SuiteRegistrator(unitos::Suite* suite)
{
    Framework::Get().RegisterSuite(suite);
}

}
