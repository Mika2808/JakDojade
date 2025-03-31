#pragma once


#include<iostream>
#define SPACJA 32

class String
{
    int size;
    int capacity;
public:
    char* napis;
    String();
    ~String();
    void append(char czar);
    void usuwanieString();
    void ladnyString();
    char& operator[](int index);
    const char& operator[](int index) const;
    String& operator=(const String& right);
    String& operator=(String&& right) noexcept;
    friend std::ostream& operator<<(std::ostream& os, const String& str);
    bool operator==(const String& other) const;
 

};
