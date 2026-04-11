#pragma once
#include<iostream>
#include <string>
using namespace std;

class User {
private:
    int id;
    string name;
    string email;

    static int counter;

public:
    User(const string& name, const string& email) {
        this->name = name;
        this->email = email;
        this->id = counter++;
    }

    const int& getId() const {
        return id;
    }

    const string& getName() const {
        return name;
    }

    const string& getEmail() const {
        return email;
    }
};

int User::counter = 0;
