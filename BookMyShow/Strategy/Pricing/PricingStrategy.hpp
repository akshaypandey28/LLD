#pragma once
#include<iostream>
#include <vector>
#include "../../Entity/Seat.hpp"

using namespace std;

class PricingStrategy {
public:
    virtual double calculatePrice(const vector<Seat*>& seats) = 0;
    virtual ~PricingStrategy() = default;
};
