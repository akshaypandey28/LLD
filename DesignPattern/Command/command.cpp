#include<iostream>
#include<vector>
using namespace std;
class Light{
public:
    void on(){
        cout<<"Light on"<<endl;
    }
    void off(){
        cout<<"light off"<<endl;
    }
    
    ~Light(){
        cout<<"Destructor of Light"<<endl;
    }
};

class Fan {
public:
    void on()  { 
        cout << "Fan on" << endl; 
    }
    void off() { 
        cout << "Fan off" << endl; 
    }
    
    ~Fan(){
        cout<<"Destructor of Fan"<<endl;
    }
};


class ICommand{
public:
    virtual void execute()=0;
    virtual void undo()=0;
    
    virtual ~ICommand(){
        cout<<"Destructor of ICommand"<<endl;
    }
};

// Concrete Command for Light
class LightCommand : public ICommand {
private:
    Light* light;

public:
    LightCommand(Light* l) { 
        light = l; 
    }

    void execute() override{ 
        light->on(); 
    }

    void undo() override{ 
        light->off(); 
    }
};

// Concrete Command for Fan
class FanCommand : public ICommand {
private:
    Fan* fan;

public:
    FanCommand(Fan* f) { 
        fan = f; 
    }
    void execute() override { 
        fan->on(); 
    }
    void undo() override{ 
        fan->off(); 
    }
};

class RemoteControl{
private:
    static const int numButtons=4;
    ICommand* buttons[numButtons];
    bool pressed[numButtons];
    
public:
    RemoteControl(){
        for(int i=0; i<numButtons; i++){
            buttons[i]=NULL;
            pressed[i]=false;
        }
    }
    
    void setCommand(int idx,ICommand* cmd){
        if(idx>=0 and idx<numButtons){
            if(buttons[idx]!=NULL) delete buttons[idx];
            
            buttons[idx]=cmd;
            pressed[idx]=false;
        }
    }
    
    void pressButton(int idx){
        if(idx>=0 and idx<numButtons and buttons[idx]!=NULL){
            if(pressed[idx]==false) buttons[idx]->execute();
            else buttons[idx]->undo();
            
            pressed[idx]=!pressed[idx];
        }
        else cout<<"No command is assigned at button "<<idx<<endl;
    }
    
    ~RemoteControl(){
        for(int i=0; i<numButtons; i++){
            if(buttons[i]!=NULL) delete buttons[i];
        }
    }
};
int main(){
    Light* light=new Light();
    Fan* fan=new Fan();
    
    RemoteControl* remote=new RemoteControl();
    
    remote->setCommand(0,new LightCommand(light));
    remote->setCommand(1,new FanCommand(fan));
    
    //button pressing for light
    cout<<"--- Pressing button of Light ---"<<endl;
    remote->pressButton(0); // on
    remote->pressButton(0); //off
    
    
    //button pressing for fan
    cout<<"--- Pressing button for fan ---"<<endl;
    remote->pressButton(1); //on
    remote->pressButton(1);//off
    
    
    //button pressing for random command with random idx passing
    cout << "--- Pressing Unassigned Button 2 ---" << endl;
    remote->pressButton(2);
    
    delete remote;
    delete light;
    delete fan;
}

