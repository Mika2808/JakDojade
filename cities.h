#pragma once
#include"String.h"
#include"MyVector.h"
#include"Flights.h"

struct City {
        
        String name;
        int x, y;
        City* next;
        City* prev;

        MyVector neighbour;
        

        City() {
                this->x = 0;
                this->y = 0;
                this->next = nullptr;
                this->prev = nullptr;
        }

        City(const String& name,int x,int y){
                this->name = name;
                this->x = x;
                this->y = y;
                this->next = nullptr;
                this->prev = nullptr;
        }
};

class Cities
{
        City* head;
        City* tail;
        int Numbers_of_Cities;
        MyVector Graph;

public:
        Cities();
        ~Cities();

        //DODAWANIE MIASTA DO LISTY
        void Add(const String& name,int x,int y);
        void Add(City *tmp);
        
        //WYSZUKIWANIE MIASTA
        City* FindCity(const String& name);
        City* FindCity(int x,int y);

        //LICZNIK MIAST
        int GetNumbers_of_Cities();

        //FUNKCJÃ DO TWORZENIA GRAFU
        void MakeGraph(char** array,int width,int height);
        void Connections(char** array,int width,int height,int i,int j,City*tmp,int suma);
        void UpgradeGraph(Flights flights_list);
        void OdczytywanieKomendy(City* from, City* to, int type);
        void Time(City* from, City* to,int type);
};
