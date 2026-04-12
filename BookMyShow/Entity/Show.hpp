#pragma once

#include <string>
#include "Movie.hpp"
#include "Screen.hpp"
#include "../Strategy/Pricing/PricingStrategy.hpp"

using namespace std;

class Show {
private:
    int id;
    Movie* movie;
    Screen* screen;
    string startTime;
    PricingStrategy* pricingStrategy;
    static int counter;

public:
    Show(Movie* movie, Screen* screen,
         const string& startTime, PricingStrategy* pricingStrategy) {
        this->id = counter++; // Assign a unique ID to each Show instance
        this->movie = movie;
        this->screen = screen;
        this->startTime = startTime;
        this->pricingStrategy = pricingStrategy;
    }

    const int& getId() const {
        return id;
    }

    Movie* getMovie() const {
        return movie;
    }

    Screen* getScreen() const {
        return screen;
    }

    const string& getStartTime() const {
        return startTime;
    }

    PricingStrategy* getPricingStrategy() const {
        return pricingStrategy;
    }
};

int Show::counter = 0;
