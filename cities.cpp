#include "Cities.h"

Cities::Cities() {
        head = nullptr;
        tail = nullptr;
        Numbers_of_Cities = 0;
}

void Cities::Add(const String& name,int x,int y) {
        
        //TWORZENIE NOWEGO MIASTA
        City* tmp_city = new City(name,x,y);

        //PIERWSZY ELEMENT LISTY
        if (head == nullptr) {   
                head = tmp_city;
                tail = tmp_city;
        }
        //KOLEJNY ELEMENT LISTY
        else {
                tmp_city->prev = tail;
                tail->next = tmp_city;
                tail = tmp_city;
        }
        
        Numbers_of_Cities++;
}

void Cities::Add(City* tmp) {

        City* tmp_city = new City(tmp->name, tmp->x, tmp->y);

        //PIERWSZY ELEMENT LISTY
        if (head == nullptr) {
                head = tmp_city;
                tail = tmp_city;
        }
        //KOLEJNY ELEMENT LISTY
        else {
                tmp_city->prev = tail;
                tail->next = tmp_city;
                tail = tmp_city;
        }

        Numbers_of_Cities++;
}

City* Cities::FindCity(const String& name) {
        City* tmp_city = head;

        while (tmp_city != nullptr) {
                if (tmp_city->name == name) return tmp_city;
                tmp_city = tmp_city->next;
        }
        return nullptr;
}

City* Cities::FindCity(int x,int y) {
        City* tmp_city = head;

        while (tmp_city != nullptr) {
                if ((tmp_city->x == x) && (tmp_city->y == y)) return tmp_city;
                tmp_city = tmp_city->next;
        }
        return nullptr;
}

void Cities::MakeGraph(char** array, int width, int height) {
        City* tmp_city = head;
        
        while (tmp_city != nullptr) {
                
                //TWORZENIE KOPII TABLICY
                char** array1 = new char* [height];
                for (int i = 0; i < height; i++) {
                        array1[i] = new char[width];
                }
                
                for (int i = 0; i < height; i++) {
                        for (int j = 0; j < width; j++) {
                                array1[i][j] = array[i][j];
                        }
                }
                
                array1[tmp_city->y][tmp_city->x] = '.';
                int suma = 0;
                
                //DODAWANIE MIASTA DO GRAFU
                this->Graph.push_back(tmp_city,0);
                
                //REKURENCYJNE SZUKANIE POŁĄCZEŃ MIĘDZY MIASTAMI
                Connections(array1, width, height,tmp_city->y,tmp_city->x,tmp_city,suma);
                
                //ZWALNIANIE PAMIĘCI
                for (int i = 0; i < height; i++) {
                        delete[] array1[i];
                }
                delete[] array1;

                tmp_city = tmp_city->next;
        }
}

void Cities::UpgradeGraph(Flights flights_list) {
        
        int cities = this->Graph.GetSize();
        
        for (int i = 0; i < cities; i++) {
                Flight* tmp_flight = flights_list.head;

                while (tmp_flight != nullptr) {
                        if (Graph[i]->to == tmp_flight->from) {
                                Graph[i]->to->neighbour.push_back(tmp_flight->to, tmp_flight->time);
                        }
                        tmp_flight = tmp_flight->next;
                }

                Graph[i]->to->neighbour.Sortowanie();
        }
}

void Cities::Connections(char** array, int width, int height, int i, int j, City* tmp,int suma) {
        if (i > 0 && array[i - 1][j] == '*') {

                if (FindCity(j, i - 1) != tmp) {
                        tmp->neighbour.push_back(FindCity(j, i - 1),suma + 1);
                }
                
        }
        if (j > 0 && array[i][j - 1] == '*') {
                if (FindCity(j - 1, i) != tmp) {
                        tmp->neighbour.push_back(FindCity(j - 1, i),suma + 1);
                }
                
        }
        if (j < width - 1 && array[i][j + 1] == '*') {
                if (FindCity(j + 1, i) != tmp) {
                        tmp->neighbour.push_back(FindCity(j + 1, i),suma + 1);
                }
                
        }
        if (i < height - 1 && array[i + 1][j] == '*') {
                if (FindCity(j, i + 1) != tmp) {
                        tmp->neighbour.push_back(FindCity(j, i + 1),suma + 1);
                }       
        }

        if (i > 0 && array[i - 1][j] == '#') {
                array[i - 1][j] = '.';
                Connections(array, width, height, i - 1, j, tmp,suma + 1);
        }
        if (j < width - 1 && array[i][j + 1] == '#') {
                array[i][j + 1] = '.';
                Connections(array, width, height, i, j + 1, tmp,suma + 1);
        }
        if (j > 0 && array[i][j - 1] == '#') {
                array[i][j - 1] = '.';
                Connections(array, width, height, i, j - 1, tmp, suma + 1);
        }
        
        if (i < height - 1 && array[i + 1][j] == '#') {
                array[i + 1][j] = '.';
                Connections(array, width, height, i + 1, j, tmp, suma + 1);
        }
}

void Cities::OdczytywanieKomendy(City* from, City* to, int type) {
        Time(from, to, type);
}

void Cities::Time(City* from, City* to,int type) {
        if (from != to) {
                Road* tmp_road = nullptr;
                int unvisited = Graph.GetSize();
                int V = Graph.GetSize();

                City* tmp_city = nullptr;

                for (int i = 0; i < V; i++) {
                        if (Graph[i]->to == from) {
                                tmp_road = Graph[i];
                                tmp_road->distance = 0;
                                tmp_city = tmp_road->to;
                                while (unvisited != 0) {

                                        for (int ii = 0; ii <= tmp_road->to->neighbour.GetSize() - 1; ii++) {
                                                if (tmp_road->to->neighbour[ii]->visited == true)continue;
                                                for (int j = 0; j < V; j++) {
                                                        
                                                        if (Graph[j]->to == tmp_road->to->neighbour[ii]->to) {
                                                                if (Graph[j]->distance == -1) {
                                                                        Graph[j]->SetDistance(tmp_road->distance + tmp_road->to->neighbour[ii]->time);
                                                                        Graph[j]->from = tmp_road->to;
                                                                        tmp_city = Graph[j]->from;
                                                                }
                                                                else if (tmp_road->distance + tmp_road->to->neighbour[ii]->time < Graph[j]->distance) {
                                                                        Graph[j]->SetDistance(tmp_road->distance + tmp_road->to->neighbour[ii]->time);                                                                  
                                                                        Graph[j]->from = tmp_road->to;                                                                  
                                                                        tmp_city = Graph[j]->from;
                                                                }
                                                                break;
                                                        }
                                                }
                                        }
                                        tmp_road->SetVisit(true);
                                        tmp_city = tmp_road->to;

                                        for (int j = 0; j < V; j++) {

                                                for (int ii = 0; ii <= Graph[j]->to->neighbour.GetSize() - 1; ii++) {
                                                        if (Graph[j]->to->neighbour[ii]->to == tmp_city)
                                                        {
                                                                Graph[j]->to->neighbour[ii]->SetVisit(true);
                                                                break;
                                                        }
                                                }
                                        }
                                        if (unvisited != 1) {
                                                for (int k = 0; k < tmp_road->to->neighbour.GetSize(); k++) {
                                                        if (tmp_road->to->neighbour[k]->visited == false) {
                                                                for (int j = 0; j < V; j++) {
                                                                        if (Graph[j]->to == tmp_road->to->neighbour[k]->to) {
                                                                                tmp_road = Graph[j];
                                                                                break;
                                                                        }
                                                                }
                                                                break;
                                                        }
                                                        else if (k == tmp_road->to->neighbour.GetSize() - 1 && unvisited != 1) {
                                                                for (int f = 0; f < V; f++) {
                                                                        if (Graph[f]->to == tmp_road->from) {
                                                                                tmp_road = Graph[f];
                                                                                break;
                                                                        }

                                                                }
                                                        }
                                                }
                                        }
                                                                                                        
                                        unvisited--;
                                }
                        }
                }

                if (type == 0) {
                        for (int i = 0; i < V; i++) {
                                if (Graph[i]->to == to) {
                                        std::cout << Graph[i]->distance << std::endl;
                                }
                        }
                }
                else if (type == 1) {
                        for (int i = 0; i < V; i++) {
                                if (Graph[i]->to == to) {
                                        String napis;
                                        Cities visited_cities;
                                        tmp_road = Graph[i];
                                        std::cout << Graph[i]->distance;
                                        while (tmp_road->from != from) {
                                                visited_cities.Add(tmp_road->from);

                                                for (int ii = 0; ii < V; ii++)
                                                {
                                                        if (Graph[ii]->to == tmp_road->from) {
                                                                tmp_road = Graph[ii];

                                                                break;
                                                        }
                                                }
                                        }
                                        if (visited_cities.tail != nullptr) {
                                                tmp_city = visited_cities.tail;
                                                while (tmp_city != nullptr) {
                                                        std::cout << " " << tmp_city->name;
                                                        tmp_city = tmp_city->prev;
                                                }
                                                
                                        }
                                        std::cout << std::endl;
                                }
                        }
                }
                for (int i = 0; i < V; i++) {
                        for (int ii = 0; ii <= Graph[i]->to->neighbour.GetSize() - 1; ii++) {
                                Graph[i]->to->neighbour[ii]->distance = -1;
                                Graph[i]->to->neighbour[ii]->SetVisit(false);
                                Graph[i]->to->neighbour[ii]->from = nullptr;
                        }
                        Graph[i]->SetVisit(false);
                        Graph[i]->distance = -1;
                        Graph[i]->from = nullptr;
                }
        }
        else std::cout << "0"<<std::endl;
}


int Cities::GetNumbers_of_Cities() {
        return Numbers_of_Cities;
}

Cities::~Cities(){
        head = nullptr;
        tail = nullptr; 
        Numbers_of_Cities = 0;
}