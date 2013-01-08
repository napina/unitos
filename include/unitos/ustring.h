// Copyright (C) Ville Ruusutie, 2010

#pragma once
#ifndef unitos_string_h
#define unitos_string_h

namespace unitos {
    
class String
{
public:
    String(int capasity);
    String(String const& other);
    String(char const* str, int length);
    explicit String(char const* str);
    ~String();
    
    template<typename T>
    String& operator<<(T const& value);
    String& operator<<(char const* value);
    String& operator<<(float value);
    String& operator<<(long long int value);
    String& operator<<(unsigned long long int value);
    void Terminate();

    char const* GetCStr() const;
    int GetLength() const;
private:
    char* buffer;
    int length;
    int capasity;
};

template<typename T>
unitos::String ToString(T const& value);

template<typename T>
unitos::String ToString(T* value);

}; // end of unitos

#include "unitos/ustring.inl"

#endif
