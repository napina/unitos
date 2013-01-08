// Copyright (C) Ville Ruusutie, 2010

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
	virtual char const* GetName() const = 0;

	bool RunTests();
	bool RunTest(char const* name);
	
	void RegisterTest(char const* name, SuiteTestInfo::CreateCallback* createCallback);

    int TestCount() const;
    int PassedCount() const;
    int TestedCount() const;

private:
	SuiteTestInfo* FindTestInfo(char const* name);
	bool RunTest(SuiteTestInfo& info);

private:
	SuiteTestInfo testInfos[256];
	int testCount;
    int passedCount;
    int testedCount;
};

} // end of unitos

#include "unitos/suite.inl"

#endif
