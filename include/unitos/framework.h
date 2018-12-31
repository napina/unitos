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

#include "unitos/ustring.h"
//----------------------------------------------------------------------------

namespace unitos {

class Suite;
class SuiteTest;
class Output;
//----------------------------------------------------------------------------

class Framework
{
public:
	Framework();
	~Framework();

	void registerOutput(unitos::Output* handler);

	void runAllTests();
	void runSuiteTests(char const* suiteName);
	void runSuiteTest(char const* suiteName, char const* testName);

	void operator<<(unitos::String const& text);
	static Framework& get();

private:
	friend class SuiteRegistrator;
	void registerSuite(unitos::Suite* suite);
	unitos::Suite* findSuite(char const* name);

private:
	unitos::Suite* m_suites[256];
	unitos::Output* m_outputs[8];
	int m_suiteCount;
	int m_outputCount;
};
//----------------------------------------------------------------------------

class SuiteRegistrator
{
public:
	SuiteRegistrator(unitos::Suite* suite);
};
//----------------------------------------------------------------------------

}; // end of unitos
