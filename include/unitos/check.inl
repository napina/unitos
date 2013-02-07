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
    return ::strcmp(str, otherStr) == 0;
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
