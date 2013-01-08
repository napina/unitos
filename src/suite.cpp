// Copyright (C) Ville Ruusutie, 2010

#include "unitos/unitos.h"

namespace unitos {

Suite::Suite()
    : testCount(0)
    , passedCount(0)
    , testedCount(0)
{
    unitos::SuiteRegistrator registrator(this);
}

Suite::~Suite()
{
}

bool Suite::RunTests()
{
    for(int i = 0; i < this->testCount; ++i) {
        SuiteTestInfo& info = this->testInfos[i];
        RunTest(info);
    }
    return this->passedCount == this->testedCount;
}

bool Suite::RunTest(char const* name)
{
    SuiteTestInfo* info = FindTestInfo(name);
    if(info) {
        return RunTest(*info);
    }
    return false;
}

bool Suite::RunTest(SuiteTestInfo& info)
{
    SuiteTest* test = info.createCallback();
    test->info = &info;
#if !defined(UNITOS_NO_EXCEPTIONS)
    try {
#endif
        __int64 startTime = unitos::GetSystemTime();
        test->Run();
        __int64 endTime = unitos::GetSystemTime();
        info.timeMicros = endTime - startTime;
#if !defined(UNITOS_NO_EXCEPTIONS)
    } catch(...) {
        Framework& output = Framework::Get();
        unitos::String message(2048);
        message << "Exception in ";
        message << test->GetSuiteName();
        message << "Suite.";
        message << test->GetName();
        message << "Test\n";
        message.Terminate();
        output << message;
        info.hasFailed = true;
    }
#endif
    delete test;

    ++(this->testedCount);
    if(!info.hasFailed) {
        ++(this->passedCount);
    }
    return !info.hasFailed;
}

void Suite::RegisterTest(char const* name, SuiteTestInfo::CreateCallback* createCallback)
{
    SuiteTestInfo& info = this->testInfos[this->testCount];
    info.name = name;
    info.createCallback = createCallback;
    info.hasFailed = false;
    ++(this->testCount);
}

SuiteTestInfo* Suite::FindTestInfo(char const* name)
{
    for(int i = 0; i < this->testCount; ++i) {
        SuiteTestInfo& info = this->testInfos[i];
        /*if(strcmp(info.name, name) == 0) */{
            return &info;
        }
    }
    return 0;
}

}
