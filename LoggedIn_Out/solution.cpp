#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <chrono>
#include <ctime>

using namespace std;
using namespace std::chrono;

class UserSession {
public:
    string userName;
    system_clock::time_point loginTime;
    system_clock::time_point logoutTime;
    bool isLoggedOut;

    UserSession() : isLoggedOut(false) {}

    UserSession(const string& name) : userName(name), isLoggedOut(false) {
        loginTime = system_clock::now(); 
    }

    void markLoggedOut() {
        logoutTime = system_clock::now(); 
        isLoggedOut = true;
    }

    void printSession() const {
        cout<<"User: "<<userName<<endl;
        time_t loginT=system_clock::to_time_t(loginTime);
        //cout<<"loginT: "<<loginT<<endl;
        
        string loginStr=ctime(&loginT);
        //cout<<"loginStr: "<<loginStr;
        loginStr.pop_back();
        cout<<"Logged in: "<<loginStr<<endl;

        if(isLoggedOut){
            time_t logoutT=system_clock::to_time_t(logoutTime);
            //cout<<"logoutT: "<<logoutT<<endl;
            string logoutStr=ctime(&logoutT);
            //cout<<"logoutStr: "<<logoutStr;
            logoutStr.pop_back();
            cout<<"Logged out: "<<logoutStr<<endl;
        }
        else{
            cout<<"Status: Active\n";
        }
    }
};

class SessionManager {
private:
    unordered_map<string, UserSession> activeSessions;
    vector<UserSession> sessionHistory;

public:
    void login(const string& userName) {
        if (activeSessions.find(userName) != activeSessions.end()) {
            cout << "User '" << userName << "' is already logged in.\n";
            return;
        }
        
        activeSessions[userName] = UserSession(userName);
        cout << "User '" << userName << "' logged in successfully.\n";
    }

    void logout(const string& userName) {
        auto it = activeSessions.find(userName);
        if (it == activeSessions.end()) {
            cout << "User '" << userName << "' is not logged in.\n";
            return;
        }

        UserSession session = it->second;
        activeSessions.erase(it);
        session.markLoggedOut();
        sessionHistory.push_back(session);
        cout << "User '" << userName << "' logged out successfully.\n";
    }

    void printHistory() const {
        cout << "\n--- Completed Session History ---\n";
        if (sessionHistory.empty()) {
            cout << "No completed sessions yet.\n";
        }
        for (const auto& session : sessionHistory) {
            session.printSession();
        }
    }
};

int main() {
    SessionManager manager;

    manager.login("Alice");
    manager.login("Bob");
    manager.logout("Alice");
    manager.printHistory();

    return 0;
}