#pragma once
#include<iostream>
#include <string>

using namespace std;

class City {
private:
    int id;
    string name;

public:
    City(const int& id, const string& name) {
        this->id = id;
        this->name = name;
    }

    const int& getId() const {
        return id;
    }

    const string& getName() const {
        return name;
    }
};
