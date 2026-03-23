#include<iostream>
#include<vector>
using namespace std;
class MySQLDatabase { // Low-level module
public:
    void saveToSQL(string user){
        cout<<"User Save to SQL"<<user<<endl;
    }
};

class MongoDBDatabase { // Low-level module
public:
    void saveToMongo(string user){
        cout<<"User Save to MongoDB"<<user<<endl;
    }
};

class UserService {  // High-level module (Tightly coupled)
private:
    MySQLDatabase sql; // Direct dependency on MySQL
    MongoDBDatabase mongo; // Direct dependency on MongoDB
public:
    void storeUserToSQL(string user){
        sql.saveToSQL(user);
    }

    void storeUserToMongoDB(string user){
        mongo.saveToMongo(user);
    }
};
int main(){
    UserService service;
    service.storeUserToMongoDB("Akshay");
    service.storeUserToSQL("Pandey");
return 0;
}