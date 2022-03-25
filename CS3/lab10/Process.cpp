// demonstrates state design pattern
// Mikhail Nesterenko
// 2/23/2014

#include <iostream>
#include <string>
#include <queue>
#include <cstdlib>
#include <ctime>
using std::cin; using std::cout; using std::endl; 
using std::string; using std::to_string;
using std::queue;
using std::rand;

class State;

// context
class Process{
public:
    Process();

    // behaviors
    void admit();
    void dispatch();
    void interrupt();
    void exit();
    void eventComplete();
    void eventWait();
    string report();
    Process* clone();

    // part of implementation of state pattern
    void changeState(State* s){state_=s;}
private:
    int id_;
    static int next_id_;
    State* state_;
};

int Process::next_id_ = 0;

// absract state
class State{
public: 
    virtual void admit(Process*){};
    virtual void dispatch(Process*){};
    virtual void interrupt(Process*){};
    virtual void exit(Process*){};
    virtual void eventComplete(Process*){};
    virtual void eventWait(Process*){};
    virtual string report()=0;
    void changeState(Process* c, State* s){
        c->changeState(s);
    }
};

class New: public State{
public:
    static State* instance(){
        static State* onlyInstance = new New;
        return onlyInstance;
    }
    virtual void admit(Process*) override;
    string report() override {return "new";}
private:
    New() {}
    New(const New&) {}
    void operator=(const New&) {}
};

class Ready: public State{
public:
    static State* instance(){
        static State* onlyInstance = new Ready;
        return onlyInstance;
    }
    virtual void dispatch(Process*) override;
    string report() override {return "ready";}
private:
    Ready() {}
    Ready(const Ready&) {}
    void operator=(const Ready&) {}
};

class Running: public State{
public:
    static State* instance(){
        static State* onlyInstance = new Running;
        return onlyInstance;
    }
    virtual void interrupt(Process*) override;
    virtual void eventWait(Process*) override;
    virtual void exit(Process*) override;
    string report() override {return "running";}
private:
    Running() {}
    Running(const Running&) {}
    void operator=(const Running&) {}
};

class Waiting: public State{
public:
    static State* instance(){
        static State* onlyInstance = new Waiting;
        return onlyInstance;
    }
    virtual void eventComplete(Process*) override;
    string report() override {return "waiting";}
private:
    Waiting() {}
    Waiting(const Waiting&) {}
    void operator=(const Waiting&) {}
};

class Terminated: public State{
public:
    static State* instance(){
        static State* onlyInstance = new Terminated;
        return onlyInstance;
    }
    string report() override {return "terminated";}
private:
    Terminated() {}
    Terminated(const Terminated&) {}
    void operator=(const Terminated&) {}
};


// state transitions member functions
// New
void New::admit(Process *c) {
   changeState(c, Ready::instance());
}

// Ready
void Ready::dispatch(Process *c) {
   changeState(c, Running::instance());
}

// Running
void Running::interrupt(Process *c) {
   changeState(c, Ready::instance());
}

void Running::eventWait(Process *c) {
   changeState(c, Waiting::instance());
}

void Running::exit(Process *c) {
   changeState(c, Terminated::instance());
}

// Waiting
void Waiting::eventComplete(Process *c) {
   changeState(c, Ready::instance());
}


// Process member functions
Process::Process() {
    id_ = next_id_;
    next_id_++;
    state_ = New::instance();
}

// handles/behaviors
void Process::admit() {state_->admit(this);}
void Process::dispatch() {state_->dispatch(this);}
void Process::interrupt() {state_->interrupt(this);}
void Process::exit() {state_->exit(this);}
void Process::eventComplete() {state_->eventComplete(this);}
void Process::eventWait() {state_->eventWait(this);}
string Process::report() {return string("Process ") + to_string(id_) + string(" is ") + state_->report();}
Process* Process::clone() {
    Process* clone = new Process();
    clone->state_ = state_;
    return clone;
}

int main(){
    srand(time(nullptr));

    queue<Process*> ready_queue, waiting_queue; // The queues

    Process prototype; // The prototype

    for (int i = 0; i < 4; i++) { // Populate the ready queue
        ready_queue.push(prototype.clone());
        cout << ready_queue.back()->report() << endl;
        ready_queue.back()->admit();
        cout << ready_queue.back()->report() << endl;
    }

    while (!ready_queue.empty() || !waiting_queue.empty()) { // While at least 1 process exists
        ready_queue.front()->dispatch();
        cout << ready_queue.front()->report() << endl;
        int r = rand() % 3;
        cout << r << endl;
        if (r == 0) { // exit
            ready_queue.front()->exit();
            cout << ready_queue.front()->report() << endl;
            Process* to_del = ready_queue.front();
            ready_queue.pop();
            delete to_del;
        } else if (r == 1) { // be preempted
            ready_queue.front()->interrupt();
            cout << ready_queue.front()->report() << endl;
            ready_queue.push(ready_queue.front());
            ready_queue.pop();
        } else { // execute an I/O request
            ready_queue.front()->eventWait();
            cout << ready_queue.front()->report() << endl;
            waiting_queue.push(ready_queue.front());
            ready_queue.pop();
            waiting_queue.front()->eventComplete();
            cout << waiting_queue.front()->report() << endl;
            ready_queue.push(waiting_queue.front());
            waiting_queue.pop();
        }
    }
}
