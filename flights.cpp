#include "Flights.h"

Flights::Flights() {
        head = nullptr;
        tail = nullptr;
}

void Flights::Add(City* from, City* to, int time) {

        //TWORZENIE NOWEGO LOTU
        Flight* tmp_flight = new Flight(from, to, time);

        //PIERWSZY ELEMENT LISTY
        if (head == nullptr) {
                head = tmp_flight;
                tail = tmp_flight;
        }
        //KOLEJNY ELEMENT LISTY
        else {
                tail->next = tmp_flight;
                tail = tmp_flight;
        }
}

void Flights::Delete() {
        if (head == tail) {
                head = nullptr;
                tail = nullptr;
        }
        else {
                head = head->next;
        }
}

Flights::~Flights() {
        head = nullptr;
        tail = nullptr;
}