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
#ifndef unitos_suitetest_inl
#define unitos_suitetest_inl

#include "unitos/framework.h"

namespace unitos {

__forceinline bool SuiteTest::hasFailed() const
{
    return m_info->hasFailed;
}

inline void SuiteTest::reportFailure(char const* test, String const& testValue, String const& expectedValue, char const* file, int line)
{
    unitos::String message(2048);
    message << file;
#if defined(__APPLE__) || defined(__GNUG__)
    message << ":" << line;
#else
    message << "(" << line << ")";
#endif
    message << ": Error " << getSuiteName() << "Suite." << getName() << "Test: failed";
    message << "\nExpectation: " << test;
    message << "\nExpected Value: " << expectedValue;
    message << "\nTest Value: " << testValue << "\n";
    message.terminate();
    *this << message;

    m_info->hasFailed = true;
}

__forceinline void SuiteTest::operator<<(unitos::String const& text)
{
    Framework::get() << text;
}

} // end of unitos

#endif
