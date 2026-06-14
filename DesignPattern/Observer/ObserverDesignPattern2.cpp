#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
/* 
This version keeps both sides synchronized:

Subscriber stores subscribed channels.
Channel stores subscribers.
subscribe() updates both lists.
unsubscribe() updates both lists.
uploadVideo() notifies all current subscribers.
*/
using namespace std;

class IChannel;

class ISubscriber {
public:
    virtual void subscribe(IChannel* channel) = 0;
    virtual void unsubscribe(IChannel* channel) = 0;
    virtual void update(IChannel* channel, const string& videoTitle) = 0;
    virtual string getName() = 0;
    virtual ~ISubscriber() {}
};

class IChannel {
public:
    virtual void addSubscriber(ISubscriber* subscriber) = 0;
    virtual void removeSubscriber(ISubscriber* subscriber) = 0;
    virtual void uploadVideo(const string& videoTitle) = 0;
    virtual string getName() = 0;
    virtual ~IChannel() {}
};

class Channel : public IChannel {
private:
    string name;
    vector<ISubscriber*> subscribers;

public:
    Channel(const string& name) : name(name) {}

    void addSubscriber(ISubscriber* subscriber) override {
        if (find(subscribers.begin(), subscribers.end(), subscriber) == subscribers.end()) {
            subscribers.push_back(subscriber);
        }
    }

    void removeSubscriber(ISubscriber* subscriber) override {
        auto it = find(subscribers.begin(), subscribers.end(), subscriber);

        if (it != subscribers.end()) {
            subscribers.erase(it);
        }
    }

    void uploadVideo(const string& videoTitle) override {
        cout << "\n[" << name << " uploaded \"" << videoTitle << "\"]\n";

        for (auto subscriber : subscribers) {
            subscriber->update(this, videoTitle);
        }
    }

    string getName() override {
        return name;
    }

    void showSubscribers() {
        cout << "\nSubscribers of " << name << ":\n";

        for (auto subscriber : subscribers) {
            cout << subscriber->getName() << '\n';
        }
    }
};

class Subscriber : public ISubscriber {
private:
    string name;
    vector<IChannel*> channels;

public:
    Subscriber(const string& name) : name(name) {}

    string getName() override {
        return name;
    }

    void subscribe(IChannel* channel) override {
        if (find(channels.begin(), channels.end(), channel) == channels.end()) {
            channels.push_back(channel);
            channel->addSubscriber(this);
        }
    }

    void unsubscribe(IChannel* channel) override {
        auto it = find(channels.begin(), channels.end(), channel);

        if (it != channels.end()) {
            channels.erase(it);
            channel->removeSubscriber(this);
        }
    }

    void update(IChannel* channel, const string& videoTitle) override {
        cout << "Hey " << name
             << ", " << channel->getName()
             << " uploaded a new video: "
             << videoTitle << '\n';
    }

    void showChannels() {
        cout << "\n" << name << " subscribed channels:\n";

        for (auto channel : channels) {
            cout << channel->getName() << '\n';
        }
    }
};

int main() {
    IChannel* coderArmy = new Channel("CoderArmy");
    IChannel* takeUForward = new Channel("TakeUForward");

    ISubscriber* akshay = new Subscriber("Akshay");
    ISubscriber* varun = new Subscriber("Varun");
    ISubscriber* tarun = new Subscriber("Tarun");

    akshay->subscribe(coderArmy);
    akshay->subscribe(takeUForward);

    varun->subscribe(coderArmy);

    tarun->subscribe(coderArmy);
    tarun->subscribe(takeUForward);

    coderArmy->uploadVideo("Observer Pattern Tutorial");

    takeUForward->uploadVideo("Graph Theory Playlist");

    akshay->unsubscribe(coderArmy);

    cout << "\nAfter Akshay unsubscribes from CoderArmy:\n";

    coderArmy->uploadVideo("Strategy Pattern Tutorial");

    delete coderArmy;
    delete takeUForward;
    delete akshay;
    delete varun;
    delete tarun;

    return 0;
}