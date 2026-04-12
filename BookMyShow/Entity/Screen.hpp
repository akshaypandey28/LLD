#pragma once
#include<iostream>
#include <string>
#include <vector>
#include "Seat.hpp"

using namespace std;

class Screen {
private:
    int id;
    vector<Seat*> seats;
    static int counter;
public:
    Screen() {
        this->id = counter++; // Assign a unique ID to each Screen instance
    }

    void addSeat(Seat* seat) {
        seats.push_back(seat);
    }

    const int& getId() const {
        return id;
    }

    const vector<Seat*>& getSeats() const {
        return seats;
    }
};

int Screen::counter = 0;
