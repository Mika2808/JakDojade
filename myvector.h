#pragma once
struct City;

struct Road {
        City* to;
        City* from;
        int time;
        int distance;
        bool visited;
        Road() {
                this->to = nullptr;
                this->from = nullptr;
                this->time = 0;
                this->distance = -1;
                this->visited = false;
        }
        Road(City* tmp, int time) {
                this->time = time;
                this->to = tmp;
                this->from = nullptr;
                this->distance = -1;
                this->visited = false;
        }
        void SetVisit(bool a) {
                this->visited = a;
        }
        void SetDistance(int a) {
                this->distance = a;
        }
};

class MyVector
{
        int size;
        int capacity;
        Road** data;

public:
        int time;
        MyVector();
        MyVector(int size);
        ~MyVector();

        int GetSize();
        //      void SetSize();

        //DODAWANIE ELEMENTU DO WEKTORA
        void push_back(City* tmp,int time);

        //SORTUJ WEKTOR
        void Sortowanie();
        
        //POBIERANIE WSKAŹNIKA NA MIASTO OD INDEKSU
        Road* operator[](int index);
        const Road* operator[](int index) const;

};