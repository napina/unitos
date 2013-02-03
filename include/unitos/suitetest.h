/*=============================================================================

Copyright (c) 2010-2013 Ville Ruusutie

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
#ifndef unitos_suitetest_h
#define unitos_suitetest_h

namespace unitos {

class Suite;
class SuiteTest;

class SuiteTestInfo
{
public:
    typedef unitos::SuiteTest* (CreateCallback)();
public:
    char const* name;
    CreateCallback* createCallback;
    __int64 timeMicros;
    bool hasFailed;
};

class SuiteTest
{
public:
    SuiteTest() : info(0) {}
    virtual ~SuiteTest() {}
    virtual void Run() = 0;
    virtual char const* GetName() const = 0;
    virtual char const* GetSuiteName() const = 0;

protected:
    bool HasFailed() const;
    void ReportFailure(char const* test, String const& testValue, String const& expectedValue, char const* file, int line);
	void operator<<(unitos::String const& text);
    
private:
    friend class Suite;
    unitos::SuiteTestInfo* info;
};

} // end of unitos

#include "unitos/suitetest.inl"

#endif
