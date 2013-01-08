// Copyright (C) Ville Ruusutie, 2010

#pragma once
#ifndef unitos_suitetest_inl
#define unitos_suitetest_inl

#include "unitos/framework.h"

namespace unitos {

__forceinline bool SuiteTest::HasFailed() const
{
    return this->info->hasFailed;
}

inline void SuiteTest::ReportFailure(char const* test, String const& testValue, String const& expectedValue, char const* file, int line)
{
    unitos::String message(2048);
    message << file;
#if defined(__APPLE__) || defined(__GNUG__)
    message << ":" << line;
#else
    message << "(" << line << ")";
#endif
    message << ": Error " << GetSuiteName() << "Suite." << GetName() << "Test: failed";
	message << "\nExpectation: " << test;
    message << "\nExpected Value: " << expectedValue;
    message << "\nTest Value: " << testValue << "\n";
    message.Terminate();
    *this << message;

    this->info->hasFailed = true;
}

__forceinline void SuiteTest::operator<<(unitos::String const& text)
{
	Framework::Get() << text;
}

} // end of unitos

#endif
