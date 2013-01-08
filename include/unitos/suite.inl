// Copyright (C) Ville Ruusutie, 2010

#pragma once
#ifndef unitos_suite_inl
#define unitos_suite_inl

namespace unitos {
	
template<typename SuiteType,typename TestType>
inline TestRegistrator<SuiteType,TestType>::TestRegistrator(char const* name)
{
	SuiteType::Get().RegisterTest(name, TestType::Create);
}

inline int Suite::TestCount() const
{
    return this->testCount;
}

inline int Suite::PassedCount() const
{
    return this->passedCount;
}

inline int Suite::TestedCount() const
{
    return this->testedCount;
}

} // end of unitos

#endif
