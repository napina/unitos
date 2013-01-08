// Copyright (C) Ville Ruusutie, 2010

#pragma once
#ifndef unitos_check_inl
#define unitos_check_inl

#include "string.h"

namespace unitos {

__forceinline bool IsNull(void const* value)
{
    return (value == nullptr);
}

__forceinline bool IsValid(void const* value)
{
    return (value != nullptr);
}

__forceinline bool IsTrue(bool value)
{
    return value == true;
}

__forceinline bool IsFalse(bool value)
{
    return value == false;
}

template<typename T,typename T2>
bool IsSame()
{
    return T == T2;
}

template<typename T,typename T2>
__forceinline bool IsEqual(T const& value, T2 const& otherValue)
{
    return (value == otherValue);
}

__forceinline bool IsEqual(char const* str, char const* otherStr)
{
    return unitos::StrCmp(str, otherStr) == 0;
}

template<typename T,typename T2>
__forceinline bool IsNotEqual(T const& value, T2 const& otherValue)
{
    return (value != otherValue);
}

template<typename T, typename T2>
__forceinline bool IsClose(T const& value, T const& otherValue, T2 tolerance)
{
    T diff = value - otherValue;
    return (diff >= -tolerance) && (diff <= tolerance);
}

} // end of unitos

#endif
