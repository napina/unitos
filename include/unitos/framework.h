// Copyright (C) Ville Ruusutie, 2010

#pragma once
#ifndef unitos_framework_h
#define unitos_framework_h

#include "unitos/ustring.h"

namespace unitos {
    
class Suite;
class SuiteTest;
class Output;
    
class Framework
{
public:
    Framework();
    ~Framework();
    
    void RegisterOutput(unitos::Output* handler);
    
    void RunAllTests();
    void RunSuiteTests(char const* suiteName);
    void RunSuiteTest(char const* suiteName, char const* testName);
    
    void operator<<(unitos::String const& text);
    static Framework& Get();
    
private:
    friend class SuiteRegistrator;
    void RegisterSuite(unitos::Suite* suite);
    unitos::Suite* FindSuite(char const* name);

private:
    unitos::Suite* suites[256];
    unitos::Output* outputs[8];
    int suiteCount;
    int outputCount;
};

class SuiteRegistrator
{
public:
    SuiteRegistrator(unitos::Suite* suite);
};

}; // end of unitos

#endif
