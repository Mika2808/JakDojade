#include<iostream>
#include"Cities.h"

struct JakDojade {
        
        //ZMIENNE DO ZARZĄDZANIE PROGRAMEM
        int width;
        int height;
        int numbers_of_flights;
        int numbers_of_qustions;
        
        //MAPA
        char** map;

        //LISTA MIAST I LOTÓW
        Cities list;    
        Flights list_flights;   

        //KONSTRUKTOR
        JakDojade() {
                this->width = 0;
                this->height = 0;
                this->numbers_of_flights = 0;
                this->numbers_of_qustions = 0;
                this->map = nullptr;
        }
};

struct Cords {
        int x, y;
};

Cords FindStar(char** array, int i, int j, int width, int height);

int main() {
        JakDojade data;

        //WCZYTYWANIE SZEROKOŚCI I WYSOKOŚCI MAPY
        std::cin >> data.width;
        std::cin >> data.height;
        
        //TWORZENIE MAPY
        data.map = new char*[data.height];
        for (int i = 0; i < data.height; i++) {
                data.map[i] = new char[data.width];
        }
        
        //WCZYTYWANIE MAPY
        char znak;

        for (int i = 0; i < data.height; i++) {
                for (int j = 0; j < data.width; j++) {

                        std::cin >> znak;
                        
                        //TABLICA CHAR
                        data.map[i][j] = znak;

                }
        }

        //SZUKANIE MIAST
        String name;
        Cords tmp_cords;
        for (int i = 0; i < data.height; i++) {
                for (int j = 0; j < data.width; j++) {
                        
                        //PIERWSZA LITERA MIASTA
                        if ((data.map[i][j] != '*') && (data.map[i][j] != '#') && (data.map[i][j] != '.')) {
                                
                                //SZUKANIE WSPÓŁRZĘDNYCH MIASTA (od pierwszej litery)
                                tmp_cords = FindStar(data.map, i, j, data.width, data.height);

                                //WCZYTYWANIE NAZWY MIASTA
                                while ((j < data.width) && (data.map[i][j] != '*') &&
                                        (data.map[i][j] != '#') && (data.map[i][j] != '.')) {
                                        name.append(data.map[i][j]);
                                        j++;
                                }
                                

                                //SZUKANIE WSPÓŁRZĘDNYCH MIASTA (od ostatniej litery)
                                if (tmp_cords.x == -1 || tmp_cords.y == -1) {
                                        tmp_cords = FindStar(data.map, i, j - 1, data.width, data.height);
                                }
                                
                                //DODAWANIE MIASTA DO LISTY
                                name.ladnyString();
                                data.list.Add(name, tmp_cords.x, tmp_cords.y);
                                name.usuwanieString();
                        }
                }
        }
        
        //WCZYTYWANIE LOTÓW
        std::cin >> data.numbers_of_flights;
        znak = getchar();

        City* from = nullptr;
        City* to = nullptr;
        bool city1 = false;

        for (int i = 0; i < data.numbers_of_flights; i++) {
                while ((znak = (char)getchar()) != '\n') {
                        if(!isspace(znak))
                        name.append(znak);
                        else {
                                name.ladnyString();
                                if (city1 == false) {
                                        from= data.list.FindCity(name);
                                        city1 = true;
                                }
                                else to = data.list.FindCity(name);
                                name.usuwanieString();
                        }
                }

                name.ladnyString();
                data.list_flights.Add(from, to,atoi(name.napis));
                name.usuwanieString();
                
                from = nullptr;
                to = nullptr;
                city1 = false;
        }
        
        data.list.MakeGraph(data.map,data.width,data.height);
        
        if(data.numbers_of_flights!=0)data.list.UpgradeGraph(data.list_flights);

        //WCZYTYWANIE ZAPYTAŃ
        std::cin >> data.numbers_of_qustions;
        
        from = nullptr;
        to = nullptr;
        city1 = false;
        znak = getchar();
        for (int i = 0; i < data.numbers_of_qustions; i++) {
                
                while ((znak = (char)getchar()) != '\n') {
                        if (znak == EOF) break;
                        if (!isspace(znak))
                                name.append(znak);
                        else {
                                name.ladnyString();
                                if (city1 == false) {
                                        from = data.list.FindCity(name);
                                        city1 = true;
                                }
                                else to = data.list.FindCity(name);
                                name.usuwanieString();
                        }
                }

                name.ladnyString();
                data.list.OdczytywanieKomendy(from, to, atoi(name.napis));
                name.usuwanieString();

                from = nullptr;
                to = nullptr;
                city1 = false;
        }

        //ZWALNIANIE PAMIĘCI
        for (int i = 0; i < data.height; i++) {
                delete[] data.map[i];
        }
        delete[] data.map;
        
        return 0;
}

Cords FindStar(char** array, int i, int j, int width, int height) {
        Cords tmp;
        tmp.x = -1;
        tmp.y = -1;
        
        if (array[i][j] == '*') {
                tmp.x = j;
                tmp.y = i;
                return tmp;
        }
        else if ((i > 0) && (array[i - 1][j] == '*')) {
                tmp.x = j;
                tmp.y = i - 1;
                return tmp;
        }
        else if ((i > 0) && (j > 0) && (array[i - 1][j - 1] == '*')) {
                tmp.x = j - 1;
                tmp.y = i - 1;
                return tmp;
        }
        else if ((i > 0) && (j < (width - 1)) && (array[i - 1][j + 1] == '*')) {
                tmp.x = j + 1;
                tmp.y = i - 1;
                return tmp;
        }
        else if ((j > 0) && (array[i][j - 1] == '*')) {
                tmp.x = j - 1;
                tmp.y = i;
                return tmp;
        }
        else if ((j < (width - 1)) && (array[i][j + 1] == '*')) {
                tmp.x = j + 1;
                tmp.y = i;
                return tmp;
        }
        
        else if ((i < (height - 1)) && (array[i + 1][j] == '*')) {
                        tmp.x = j;
                        tmp.y = i + 1;
                        return tmp;
        }
        else if ((i < (height - 1)) && (j > 0) && (array[i + 1][j - 1] == '*')) {
                tmp.x = j - 1;
                tmp.y = i + 1;
                return tmp;
        }
        else if ((i < (height - 1)) && (j < (width - 1)) && (array[i + 1][j + 1] == '*')) {
                tmp.x = j + 1;
                tmp.y = i + 1;
                return tmp;
                }
                
        return tmp;
}