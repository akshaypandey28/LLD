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

public:
    Movie(const int& id, const string& title, int durationInMinutes) {
        this->id = id;
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
