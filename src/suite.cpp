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

Suite::Suite()
	: m_testCount(0)
	, m_passedCount(0)
	, m_testedCount(0)
{
	unitos::SuiteRegistrator registrator(this);
}
//----------------------------------------------------------------------------

Suite::~Suite()
{
}
//----------------------------------------------------------------------------

bool Suite::runTests()
{
	for(int i = 0; i < m_testCount; ++i) {
		SuiteTestInfo& info = m_testInfos[i];
		runTest(info);
	}
	return m_passedCount == m_testedCount;
}
//----------------------------------------------------------------------------

bool Suite::runTest(char const* name)
{
	SuiteTestInfo* info = findTestInfo(name);
	if(info) {
		return runTest(*info);
	}
	return false;
}
//----------------------------------------------------------------------------

bool Suite::runTest(SuiteTestInfo& info)
{
	SuiteTest* test = info.createCallback();
	test->m_info = &info;
#if !defined(UNITOS_NO_EXCEPTIONS)
	try {
#endif
		int64_t startTime = unitos::getSystemTime();
		test->run();
		int64_t endTime = unitos::getSystemTime();
		info.timeMicros = endTime - startTime;
#if !defined(UNITOS_NO_EXCEPTIONS)
	} catch(...) {
		Framework& output = Framework::get();
		unitos::String message(2048);
		message << "Exception in ";
		message << test->getSuiteName();
		message << "Suite.";
		message << test->getName();
		message << "Test\n";
		message.terminate();
		output << message;
		info.hasFailed = true;
	}
#endif
	delete test;

	++(m_testedCount);
	if(!info.hasFailed) {
		++m_passedCount;
	}
	return !info.hasFailed;
}
//----------------------------------------------------------------------------

void Suite::registerTest(char const* name, SuiteTestInfo::CreateCallback* createCallback)
{
	SuiteTestInfo& info = m_testInfos[m_testCount];
	info.name = name;
	info.createCallback = createCallback;
	info.hasFailed = false;
	++m_testCount;
}
//----------------------------------------------------------------------------

SuiteTestInfo* Suite::findTestInfo(char const* name)
{
	for(int i = 0; i < m_testCount; ++i) {
		SuiteTestInfo& info = m_testInfos[i];
		if(unitos::compare(info.name, name) == 0) {
			return &info;
		}
	}
	return nullptr;
}
//----------------------------------------------------------------------------

} // end of unitos
