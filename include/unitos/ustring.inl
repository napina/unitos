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

#include "unitos/platform.h"
//----------------------------------------------------------------------------

namespace unitos {

inline String::String(size_t capasity)
	: m_buffer(nullptr)
	, m_length(0)
	, m_capasity(capasity)
{
	m_buffer = new char[capasity];
	m_buffer[0] = 0;
}
//----------------------------------------------------------------------------

inline String::String(String const& other)
	: m_buffer(nullptr)
	, m_length(0)
	, m_capasity(0)
{
	m_length = other.m_length;
	m_capasity = other.m_length + 1;
	m_buffer = new char[m_capasity];
	unitos::memcopy(m_buffer, other.m_buffer, m_capasity);
}
//----------------------------------------------------------------------------

__forceinline String::String(char const* str, size_t length)
	: m_buffer(nullptr)
	, m_length(length)
	, m_capasity(0)
{
	m_capasity = length + 1;
	m_buffer = new char[m_capasity];
	unitos::memcopy(m_buffer, str, m_capasity);
}
//----------------------------------------------------------------------------

__forceinline String::String(char const* str)
{
	m_length = unitos::strlen(str);
	m_capasity = m_length + 1;
	m_buffer = new char[m_capasity];
	unitos::memcopy(m_buffer, str, m_capasity);
}
//----------------------------------------------------------------------------

__forceinline String::~String()
{
	delete [] m_buffer;
}
//----------------------------------------------------------------------------

template<typename T>
inline String& String::operator<<(T const& value)
{
	(*this) << toString<T>(value);
	return *this;
}
//----------------------------------------------------------------------------

template<>
__forceinline String& String::operator<<(char const& ch)
{
	m_buffer[m_length] = ch;
	++m_length;
	return *this;
}
//----------------------------------------------------------------------------

template<>
inline String& String::operator<<(String const& text)
{
	// todo make safe
	unitos::memcopy(&m_buffer[m_length], text.c_str(), text.length());
	m_length += text.length();
	return *this;
}
//----------------------------------------------------------------------------

inline String& String::operator<<(char const* text)
{
	// todo make safe
	size_t appendLength = unitos::strlen(text);
	unitos::memcopy(&m_buffer[m_length], text, appendLength);
	m_length += appendLength;
	return *this;
}
//----------------------------------------------------------------------------

__forceinline void String::terminate()
{
	m_buffer[m_length] = 0;
}
//----------------------------------------------------------------------------

__forceinline char const* String::c_str() const
{
	return m_buffer;
}
//----------------------------------------------------------------------------

__forceinline size_t String::length() const
{
	return m_length;
}
//----------------------------------------------------------------------------

template<typename T>
inline unitos::String toString(T const& value)
{
	return toString((T*)&value);
}
//----------------------------------------------------------------------------

#define U_NUMBERTOSTRING(SRCTYPE, TARGETTYPE)\
	template<>\
	inline unitos::String toString(SRCTYPE const& value)\
	{\
		unitos::String result(64);\
		result << (TARGETTYPE)(value);\
		result.terminate();\
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
//----------------------------------------------------------------------------

template<>
inline unitos::String toString(bool const& value)
{
	unitos::String result(6);
	result << (value ? "true" : "false");
	result.terminate();
	return result;
}
//----------------------------------------------------------------------------

template<typename T>
inline unitos::String toString(T* value)
{
	unitos::String result(17);
	if(value == nullptr)
		result << "nullptr";
	else
		result << (int)value;
	result.terminate();
	return result;
}
//----------------------------------------------------------------------------

template<>
inline unitos::String toString(char const* str)
{
	return unitos::String(str);
}
//----------------------------------------------------------------------------

} // end of unitos
