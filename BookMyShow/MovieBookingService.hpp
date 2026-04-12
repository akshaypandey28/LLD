#pragma once

#include<iostream>
#include<string>
#include<unordered_map>
#include<vector>
#include<mutex>
#include "Entity/City.hpp"
#include "Entity/Cinema.hpp"
#include "Entity/Movie.hpp"
#include "Entity/User.hpp"
#include "Entity/Show.hpp"
#include "Entity/Cinema.hpp"
#include "BookingManager.hpp"
#include "SeatLockManager.hpp"

using namespace std;

class MovieBookingService {
private:
    unordered_map<int,City*> cities; // cityId to City object mapping
    unordered_map<int,Cinema*> cinemas; // cinemaId to Cinema object mapping
    unordered_map<int,Movie*> movies; // movieId to Movie object mapping
    unordered_map<int,User*> users; // userId to User object mapping
    unordered_map<int,Show*> shows; // showId to Show object mapping

    BookingManager* bookingManager; // Booking manager to handle bookings
    SeatLockManager* seatLockManager; // Seat lock manager to handle seat locking

    static MovieBookingService* instance; // Singleton instance
    static mutex mtx; // Mutex for thread-safe singleton initialization

    MovieBookingService() {
        bookingManager = new BookingManager(new SeatLockManager());
    }
public:
    

    static MovieBookingService* getInstance(){  
        if(instance==nullptr){
            lock_guard<mutex> lock(mtx); // lock for thread safety
            if(instance==nullptr){
                instance=new MovieBookingService();
            }   
        }
        return instance;
    }


    City* addCity(const string& name){
        City* city=new City(name);
        cities[city->getId()]=city;
        return city;
    }


    void addMovie(Movie* movie){
        movies[movie->getId()]=movie;
    }


    Cinema* addCinema(const string& name,const int& cityId,const vector<Screen*>& screens){
        City* city=cities[cityId];
        if(city==nullptr){
            cout<<"City with id "<<cityId<<" does not exist.\n";
            return nullptr;
        }
        Cinema* cinema=new Cinema(name,city,screens);
        cinemas[cinema->getId()]=cinema;
        return cinema;
    }

    //add Shows
    Show* addShow(Movie* movie,Screen* screen,const string& startTime,PricingStrategy* pricingStrategy){
        Show* show=new Show(movie,screen,startTime,pricingStrategy);
        shows[show->getId()]=show;
        return show;
    }

    //add User
    User* createUser(const string& name,const string& email){
        User* user=new User(name,email);
        users[user->getId()]=user;
        return user;
    }


    Booking* bookTickets(const int& userId,const int& showId,const vector<Seat*>& seats,PaymentStrategy* paymentStrategy){
        User* user=users[userId];
        Show* show=shows[showId];

        if(user==nullptr){
            cout<<"User with id "<<userId<<" does not exist.\n";
            return nullptr;
        }

        if(show==nullptr){
            cout<<"Show with id "<<showId<<" does not exist.\n";
            return nullptr;
        }

        return bookingManager->createBooking(user,show,seats,paymentStrategy);
    }

    //search functionality
    vector<Show*> findShows(const string& movieTitle,const string& cityName){
        vector<Show*> result;
        for(const auto& [id,show] : shows){
            if(show->getMovie()->getTitle() == movieTitle){
                Cinema* cinema = findCinemaByShow(show);
                if(cinema and cinema->getCity()->getName() == cityName){
                    result.push_back(show);
                }
            }
        }
        return result;
    }


    void shutDown(){
        cout<<"Shutting down Movie Booking Service...\n";
        cout<<"-----------------------------------------------------------------"<<endl;
        seatLockManager->shutdown();
    }

private:
    Cinema* findCinemaByShow(Show* show){
        for(const auto& [id,cinema] : cinemas){
            for(const auto& screen : cinema->getScreens()){
                if(screen->getId() == show->getScreen()->getId()){
                    return cinema;
                }
            }
        }
        return nullptr;
    }
};


MovieBookingService* MovieBookingService::instance=nullptr;
mutex MovieBookingService::mtx;