#pragma once
#include<iostream>
#include <string>
#include "../observer/MovieSubject.hpp"

using namespace std;

class Movie : public MovieSubject {
private:
    int id;
    string title;
    int durationInMinutes;
    static int counter;
public:
    Movie(const string& title, int durationInMinutes) {
        this->id = counter++; // Assign a unique ID to each Movie instance
        this->title = title;
        this->durationInMinutes = durationInMinutes;
    }

    const int& getId() const {
        return id;
    }

    const string& getTitle() const {
        return title;
    }

    int getDurationInMinutes() const {
        return durationInMinutes;
    }
};

int Movie::counter = 0; 
