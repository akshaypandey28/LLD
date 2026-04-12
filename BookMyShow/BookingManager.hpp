#pragma once
#include<iostream>
#include<vector>
#include "SeatLockManager.hpp"
#include "Entity/Booking.hpp"
#include "Entity/User.hpp"
#include "Entity/Show.hpp"
#include "Entity/Seat.hpp"
#include "Entity/Payment.hpp"
#include "Enums/PaymentStatus.hpp"
#include "Strategy/Payment/PaymentStrategy.hpp"
using namespace std;

class BookingManager {
private:
    SeatLockManager* seatLockManager;
public:
    BookingManager(SeatLockManager* seatLockManager) {
        this->seatLockManager = seatLockManager;
    }

    Booking* createBooking(User* user,Show* show,const vector<Seat*>& seats,PaymentStrategy* paymentStrategy){
        // 1 => lock the seats
        seatLockManager->lockSeats(show,seats,user->getId());


        // 2 => calculate the total price
        double totalAmount = show->getPricingStrategy()->calculatePrice(seats);


        // 3 => process payment
        Payment* payment = paymentStrategy->pay(totalAmount);


        // 4 => if payment is successful , create the booking
        if(payment->getStatus() == PaymentStatus::SUCCESS){
            Booking* booking = BookingBuilder()
                .setUser(user)
                .setShow(show)
                .setSeats(seats)
                .setTotalAmount(totalAmount)
                .setPayment(payment)
                .build();
            
            
            // 5 => confirm the booking by marking the seats as booked
            booking->confirmBooking();
            
            seatLockManager->unlockSeats(show,seats,user->getId());

            return booking;
        }
        else{
            cout<<"Payment failed for user "<<user->getId()<<" for show "<<show->getId()<<endl;
            return nullptr;
        }
    }
};