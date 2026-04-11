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

public:
    Screen(const string& id) {
        this->id = id;
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
