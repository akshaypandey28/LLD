#include<iostream>
#include<vector>
#include "Entity/City.hpp"
#include "Entity/Cinema.hpp"
#include "Entity/Movie.hpp"
#include "Entity/Screen.hpp"
#include "Entity/Seat.hpp"
#include "Entity/Show.hpp"
#include "Entity/Booking.hpp"
#include "Entity/User.hpp"
#include "Enums/SeatType.hpp"
#include "Enums/SeatStatus.hpp"
#include "Observer/UserObserver.hpp"
#include "MovieBookingService.hpp"
#include "Strategy/Pricing/WeekdayPricingStrategy.hpp"
#include "Strategy/Payment/CreditCardPaymentStrategy.hpp"
using namespace std;
int main(){
    MovieBookingService* service=MovieBookingService::getInstance();


    //add cities
    City* mumbai=service->addCity("Mumbai");
    City* delhi=service->addCity("Delhi");

    //add movies
    Movie* matrix = new Movie("The Matrix", 136);
    Movie* inception = new Movie("Inception", 148);

    service->addMovie(matrix);
    service->addMovie(inception);

    //create screens
    Screen* screen1 = new Screen();

    //add seats to screen1
    for(int i=1; i<=10; i++){
        screen1->addSeat(new Seat(1,i,i<=5 ? SeatType::REGULAR : SeatType::PREMIUM));
        screen1->addSeat(new Seat(2,i,i<=5 ? SeatType::REGULAR : SeatType::RECLINER));

    }


    //add cinema
    Cinema* pvrMumbai = service->addCinema("PVR Cinema",mumbai->getId(),{screen1});

    //pricing strategy
    WeekdayPricingStrategy* weekdayPricing = new WeekdayPricingStrategy();

    Show* matrixShow = service->addShow(matrix, screen1, "2024-10-01 19:00", weekdayPricing);
    Show* inceptionShow = service->addShow(inception, screen1, "2024-10-01 22:00", weekdayPricing);

    //User and Observer setup
    User* alice = service->createUser("Alice", "123@gmail.com");
    UserObserver* aliceObserver1 = new UserObserver(alice);
    inception->addObserver(aliceObserver1);


    //notify observers about new show
    inception->notifyObservers();

    //User story => alice wants to book tickets
    string cityName = "Mumbai";
    string movieTitle = "Inception";


    //search for shows
    vector<Show*> availableShows = service->findShows(movieTitle, cityName);

    if(availableShows.empty()){
        cout<<"No shows available for movie "<<movieTitle<<" in city "<<cityName<<endl;
        return 0;
    }

    Show* selectedShow = availableShows[0]; // Alice selects the first available show

    //view available seats for the selected show
    vector<Seat*> availableSeats;
    for(Seat* seat : selectedShow->getScreen()->getSeats()){
        if(seat->getStatus() == SeatStatus::AVAILABLE){
            availableSeats.push_back(seat);
        }
    }


    //print the available seats
    cout<<"Available seats for show "<<selectedShow->getMovie()->getTitle()<<" are: \n";
    for(size_t i=0; i<availableSeats.size(); i++){
        cout<<"Seat ID: "<<availableSeats[i]->getId()
            <<", Row: "<<availableSeats[i]->getRow()
            <<", Col: "<<availableSeats[i]->getCol()
            << ", Type: " << seatTypeToString(availableSeats[i]->getType()) << endl;
    }

    cout<<"-----------------------------------------------------------------"<<endl;
    cout<<"-----------------------------------------------------------------"<<endl;



    //Alice selects some seats to book
    vector<Seat*> desiredSeats = {availableSeats[0], availableSeats[1]}; // Alice selects the first two available seats
    cout<<"Alice is trying to book seats: ";
    for(size_t i=0; i<desiredSeats.size(); i++){
        cout<<desiredSeats[i]->getId();
        if(i<desiredSeats.size()-1) cout<<", ";
    }
    cout<<endl;
    cout<<"-----------------------------------------------------------------"<<endl;
    cout<<"-----------------------------------------------------------------"<<endl;


    //book tickets 
    CreditCardPaymentStrategy* paymentStrategy = new CreditCardPaymentStrategy("1234-5678-9012-3456", "123");
    Booking* booking = service->bookTickets(
        alice->getId(), 
        selectedShow->getId(),
        desiredSeats, 
        paymentStrategy
    );

    if(booking){
        cout<<"Booking for "<<booking->getUser()->getName()<<endl;
        cout<<"Booking successful! Booking ID: "<<booking->getId()<<endl;
        cout<<"Booked Seats: ";
        for(size_t i=0; i<booking->getSeats().size(); i++){
            cout<<booking->getSeats()[i]->getId();
            if(i<booking->getSeats().size()-1) cout<<", ";
        }
        cout<<endl;

        cout<<"Total Amount Paid: $"<<booking->getTotalAmount()<<endl;

        cout<<"Payment Transaction ID: "<<booking->getPayment()->getTransactionId()<<endl;

    }
    else{
        cout<<"Booking failed for user "<<alice->getName()<<endl;
    }
    cout<<"-----------------------------------------------------------------"<<endl;
    cout<<"-----------------------------------------------------------------"<<endl;
    //verify seats after booking
    cout<<"Seat status after booking attempt: \n";
    for(Seat* seat : desiredSeats){
        string statusSeat;
        switch(seat->getStatus()){
            case SeatStatus::AVAILABLE: statusSeat = "AVAILABLE"; break;
            case SeatStatus::BOOKED: statusSeat = "BOOKED"; break;
            case SeatStatus::LOCKED: statusSeat = "LOCKED"; break;
        }

        cout<<"Seat ID: "<<seat->getId()<<", Status: "<<statusSeat<<endl;
    }
    cout<<"-----------------------------------------------------------------"<<endl;
    service->shutDown();
    return 0;
}