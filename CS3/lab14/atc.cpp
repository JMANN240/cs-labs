// mediator-based air traffic control
// Mikhail Nesterenko
// 4/23/2021

#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <cstdio>
#include <ctime>

// for timed sleep
#include <thread>
#include <chrono>


using std::cout; using std::cin; using std::endl;
using std::string;

// abstract mediator
class Controller{
public:
   virtual void join(class Flight*)=0;
   virtual void leave(class Flight*)=0;
   virtual void broadcast() = 0;
   virtual void observe() = 0;
};


// concrete mediator
// tower, runway clearance
class Tower: public Controller{
public:
   void join(class Flight*) override;
   void leave(class Flight*) override;
   void broadcast() override;
   void observe() override;
private:
   std::set<class Flight*> waiting_;
};


// abstract colleague
class Flight {
public:
   Flight(Controller *controller):controller_(controller), status_(Status::waiting){
      task_ = rand() % 2 ? Task::taxiing : Task::approaching;
      controller_->join(this);
   }
   void receive(const string &msg){
      if (msg.find(flightNo_) != string::npos || msg.find("all") != string::npos){
	 if(msg.find("clear") != string::npos){
	    cout << flightNo_ << " roger that, ";
	    cout << (task_ == Task::taxiing ? "taking off" : "landing") << endl;
	    status_ = Status::cleared;
	 } else if(msg.find("status") != string::npos) {
	    cout << flightNo_ << " waiting to " 
	         << (task_ == Task::taxiing ? "take off" : "land") << endl;
	 } else
	    cout << "Tower, this is " << flightNo_ << " please repeat." << endl;
      }
   }
   bool isCleared(){return status_ == Status::cleared;}
   void proceed(){
      std::this_thread::sleep_for(std::chrono::seconds(rand()%3+1)); // wait a while    
      cout << flightNo_ << 
	   (task_ == Task::taxiing ? " taken off" : " landed")
	   << ". Have a good day!" << endl; 
      controller_->leave(this);
   }

protected:
   string flightNo_;
   Controller *controller_;
   enum class Task {taxiing, approaching};  Task task_;
   enum class Status {waiting, cleared};    Status status_;
};

// concrete colleagues
class Airbus: public Flight{
public:
   Airbus(Tower *tower): Flight(tower){
      static const std::vector<string> companies = 
	 {"AirFrance", "KLM", "Aeroflot", "Lufthansa", 
	  "BritishAirways", "Alitalia", "Iberia", "Avianca"};
      flightNo_ = companies[rand() % companies.size()] +
	          std::to_string(rand() % 1000);
      cout << flightNo_ << " requesting "
	   << (task_ == Task::taxiing ? "takeoff" : "landing") << endl;
   }
};

class Boeing: public Flight{
public:
   Boeing(Tower *tower): Flight(tower){
      static const std::vector<string> companies = 
	 {"Delta", "United", "JetBlue", "SouthWest"};
      flightNo_ = companies[rand() % companies.size()] + std::to_string(rand() % 1000);
      cout << flightNo_ << " requesting "
	   << (task_ == Task::taxiing ? "takeoff" : "landing") << endl;
   }
};


// member functions for Tower
void Tower::broadcast() {
   cout << "Tower: ";
   string msg;
   getline(cin,msg);
   if(!msg.empty())
      for(auto f: waiting_) f->receive(msg);
}


void Tower::observe() {
   Flight *toProceed = nullptr;
   for(auto f: waiting_)
      if(f->isCleared()){
	 if(toProceed == nullptr)
	    toProceed = f;
	 else // more than a single plane cleared
	    cout << "MAYDAY! MAYDAY! MAYDAY! " << endl;
      }
   if(toProceed != nullptr) toProceed ->proceed();
}

void Tower::leave(Flight *f) {
   waiting_.erase(f);
   delete f;
}

void Tower::join(Flight *f) {
   waiting_.insert(f);
}


int main(){
   srand(time(nullptr));
   Tower jfk;

   new Boeing(&jfk);
   new Airbus(&jfk);
   new Boeing(&jfk);
   new Airbus(&jfk);

   while(true){
      jfk.broadcast();
      jfk.observe();
      if(rand() % 2){
	 if (rand() % 2)
	    new Boeing(&jfk);
	 else
	    new Airbus(&jfk);
      }
   }
}
