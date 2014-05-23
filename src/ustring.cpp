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
#include "unitos/unitos.h"
#include <string>

namespace unitos {

String& String::operator<<(float value)
{
    int upper = (int)value;
    if(value != value) {
        (*this) << "infinity";
        return *this;
    }
    if(upper == 0 && value < 0.0f) {
        (*this) << '-';
    }
    (*this) << upper;
    (*this) << '.';

    float lower = value - (float)upper;
    int lowerInt;
    for(int i = 0; i < 6; ++i) {
        lower *= 10;
        lowerInt = (int)lower;
        (*this) << "9876543210123456789"[9 + lowerInt];
        lower -= (float)lowerInt;
    }
    (*this) << 'f';

    return *this;
}

String& String::operator<<(long long int value)
{
    char* ptr = &m_buffer[m_length];
    char* ptr1 = ptr;
    char tmp_char;
    long long int tmp_value;
    
    do {
        tmp_value = value;
        value /= 10;
        (*ptr) = "fedcba9876543210123456789abcdef"[15 + (tmp_value - value * 10)];
        ++ptr;
        ++m_length;
    } while(value);

    if(tmp_value < 0) {
        *ptr++ = '-';
        ++m_length;
    }
    --ptr;

    // reverse
    while(ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }

    return *this;
}

String& String::operator<<(unsigned long long int value)
{
    char* ptr = &m_buffer[m_length];
    char* ptr1 = ptr;
    char tmp_char;
    unsigned long long int tmp_value;
    
    do {
        tmp_value = value;
        value /= 10;
        (*ptr) = "fedcba9876543210123456789abcdef"[15 + (tmp_value - value * 10)];
        ++ptr;
        ++m_length;
    } while(value);
    --ptr;

    // reverse
    while(ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }

    return *this;
}

size_t strlen(char const* str)
{
    return ::strlen(str);
}

int compare(char const* str, char const* otherStr)
{
    return ::strcmp(str, otherStr);
}

void memcopy(void* dest, void const* src, size_t size)
{
    ::memcpy(dest, src, size);
}

}
