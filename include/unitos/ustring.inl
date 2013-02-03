/*=============================================================================

Copyright (c) 2010-2013 Ville Ruusutie

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
#ifndef unitos_string_inl
#define unitos_string_inl

#include "unitos/platform.h"
#include <string.h>

namespace unitos {

__forceinline String::String(int capasity)
    : buffer(0)
    , capasity(capasity)
    , length(0)
{
    this->buffer = new char[capasity];
    this->buffer[0] = 0;
}

__forceinline String::String(String const& other)
    : buffer(0)
    , length(0)
    , capasity(0)
{
    this->length = other.length;
    this->capasity = other.length + 1;
    this->buffer = new char[this->capasity];
	::memcpy(this->buffer, other.buffer, this->capasity);
}

__forceinline String::String(char const* str, size_t length)
    : buffer(0)
    , length(length)
    , capasity(0)
{
    this->capasity = length + 1;
    this->buffer = new char[this->capasity];
    ::memcpy(this->buffer, str, this->capasity);
}

__forceinline String::String(char const* str)
{
    this->length = ::strlen(str);
    this->capasity = this->length + 1;
    this->buffer = new char[this->capasity];
    ::memcpy(this->buffer, str, this->capasity);
}

__forceinline String::~String()
{
    delete [] this->buffer;
}

template<typename T>
__forceinline String& String::operator<<(T const& value)
{
    (*this) << ToString<T>(value);
	return *this;
}

template<>
__forceinline String& String::operator<<(char const& ch)
{
    this->buffer[this->length] = ch;
    ++(this->length);
	return *this;
}

template<>
__forceinline String& String::operator<<(String const& text)
{
    // todo make safe
    ::memcpy(&this->buffer[this->length], text.GetCStr(), text.GetLength());
    this->length += text.GetLength();
	return *this;
}

__forceinline String& String::operator<<(char const* text)
{
    // todo make safe
    size_t appendLength = ::strlen(text);
    ::memcpy(&this->buffer[this->length], text, appendLength);
    this->length += appendLength;
	return *this;
}

__forceinline void String::Terminate()
{
    this->buffer[this->length] = 0;
}
    
__forceinline char const* String::GetCStr() const
{
    return this->buffer;
}

__forceinline size_t String::GetLength() const
{
    return this->length;
}

template<typename T>
__forceinline unitos::String ToString(T const& value)
{
    return ToString((T*)&value);
}

#define U_NUMBERTOSTRING(SRCTYPE, TARGETTYPE)\
    template<>\
    __forceinline unitos::String ToString(SRCTYPE const& value)\
    {\
        unitos::String result(64);\
        TARGETTYPE val = (TARGETTYPE)(value);\
        result << val;\
        result.Terminate();\
        return result;\
    }

    U_NUMBERTOSTRING(signed short, long long int)
    U_NUMBERTOSTRING(signed int, long long int)
    U_NUMBERTOSTRING(signed long, long long int)
    U_NUMBERTOSTRING(signed long long int, long long int)
    U_NUMBERTOSTRING(unsigned short, unsigned long long int)
    U_NUMBERTOSTRING(unsigned int, unsigned long long int)
    U_NUMBERTOSTRING(unsigned long, unsigned long long int)
    U_NUMBERTOSTRING(unsigned long long int, unsigned long long int)
    U_NUMBERTOSTRING(float, float)
#undef U_NUMBERTOSTRING

template<>
__forceinline unitos::String ToString(bool const& value)
{
    unitos::String result(6);
    result << (value ? "true" : "false");
    result.Terminate();
    return result;
}

template<typename T>
__forceinline unitos::String ToString(T* value)
{
    unitos::String result(11);
    result << (int)value;
    result.Terminate();
    return result;
}

template<>
__forceinline unitos::String ToString(char const* str)
{
    return unitos::String(str);
}

} // end of unitos

#endif
