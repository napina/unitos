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
//----------------------------------------------------------------------------

namespace unitos {

Framework::Framework()
    : m_suiteCount(0)
    , m_outputCount(0)
{
}
//----------------------------------------------------------------------------

Framework::~Framework()
{
}
//----------------------------------------------------------------------------

void Framework::runAllTests()
{
    *this << unitos::String("========== Running Unit Tests =========\n");

    int64_t startTime = unitos::getSystemTime();
    int testedCount = 0;
    int passedCount = 0;
    for(int i = 0; i < m_suiteCount; ++i) {
        Suite* suite = m_suites[i];
        suite->runTests();
        testedCount += suite->testedCount();
        passedCount += suite->passedCount();
    }
    int64_t endTime = unitos::getSystemTime();

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
        message.terminate();
        *this << message;
    } else {
        unitos::String message(128);
        message << "  all ";
        message << passedCount;
        message << " tests passed in time ";
        message << ((endTime - startTime) / 1000000);
        message << "s\n";
        message.terminate();
        *this << message;
    }
    *this << unitos::String("=======================================\n");
}
//----------------------------------------------------------------------------

void Framework::runSuiteTests(char const* name)
{
    unitos::Suite* suite = findSuite(name);
    if(suite) {
        suite->runTests();
    }
}
//----------------------------------------------------------------------------

void Framework::registerOutput(unitos::Output* output)
{
    m_outputs[m_outputCount] = output;
    ++m_outputCount;
}
//----------------------------------------------------------------------------

void Framework::registerSuite(unitos::Suite* suite)
{
    // todo better list
    m_suites[m_suiteCount] = suite;
    ++m_suiteCount;
}
//----------------------------------------------------------------------------

unitos::Suite* Framework::findSuite(char const* name)
{
    for(int i = 0; i < m_suiteCount; ++i) {
        if(unitos::compare(m_suites[i]->getName(), name) == 0) {
            return m_suites[i];
        }
    }
    return nullptr;
}
//----------------------------------------------------------------------------

void Framework::operator<<(String const& text)
{
    for(int i = 0; i < m_outputCount; ++i) {
        *(m_outputs[i]) << text;
    }
}
//----------------------------------------------------------------------------

Framework& Framework::get()
{
    static Framework framework;
    return framework;
}
//----------------------------------------------------------------------------

SuiteRegistrator::SuiteRegistrator(unitos::Suite* suite)
{
    Framework::get().registerSuite(suite);
}
//----------------------------------------------------------------------------

} // end of unitos
