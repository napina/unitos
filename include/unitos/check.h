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
