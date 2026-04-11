#include<iostream>
#include<vector>
#include<algorithm>
#include "MovieObserver.hpp"
using namespace std;

class MovieSubject{
private:
    vector<MovieObserver*> observers;
public:
    void addObserver(MovieObserver* observer) {
        observers.push_back(observer);
    }

    void removeObserver(MovieObserver* observer) {
        observers.erase(
            remove(observers.begin(), observers.end(), observer),
            observers.end()
        );
    }

    void notifyObservers() {
        for (auto* observer : observers) {
            observer->update(this);
        }
    }

    virtual ~MovieSubject() = default;
};