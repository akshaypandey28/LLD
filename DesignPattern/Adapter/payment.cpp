#include <iostream>
using namespace std;

// Target Interface
// Our application expects every payment system
// to provide a pay() function.
class Payment {
public:
    virtual void pay(double amount) = 0;
    virtual ~Payment() {}
};

// Adaptee
// Third-party payment gateway.
// We cannot modify this class.
class OldGateway {
public:
    void makePayment(double amount) {
        cout << "Payment of Rs." << amount
             << " processed through OldGateway\n";
    }
};

// Adapter
// Converts the interface expected by the client
// into the interface provided by OldGateway.
class PaymentAdapter : public Payment {
private:
    OldGateway gateway;

public:
    void pay(double amount) override {
        // Translate pay() call to makePayment()
        gateway.makePayment(amount);
    }
};

//Client
class Client {
public:
    void usePayment(Payment* payment,double amount) {
        payment->pay(1000);
    }
};
int main() {

    // Client works only with Payment interface
    Payment* payment = new PaymentAdapter();

    // Client calls pay()
    Client client;
    client.usePayment(payment,1000);

    delete payment;

    return 0;
}