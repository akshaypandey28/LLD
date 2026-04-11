#pragma once

#include <string>
#include "../Enums/PaymentStatus.hpp"

using namespace std;

class Payment {
private:
    int id;
    double amount;
    PaymentStatus status;
    string transactionId;

    static int counter;
public:
    Payment(double amount, PaymentStatus status, const string& transactionId) {
        this->amount = amount;
        this->status = status;
        this->transactionId = transactionId;
        this->id = counter++;
    }

    const int& getId() const {
        return id;
    }

    double getAmount() const {
        return amount;
    }

    PaymentStatus getStatus() const {
        return status;
    }

    const string& getTransactionId() const {
        return transactionId;
    }
};

int Payment::counter=0;
