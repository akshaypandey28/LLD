#pragma once
#include<iostream>
#include <string>

using namespace std;

class City {
private:
    int id;
    string name;
    static int counter; 
public:
    City(const string& name) {
        this->id = counter++; // Assign a unique ID to each City instance
        this->name = name;
    }

    const int& getId() const {
        return id;
    }

    const string& getName() const {
        return name;
    }
};

int City::counter = 0; 
