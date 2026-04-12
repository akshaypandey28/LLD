#pragma once
#include<iostream>
using namespace std;

class MovieSubject;

class MovieObserver{
public:
    virtual void update(MovieSubject* movie)=0;
    virtual ~MovieObserver() = default;
};