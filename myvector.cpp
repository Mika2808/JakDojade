#include "MyVector.h"

MyVector::MyVector() {
        this->size = 0;
        this->capacity = 2;
        this->time = 0;
        this->data = new Road*[capacity];
}

MyVector::MyVector(int size) {
        this->size = size;
        this->capacity = size;
        this->time = 0;
        this->data = new Road*[capacity];
}

void MyVector::push_back(City* tmp,int time) {

        bool oldtown = false;

        for (int i = 0; i < this->size; i++) {
                if (this->data[i]->to == tmp) {
                        if (this->data[i]->time > time) {
                                data[i]->time = time;
                        }
                        oldtown = true;
                        break;
                }
        }

        if (oldtown == false) {
                if (size == capacity) {
                        capacity *= 2;
                        Road** NewData = new Road*[capacity];
                        for (int i = 0; i < size; i++) {
                                NewData[i] = new Road(data[i]->to, data[i]->time);
                        }
                        delete[]data;

                        data = NewData;

                }
                data[size] = new Road(tmp, time);
                data[size]->visited = false;
                size++;
        }
}

void MyVector::Sortowanie() {
        for (int i = 1; i < size; i++) {
                Road* tmp = data[i];
                int j = i - 1;
                while (j >= 0 && data[j]->time > tmp->time) {
                        data[j + 1] = data[j];
                        j--;
                }
                data[j + 1] = tmp;
        }
}

int MyVector::GetSize() {
        return size;
}

MyVector::~MyVector() {
        delete[] data;
}

Road* MyVector::operator[](int index) {
        return data[index];
}

const Road* MyVector::operator[](int index) const {
        return data[index];
}