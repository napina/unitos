// Copyright (C) Ville Ruusutie, 2010

#pragma once
#ifndef unitos_check_h
#define unitos_check_h

namespace unitos {

bool IsNull(void const* value);
bool IsValid(void const* value);
bool IsTrue(bool value);
bool IsFalse(bool value);

template<typename T,typename T2>
bool IsSame();

template<typename T,typename T2>
bool IsEqual(T const& value, T2 const& otherValue);

bool IsEqual(char const* str, char const* otherStr);

template<typename T,typename T2>
bool IsNotEqual(T const& value, T2 const& otherValue);

bool IsNotEqual(char const* str, char const* otherStr);

template<typename T, typename T2>
bool IsClose(T const& value, T const& otherValue, T2 tolerance);

}; // end of unitos

#include "unitos/check.inl"

#endif
