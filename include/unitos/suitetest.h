// Copyright (C) Ville Ruusutie, 2010

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
