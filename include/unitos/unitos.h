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

#include "unitos/platform.h"
#include "unitos/ustring.h"
#include "unitos/framework.h"
#include "unitos/suite.h"
#include "unitos/suitetest.h"
#include "unitos/output.h"
#include "unitos/check.h"
//----------------------------------------------------------------------------

#define RUN_ALL_TESTS()\
	unitos::Framework::get().runAllTests();

#define RUN_SUITE(SuiteName)\
	unitos::Framework::get().runSuiteTests(#SuiteName);

#define RUN_SUITE_TEST(SuiteName, TestName)\
	unitos::Framework::get().runSuiteTest(#SuiteName, #TestName);

#define REGISTER_OUTPUT(OutputType)\
	OutputType local##OutputType;\
	unitos::Framework::get().registerOutput(&local##OutputType);

#define TEST_SUITE(SuiteName)\
	namespace Suite##SuiteName {\
		class LocalTestSuite : public unitos::Suite {\
		public:\
			LocalTestSuite() : unitos::Suite() {}\
			virtual ~LocalTestSuite() {}\
			virtual char const* getName() const { return #SuiteName; }\
			static LocalTestSuite& get() { static LocalTestSuite suite; return suite; }\
		};\
	}\
	namespace Suite##SuiteName

#define TEST_FIXTURE(FixtureName, TestName)\
	class Test_##TestName : public FixtureName {\
	public:\
		Test_##TestName() : FixtureName() {}\
		virtual ~Test_##TestName() {}\
		virtual void run();\
		virtual char const* getName() const { return #TestName; }\
		virtual char const* getSuiteName() const { return LocalTestSuite::get().getName(); }\
		static unitos::SuiteTest* create() { return new Test_##TestName(); }\
	};\
	static unitos::TestRegistrator<LocalTestSuite,Test_##TestName> s_test##TestName(#TestName);\
	void Test_##TestName::run()

#define TEST(TestName)\
	TEST_FIXTURE(unitos::SuiteTest, TestName)

#define TODO_TEST(TestName)\
	void TODO_##TestName(void(*reportFailure)(char const*, unitos::String const&, unitos::String const&, char const*, int))
#define TODO_TEST_FIXTURE(FixtureName, TestName)\
	void TODO_##TestName(void(*reportFailure)(char const*, unitos::String const&, unitos::String const&, char const*, int))

#define REPORT_FAILURE_MACRO(Text,TestValue,ExpectedValue)\
	UNITOS_TRAP(); reportFailure(Text,unitos::toString(TestValue),unitos::toString(ExpectedValue),__FILE__,__LINE__)

#define EXPECT_TEST_MACRO(Test,TestValue,ExpectedValue)\
	if(!unitos::##Test) { REPORT_FAILURE_MACRO(#Test,TestValue,ExpectedValue); return; }

#define EXPECT_NULL(TestValue)\
	EXPECT_TEST_MACRO(isNull(TestValue),TestValue,"nullptr")
	
#define EXPECT_VALID(TestValue)\
	EXPECT_TEST_MACRO(isValid(TestValue),TestValue,"not nullptr")

#define EXPECT_TRUE(TestValue)\
	EXPECT_TEST_MACRO(isTrue(TestValue),TestValue,"true")

#define EXPECT_FALSE(TestValue)\
	EXPECT_TEST_MACRO(isFalse(TestValue),TestValue,"false")

#define EXPECT_EQUAL(TestValue, ExpectedValue)\
	EXPECT_TEST_MACRO(isEqual(TestValue, ExpectedValue),TestValue,ExpectedValue)

#define EXPECT_NOTEQUAL(TestValue, ExpectedValue)\
	EXPECT_TEST_MACRO(isNotEqual(TestValue, ExpectedValue),TestValue,ExpectedValue)

#define EXPECT_CLOSE(TestValue, ExpectedValue, Tolerance)\
	EXPECT_TEST_MACRO(isClose(TestValue, ExpectedValue, Tolerance),TestValue,ExpectedValue)

#define EXPECT_OK(Function)\
	Function; if(hasFailed()) { return; }

#if defined(UNITOS_NO_EXCEPTIONS)
#define EXPECT_ASSERT(SomeCode,ExpectedAssert)
#else
#define EXPECT_ASSERT(SomeCode,ExpectedAssert)\
	try { SomeCode; REPORT_FAILURE_MACRO(#SomeCode " did not throw assert",0); return; } catch(ExpectedAssert) {}
#endif
