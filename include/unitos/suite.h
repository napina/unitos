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
#pragma once
#ifndef unitos_suite_h
#define unitos_suite_h

#include "unitos/suitetest.h"

namespace unitos {

template<typename SuiteType,typename TestType>
class TestRegistrator
{
public:
    TestRegistrator(char const* name);
};

class Suite
{
public:
    Suite();
    virtual ~Suite();
    virtual char const* getName() const = 0;

    bool runTests();
    bool runTest(char const* name);

    void registerTest(char const* name, SuiteTestInfo::CreateCallback* createCallback);

    int testCount() const;
    int passedCount() const;
    int testedCount() const;

private:
    SuiteTestInfo* findTestInfo(char const* name);
    bool runTest(SuiteTestInfo& info);

private:
    SuiteTestInfo m_testInfos[256];
    int m_testCount;
    int m_passedCount;
    int m_testedCount;
};

} // end of unitos

#include "unitos/suite.inl"

#endif
