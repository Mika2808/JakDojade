#include "String.h"
#include<iostream>


String::String() : size(0), capacity(2), napis(NULL) {
    this->napis = new char[capacity];
}

void String::append(char czar) {
    if (size < capacity) {
        napis[size] = czar;
        size++;
    }
    else {
        capacity *= 2;
        char* nowy_napis = new char[capacity];
        for (int i = 0; i <= size; i++)
        {
            nowy_napis[i] = napis[i];
        }
        nowy_napis[size] = czar;
        napis = nowy_napis;
        size++;
    }
}
void String::usuwanieString() {
    for (int i = size - 1; i >= 0; i--)
    {
        napis[i] = NULL;
    }
    size = 0;
    capacity = 2;
}

void String::ladnyString() {
    int i = 0, j = size - 1;
    if (strcmp(this->napis, "") != 0) {
        while (napis[i] == SPACJA) {
            i++;
        }
        while (napis[j] == SPACJA && j >= 0) {
            j--;
        }
        int new_size = j - i + 1;
        if (new_size > 0) {
            char* tmp = new char[new_size + 1];

            for (int k = 0; k < new_size; k++)
            {
                tmp[k] = napis[i];
                i++;
            }
            tmp[new_size] = '\0';
            for (int k = 0; k < new_size; k++)
            {
                napis[k] = tmp[k];
            }
            size = new_size;
            append('\0');
            delete[]tmp;
        }
    }
}

char& String::operator[](int index) {
    return napis[index];
}

const char& String::operator[](int index) const {
    return napis[index];
}

String& String::operator=(const String& right) {//swap

    if (this != &right) {
        char* tmp = new char[right.size + 1];
        for (size_t i = 0; i <= right.size; i++) {
            tmp[i] = right.napis[i];
        }
        delete[] napis;
        napis = tmp;
        size = right.size;
    }
    return *this;
}

String& String::operator=(String&& right) noexcept {//move
    if (this != &right) {
        delete[] napis;
        size = right.size;
        napis = right.napis;
        right.size = 0;
        right.napis = nullptr;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const String& str) {
    os << str.napis;
    return os;
}

bool String::operator==(const String& right) const {
    return (std::strcmp(this->napis, right.napis) == 0);
}

String::~String() {
    delete[]napis;
}