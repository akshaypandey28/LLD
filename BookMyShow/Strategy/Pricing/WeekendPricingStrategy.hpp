#pragma once
#include<iostream>
#include "PricingStrategy.hpp"
#include "../../enums/SeatType.hpp"

using namespace std;

class WeekendPricingStrategy : public PricingStrategy {
private:
    static const double WEEKEND_SURCHARGE = 1.2;

public:
    double calculatePrice(const vector<Seat*>& seats) override {
    
    double basePrice = 0.0;
    for (const auto& seat : seats) {
        basePrice += getSeatTypePrice(seat->getType());
    }
    return basePrice * WEEKEND_SURCHARGE;
    }
};