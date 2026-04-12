#pragma once
#include<iostream>
#include <string>
#include <vector>
#include "City.hpp"
#include "Screen.hpp"

using namespace std;

class Cinema {
private:
    int id;
    string name;
    City* city;
    vector<Screen*> screens;
    static int counter;
public:
    Cinema(const string& name,
           City* city, const vector<Screen*>& screens) {
        this->id = counter++; // Assign a unique ID to each Cinema instance
        this->name = name;
        this->city = city;
        this->screens = screens;
    }

    const int& getId() const {
        return id;
    }

    const string& getName() const {
        return name;
    }

    City* getCity() const {
        return city;
    }

    const vector<Screen*>& getScreens() const {
        return screens;
    }
};

int Cinema::counter = 0; 
