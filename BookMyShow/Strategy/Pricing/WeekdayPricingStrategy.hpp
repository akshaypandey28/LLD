#pragma once
#include<iostream>
#include "PricingStrategy.hpp"
#include "../../enums/SeatType.hpp"

using namespace std;

class WeekdayPricingStrategy : public PricingStrategy {
public:
    double calculatePrice(const vector<Seat*>& seats) override {
        double total = 0.0;
        for (const auto& seat : seats) {
            total += getSeatTypePrice(seat->getType());
        }
        return total;
    }
};
