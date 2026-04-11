#include<iostream>
#include "MovieObserver.hpp"
#include "../Entity/User.hpp"
#include "../Entity/Movie.hpp"
using namespace std;

class UserObserver : public MovieObserver{
private:
    User* user;
public:
    UserObserver(User* user){
        this->user=user;
    }

    void update(MovieSubject* movieSubject) override {
        Movie* movie = static_cast<Movie*>(movieSubject);
        cout << "Notification for " << user->getName()
            << " (" << user->getId() << "): Movie '"
            << movie->getTitle() << "' is now available for booking!" << endl;
    }
};