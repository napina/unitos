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
//----------------------------------------------------------------------------

namespace unitos {

class Suite;
class SuiteTest;
//----------------------------------------------------------------------------

class SuiteTestInfo
{
public:
	typedef unitos::SuiteTest* (CreateCallback)();
public:
	char const* name;
	CreateCallback* createCallback;
	int64_t timeMicros;
	bool hasFailed;
};
//----------------------------------------------------------------------------

class SuiteTest
{
public:
	SuiteTest() : m_info(nullptr) {}
	virtual ~SuiteTest() {}
	virtual void run() = 0;
	virtual char const* getName() const = 0;
	virtual char const* getSuiteName() const = 0;

protected:
	bool hasFailed() const;
	void reportFailure(char const* test, String const& testValue, String const& expectedValue, char const* file, int line);
	void operator<<(unitos::String const& text);

private:
	friend class Suite;
	unitos::SuiteTestInfo* m_info;
};
//----------------------------------------------------------------------------

} // end of unitos

#include "unitos/suitetest.inl"
//----------------------------------------------------------------------------
