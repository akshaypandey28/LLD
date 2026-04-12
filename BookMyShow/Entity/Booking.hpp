#pragma once
#include<iostream>
#include "User.hpp"
#include "Seat.hpp"
#include "Show.hpp"
#include "Payment.hpp"
using namespace std;

class Booking{
private:
    int id;
    User* user;
    vector<Seat*> seats; //list of seats for a user
    Show* show;
    Payment* payment;
    double totalAmount;
    static int counter;
    friend class BookingBuilder;

    Booking() : user(nullptr), show(nullptr), totalAmount(0.0), payment(nullptr),id(counter++) {}
public :
    void confirmBooking(){
        for(auto seat: seats){
            seat->setStatus(SeatStatus::BOOKED);
        }
    }

    const int& getId() const {
        return id;
    }

    User* getUser() const {
        return user;
    }

    const vector<Seat*>& getSeats() const {
        return seats;
    }

    Show* getShow() const {
        return show;
    }

    Payment* getPayment() const {
        return payment;
    }

    double getTotalAmount() const {
        return totalAmount;
    }
};

class BookingBuilder{
private:
    Booking* booking;       // HAS-A Booking

public:
    BookingBuilder() {
        booking = new Booking();
    }

    BookingBuilder& setUser(User* user) {
        booking->user = user;
        return *this;
    }

    BookingBuilder& setShow(Show* show) {
        booking->show = show;
        return *this;
    }

    BookingBuilder& setSeats(const vector<Seat*>& seats) {
        booking->seats = seats;
        return *this;
    }

    BookingBuilder& setTotalAmount(double totalAmount) {
        booking->totalAmount = totalAmount;
        return *this;
    }

    BookingBuilder& setPayment(Payment* payment) {
        booking->payment = payment;
        return *this;
    }

    Booking* build() {
        return booking;
    }
};

int Booking::counter=0;