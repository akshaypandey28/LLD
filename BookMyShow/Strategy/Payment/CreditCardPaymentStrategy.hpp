#pragma once

#include <iostream>
#include <cstdlib>
#include <string>
#include "PaymentStrategy.hpp"
#include "../../Enums/PaymentStatus.hpp"
#include "../../Entity/Payment.hpp"

using namespace std;

class CreditCardPaymentStrategy : public PaymentStrategy {
private:
    string cardNumber;
    string cvv;
    static int txnCounter;
public:
    CreditCardPaymentStrategy(const string& cardNumber, const string& cvv){
      this->cardNumber=cardNumber;
      this->cvv=cvv;
    }

    Payment* pay(double amount) override {
        cout << "Processing credit card payment of $" << amount << endl;
        cout<<"-----------------------------------------------------------------"<<endl;
        bool paymentSuccess = (rand() % 100) > 5;
        
        string txnId = "TXN_" + to_string(this->txnCounter++);
        return new Payment(
            amount,
            paymentSuccess ? PaymentStatus::SUCCESS : PaymentStatus::FAILURE,
            txnId
        );
    }
};

int CreditCardPaymentStrategy::txnCounter = 0;
