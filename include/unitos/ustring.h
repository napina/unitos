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
//----------------------------------------------------------------------------

namespace unitos {

class String
{
public:
	String(size_t capasity);
	String(String const& other);
	String(char const* str, size_t length);
	explicit String(char const* str);
	~String();

	template<typename T>
	String& operator<<(T const& value);
	String& operator<<(char const* value);
	String& operator<<(float value);
	String& operator<<(int64_t value);
	String& operator<<(uint64_t value);
	void terminate();

	char const* c_str() const;
	size_t length() const;
private:
	char* m_buffer;
	size_t m_length;
	size_t m_capasity;
};
//----------------------------------------------------------------------------

template<typename T>
unitos::String toString(T const& value);

template<typename T>
unitos::String toString(T* value);

size_t strlen(char const* str);
int compare(char const* str, char const* otherStr);
void memcopy(void* dest, void const* src, size_t size);
//----------------------------------------------------------------------------

} // end of unitos

#include "unitos/ustring.inl"
//----------------------------------------------------------------------------
