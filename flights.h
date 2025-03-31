#pragma once
#include"String.h"
struct City;
struct Flight {

        City* from;
        City* to;
        int time;
        Flight* next;

        Flight() {
                this->time = 0;
                this->to = nullptr;
                this->from = nullptr;
                this->next = nullptr;
        }

        Flight(City*from, City* to, int time) {
                this->time = time;
                this->to = to;
                this->from = from;
                this->next = nullptr;
        }
};

class Flights{

public:
        Flights();
        ~Flights();
        Flight* head;
        Flight* tail;
        
        //DODAWANIE LOTU DO LISTY
        void Add(City* from, City* to, int time);
        
        //USUWANIE LOTÃW Z LISTY
        void Delete();
};