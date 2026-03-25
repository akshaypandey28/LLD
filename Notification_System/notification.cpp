#include<iostream>
#include<string>
#include<vector>
#include <algorithm>
using namespace std;

class INotification{
    public:
    virtual string getContent()=0;
    virtual ~INotification() {
        cout<<"Destructor of INotification"<<endl;
    }
};

class SimpleNotification : public INotification{
private:
    string message;
public:
    SimpleNotification(string text){
        this->message=text;
    }
    
    string getContent() override{
        return message + "\n";
    }
};

class INotificationDecorator : public INotification{
protected:
    INotification* n;
public: 
    INotificationDecorator(INotification* n){
        this->n=n;
    }
    virtual ~INotificationDecorator() {
        cout<<"Destructor of INotificationDecorator"<<endl;
    }
};

class TimeStampDecorator : public INotificationDecorator{
public:
    TimeStampDecorator(INotification* n) : INotificationDecorator(n) {
        cout<<"TimeStampDecorator"<<endl;
    };
    string getContent() override{
        return "[2025-04-13 14:22:00] " + n->getContent() + "\n";
    }
};

class SignatureDecorator : public INotificationDecorator {
private:
    string signature;
public:
    SignatureDecorator(INotification* n, const string& sig) : INotificationDecorator(n) {
        signature = sig;
        cout<<"SignatureDecorator"<<endl;
    }
    string getContent() override {
        return n->getContent() + "-- " + signature + "\n";
    }
};


//this class is for observer
class IObserver{
public:
    virtual void update()=0;
    virtual ~ IObserver() {
        cout<<"IObserver Destructor"<<endl;
    }
};

//this class if for observable which actually manager adding removing observer
class IObervable{
public:
    virtual void addObserver(IObserver* observer)=0; 
    virtual void removeObserver(IObserver* observer)=0;
    
    virtual void notifyObserver()=0;
};

class NotificationObservable : public IObervable{
private:    
    vector<IObserver*> observers;
    INotification* currNotification;
public:
    
    NotificationObservable(){
        currNotification=NULL;
        cout<<"NotificationObservable class"<<endl;
    }
    
    void addObserver(IObserver* o) override{
        observers.push_back(o);
    }
    
    void removeObserver(IObserver* o) override{
        observers.erase(remove(observers.begin() , observers.end() , o) , observers.end());
    }
    
    void notifyObserver() override{
        for (auto* observer : observers) {
            observer->update();
        }
    }
    
    void setNotification(INotification* notification){
        if(currNotification!=NULL) delete currNotification;
        currNotification=notification;
        notifyObserver();
    }
    
    
    INotification* getNotification(){
        return currNotification;
    }
    
    string getNotificationContent(){
        return currNotification->getContent();
    }
    
};

// Concrete Observer 1
class Logger : public IObserver {
private:
    NotificationObservable* notificationObservable;

public:
    Logger(NotificationObservable* observable) {
        this->notificationObservable = observable;
    }

    void update() {
        cout << "Logging New Notification : \n" << notificationObservable->getNotificationContent();
    }
};

/*============================
  Strategy Pattern Components (Concrete Observer 2)
=============================*/

// Abstract class for different Notification Strategies.
class INotificationStrategy {
public:    
    virtual void sendNotification(string content) = 0;
};

class EmailStrategy : public INotificationStrategy {
private:
    string emailId;
public:

    EmailStrategy(string emailId) {
        this->emailId = emailId;
    }

    void sendNotification(string content) override {
        // Simulate the process of sending an email notification, 
        // representing the dispatch of messages to users via email.​
        cout << "Sending email Notification to: " << emailId << "\n" << content;
    }
};

class SMSStrategy : public INotificationStrategy {
private:
    string mobileNumber;
public:

    SMSStrategy(string mobileNumber) {
        this->mobileNumber = mobileNumber;
    }

    void sendNotification(string content) override {
        // Simulate the process of sending an SMS notification, 
        // representing the dispatch of messages to users via SMS.​
        cout << "Sending SMS Notification to: " << mobileNumber << "\n" << content;
    }
};

class PopUpStrategy : public INotificationStrategy {
public:
    void sendNotification(string content) override {
        // Simulate the process of sending popup notification.
        cout << "Sending Popup Notification: \n" << content;
    }
};


class NotificationEngine : public IObserver{
private:
    NotificationObservable* notificationObservable;
    vector<INotificationStrategy*> notificationStrategies;
    

public:
    NotificationEngine(NotificationObservable* observable){
        this->notificationObservable=observable;
    }
    
    void addNotificationStrategy(INotificationStrategy* ns){
        this->notificationStrategies.push_back(ns);
    }
    
    void update(){
        string notificationContent = notificationObservable->getNotificationContent();
        for(const auto ele: notificationStrategies){
            ele->sendNotification(notificationContent);
        }
    }
};

/*============================
       NotificationService
=============================*/

// The NotificationService manages notifications. It keeps track of notifications. 
// Any client code will interact with this service.

// Singleton class
class NotificationService {
private:
    NotificationObservable* observable;
    static NotificationService* instance;
    vector<INotification*> notifications; //stores all notifications

    NotificationService() {
        // private constructor
        observable = new NotificationObservable();
    }

public:
    static NotificationService* getInstance() {
        if(instance == nullptr) {
            instance = new NotificationService();
        }
        return instance;
    }

    // Expose the observable so observers can attach.
    NotificationObservable* getObservable() {
        return observable;
    }

    // Creates a new Notification and notifies observers.
    void sendNotification(INotification* notification) {
        notifications.push_back(notification); // history
        observable->setNotification(notification);
    }

    ~NotificationService() {
        delete observable;
    }
};

NotificationService* NotificationService::instance = nullptr;
int main(){
     NotificationService* notificationService = NotificationService::getInstance();

    // Get Observable
    NotificationObservable* notificationObservable = notificationService->getObservable();
   
    // Create Logger Observer
    Logger* logger = new Logger(notificationObservable);

    // Create NotificationEngine observers.
    NotificationEngine* notificationEngine = new NotificationEngine(notificationObservable);

    notificationEngine->addNotificationStrategy(new EmailStrategy("random.person@gmail.com"));
    notificationEngine->addNotificationStrategy(new SMSStrategy("+91 9876543210"));
    notificationEngine->addNotificationStrategy(new PopUpStrategy());

    // Attach these observers.
    notificationObservable->addObserver(logger);
    notificationObservable->addObserver(notificationEngine);

    // Create a notification with decorators.
    INotification* notification = new SimpleNotification("Your order has been shipped!");
    notification = new TimeStampDecorator(notification);
    notification = new SignatureDecorator(notification, "Customer Care");
    
    notificationService->sendNotification(notification);
    
    
    // INotification* notify=new SimpleNotification("akshay pandey");
    // cout<<notify->getContent()<<endl;
    
    // notify=new TimeStampDecorator(notify);
    // cout<<notify->getContent()<<endl;
    
    // notify=new SignatureDecorator(notify, "Customer Care");
    // cout<<notify->getContent()<<endl;
    
    //delete notify;
    return 0;
}



