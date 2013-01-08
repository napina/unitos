// Copyright (C) Ville Ruusutie, 2010

#include "unitos/unitos.h"

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
    char* ptr = &this->buffer[this->length];
    char* ptr1 = ptr;
    char tmp_char;
    long long int tmp_value;
    
    do {
        tmp_value = value;
        value /= 10;
        (*ptr) = "fedcba9876543210123456789abcdef"[15 + (tmp_value - value * 10)];
        ++ptr;
        ++(this->length);
    } while(value);

    if(tmp_value < 0) {
        *ptr++ = '-';
        ++(this->length);
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
    char* ptr = &this->buffer[this->length];
    char* ptr1 = ptr;
    char tmp_char;
    unsigned long long int tmp_value;
    
    do {
        tmp_value = value;
        value /= 10;
        (*ptr) = "fedcba9876543210123456789abcdef"[15 + (tmp_value - value * 10)];
        ++ptr;
        ++(this->length);
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

/*int String::ComputeLength(char const* text)
{
    int length = 0;
    while(*text != 0) {
        ++text;
        ++length;
    }
    return length;
}*/

}
