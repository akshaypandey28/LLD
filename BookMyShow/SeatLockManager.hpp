#pragma once
#include<iostream>
#include<mutex> //this is used to prevent multiple threads from accessing the same resource at the same time
#include<thread> //used to create and manage threads for parallel execution in C++.
#include<unordered_map> 
#include "Entity/Show.hpp"
#include "Entity/Seat.hpp"
#include "Enums/SeatStatus.hpp"
using namespace std;

class SeatLockManager {
private:
    unordered_map<int,unordered_map<int,int>> lockedSeats; //(showId, (seatId, userId))
    mutex mtx; //to ensure that only one thread can access the lockedSeats map at a time
    static constexpr long LOCK_TIMEOUT_MS = 500; // Lock timeout in milliseconds
public:
    void lockSeats(Show* show,const vector<Seat*>& seats,const int userId){
        lock_guard<mutex> lock(mtx);
        
        for(const auto& seat : seats){
            if(seat->getStatus() != SeatStatus::AVAILABLE){
                cout<<"Seat "<<seat->getId()<<" is not available for booking.\n";
                return;
            }
        }

        //now we can lock the seats for the user
        int showId = show->getId();

        for(const auto& seat : seats){
            seat->setStatus(SeatStatus::LOCKED);
            int seatId = seat->getId();
            lockedSeats[showId][seatId] = userId;
        }

        cout<<"Seats locked for user "<<userId<<" for show "<<showId<<" are ";

        for(int i=0; i<seats.size(); i++){
            cout<<seats[i]->getId();
            if(i<seats.size()-1) cout<<", ";
        }

        cout<<endl;
        cout<<"-----------------------------------------------------------------"<<endl;
        cout<<"-----------------------------------------------------------------"<<endl;

        thread([this,show,seats,userId](){
            this_thread::sleep_for(chrono::milliseconds(LOCK_TIMEOUT_MS));
            unlockSeats(show,seats,userId);
        }).detach();
    }

    void unlockSeats(Show* show,const vector<Seat*>& seats,const int userId){
        lock_guard<mutex> lock(mtx);

        auto showIt = lockedSeats.find(show->getId()); //(seatId, userId)

        if(showIt != lockedSeats.end()){
            auto& showLockSeats = showIt->second; // it's a map of seatId to userId

            for(const auto& seat : seats){
                auto seatIt = showLockSeats.find(seat->getId());

                if(seatIt != showLockSeats.end() and seatIt->second == userId){
                    showLockSeats.erase(seatIt);
                    if(seat->getStatus() == SeatStatus::LOCKED){
                        seat->setStatus(SeatStatus::AVAILABLE);
                        cout<<"Unlocked Seat: "<<seat->getId()<<" due to timeout."<<endl;
                    }
                    else{
                        cout << "Seat "<<seat->getId() <<" already booked; skipping unlock " << endl;
                    }
                }
            }
            cout<<"-----------------------------------------------------------------"<<endl;
            cout<<"-----------------------------------------------------------------"<<endl;
            if(showLockSeats.empty()){
                lockedSeats.erase(showIt);
            }
        }
    }
    void shutdown(){
        cout<<"Shutting down SeatLockManager, clearing all locks.\n";
    }    
};