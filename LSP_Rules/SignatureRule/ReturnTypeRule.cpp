#include<iostream>
using namespace std;

// Return Type Rule : 
// Subtype overriden method return type should be either identical 
// or narrower then the parent method's return type.
// This is also called as return type covariance.
// C++ enforces this by covariance.
class Animal {
    //some common animal methods
};

class Dog : public Animal {
    // additional dog methods    
};

class Parent {
public:
    virtual Animal* getAnimal(){
        cout<<"Parent returning Animal class"<<endl;
        return new Animal();
    }
};

class Child : public Parent {
public:
    Dog* getAnimal() override{
        cout<<"Child returning Dog class"<<endl;
        return new Dog();
    }
};


class Client {
private:
    Parent* p;
public:
    Client(Parent* p){
        this->p=p;
    }

    void takeAnimal(){
        p->getAnimal();
    }
};

int main(){
    Parent* p=new Parent();
    Child* c=new Child();

    Client* cl=new Client(c);
    //Client * client = new Client(p);
    cl->takeAnimal();
    return 0;
}
