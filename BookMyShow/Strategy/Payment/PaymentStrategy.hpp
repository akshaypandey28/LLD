#pragma once

#include<iostream>
#include "../../Entity/Payment.hpp"

using namespace std;

class PaymentStrategy {
public:
    virtual Payment* pay(double amount) = 0;
    virtual ~PaymentStrategy() = default;
};
