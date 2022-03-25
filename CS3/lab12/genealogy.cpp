// traversing genealogical tree using Composite and Visitors
// Mikhail Nesterenko
// 10/28/2015

#include <iostream>
#include <string>
#include <vector>

using std::cout; using std::endl; using std::cin;
using std::string; 
using std::vector;

class Person{ // component
public:
    Person(string firstName, Person* spouse, Person* father, Person* mother):
        firstName_(firstName), spouse_(spouse), father_(father), mother_(mother){}
    const string & getFirstName() const {return firstName_;}
    Person* getSpouse() const {return spouse_;}
    void setSpouse(Person* spouse){spouse_=spouse;}
    Person* getFather() const {return father_;}
    Person* getMother() const {return mother_;}
    virtual void accept(class PersonVisitor* ) = 0;  
    virtual const string getName() const = 0;
    virtual ~Person(){}
private:
    const string firstName_;
    Person* spouse_;
    Person* father_;
    Person* mother_;
};


// leaf
// man has a last name 
class Man: public Person{
public:
    Man(string lastName, string firstName, Person* spouse, 
         Person* father, Person* mother): 
        lastName_(lastName), 
        Person(firstName, spouse, father, mother){}
    const string & getLastName(){return lastName_;}
    const string getName() const override { return getFirstName() + ' ' + lastName_; }
    void accept(class PersonVisitor* visitor) override;
private:
    const string lastName_;
};

// composite
// woman has a list of children
class Woman: public Person{
public: 
    Woman(vector<Person* > children, 
         string firstName, 
         Person* spouse, 
         Person* father, Person* mother): 
         children_(children),
         Person(firstName, spouse, father, mother){}
    const vector<Person* > & getChildren() {return children_;}
    const string getName() const override { 
        string name = getFirstName() + ' ';
        if (getSpouse() != nullptr)
	        name += static_cast<Man* > (getSpouse())->getLastName();
        else if (getFather() != nullptr)
            name += static_cast<Man* > (getFather())->getLastName();
        else
	        name += "Doe"; 
        return name;
    }
    void setChildren(const vector<Person* > &children){ children_ = children;}
    void accept(class PersonVisitor* visitor) override;
private:
    vector<Person* > children_;
}; 

// abstract visitor
class PersonVisitor{
public:
    virtual void visit(Man*)=0;
    virtual void visit(Woman*)=0;
    Person* getLastVisited() { return last_visited_; }
    void setLastVisited(Person* p) { last_visited_ = p; }
    virtual ~PersonVisitor(){}
private:
    Person* last_visited_;
};

// composite methods that define traversal
void Man::accept(PersonVisitor* visitor) {
    visitor->visit(this);
    if (getSpouse() != nullptr && visitor->getLastVisited() != getSpouse()) {
        visitor->setLastVisited(this);
        getSpouse()->accept(visitor);
    }
}

void Woman::accept(PersonVisitor* visitor){ 
    // children traversal through mother only
    // father's children are not traversed so as not 
    // to traverse them twice: for mother and father

    visitor->visit(this);
    if (getSpouse() != nullptr && visitor->getLastVisited() != getSpouse()) {
        visitor->setLastVisited(this);
        getSpouse()->accept(visitor);
    }
    // traversing descendants
    for(auto child : children_) 
        child->accept(visitor);

    
}

// concrete visitors
// the last name for a man is stored in object
// the last name a woman is determined by her 
// spouse if she is married
// or by her father if she is not
class NamePrinter: public PersonVisitor{
public:
    void visit(Man* m) override {
        cout << m->getName() << endl;
    }
    void visit(Woman* w) override {
        cout << w->getName() << endl;
    }
};


class ChildrenPrinter: public PersonVisitor{
public:
    void visit(Man* m) override {
        cout << m->getFirstName() << ": ";
        Woman* spouse = static_cast<Woman* >(m->getSpouse());
        if(spouse != nullptr)
	        printNames(spouse->getChildren());
        cout << endl;
    }
    void visit(Woman* w) override {
        cout << w->getFirstName() << ": ";
        printNames(w->getChildren());
        cout << endl;
    }
private:
    void printNames(const vector<Person* > &children){
        for(const auto c: children)
	        cout << c->getFirstName() << ", ";
    }
};


class MaidenNamePrinter: public PersonVisitor{
public:
    void visit(Man* m) override {}
    void visit(Woman* w) override {
        cout << w->getFirstName() << ": ";
        if (w->getFather() != nullptr)
	        cout << static_cast<Man* >(w->getFather())->getLastName() << endl;
        else
	        cout << "Doe" << endl;
    }
};


class MarriageAdvisor: public PersonVisitor{
public:
    MarriageAdvisor(string first, string second): first_(first), second_(second) {}
    void visit(Man* m) override {
        string name = m->getName();
        if (name == first_) {
            cout << "Found First" << endl;
            Person* spouse = m->getSpouse();
            first_single_ = spouse == nullptr; // Checking for infidelity

            cout << "first_single_:" << first_single_ << endl;

            Person* father = m->getFather();
            bool not_father = father == nullptr; // Checking for father-self marriage
            if (father != nullptr) {
                string father_name = father->getName();
                not_father = second_ != father_name;
            }

            Person* mother = m->getMother();
            bool not_mother = mother == nullptr; // Checking for mother-self marriage
            if (mother != nullptr) {
                string mother_name = mother->getName();
                not_mother = second_ != mother_name;
            }

            bool not_sibling = true; // checking for sibling-self marriage
            if (mother != nullptr) {
                for (auto child : static_cast<Woman*>(mother)->getChildren()) {
                    if (child->getName() == second_) {
                        not_sibling = false;
                    }
                }
            }

            bool not_child = true; // checking for child-self marriage
            if (spouse != nullptr) {
                for (auto child : static_cast<Woman*>(spouse)->getChildren()) {
                    if (child->getName() == second_) {
                        not_child = false;
                    }
                }
            }
            
            bool not_aunt_uncle = true;
            if (mother->getMother() != nullptr) {
                for (auto child : static_cast<Woman*>(mother->getMother())->getChildren()) {
                    if (child->getName() == second_) {
                        not_aunt_uncle = false;
                    }
                }
            }

            eligible_ = not_father && not_mother && not_sibling && not_aunt_uncle && not_child;
        } else if (name == second_) {
            cout << "Found Second" << endl;
            second_single_ = m->getSpouse() == nullptr;
        }
    }
    void visit(Woman* w) override {
        string name = w->getName();
        if (name == first_) {
            cout << "Found First" << endl;
            Person* spouse = w->getSpouse();
            first_single_ = spouse == nullptr; // Checking for infidelity

            Person* father = w->getFather();
            bool not_father = father == nullptr; // Checking for father-self marriage
            if (father != nullptr) {
                string father_name = father->getName();
                not_father = second_ != father_name;
            }

            Person* mother = w->getMother();
            bool not_mother = mother == nullptr; // Checking for mother-self marriage
            if (mother != nullptr) {
                string mother_name = mother->getName();
                not_mother = second_ != mother_name;
            }

            bool not_sibling = true; // checking for sibling-self marriage
            if (mother != nullptr) {
                for (auto child : static_cast<Woman*>(mother)->getChildren()) {
                    if (child->getName() == second_) {
                        not_sibling = false;
                    }
                }
            }

            bool not_child = true; // checking for child-self marriage
            for (auto child : w->getChildren()) {
                if (child->getName() == second_) {
                    not_child = false;
                }
            }
            
            bool not_aunt_uncle = true;
            if (mother != nullptr && mother->getMother() != nullptr) {
                for (auto child : static_cast<Woman*>(mother->getMother())->getChildren()) {
                    if (child->getName() == second_) {
                        not_aunt_uncle = false;
                    }
                }
            }

            eligible_ = not_father && not_mother && not_sibling && not_aunt_uncle && not_child;
        } else if (name == second_) {
            cout << "Found Second" << endl;
            second_single_ = w->getSpouse() == nullptr;
        }
    }
    void makeDecision() {
        if (first_ != second_ && first_single_ && second_single_ && eligible_) {
            cout << "You may now kiss" << endl;
        } else {
            cout << "You cannot marry" << endl;
        }
    }
private:
    string first_;
    bool first_single_ = false;
    string second_;
    bool second_single_ = false;
    bool eligible_ = false;
};


// demonstrating the operation
int main(){

   // setting up the genealogical tree      
   // the tree is as follows
   //    
   //
   //       James Smith  <--spouse-->   Mary 
   //	                                  |
   //	                                 children -------------------------
   //	                                  |              |                |
   //	                                  |              |                |
   //	   William Johnson <--spouse-> Patricia      Robert Smith       Linda
   //	                                  |
   //	                                 children------------
   //	                                  |                 |
   //                                     |                 |
   //	   Jennifer  <--spouse-->  Michael Johnson      Barbara
   //	       |
   //	     children
   //	       |
   //          |
   //	     Susan


    // first generation
    Man* js = new Man("Smith", "James", nullptr, nullptr, nullptr);
    Woman* ms = new Woman({}, "Mary", nullptr, nullptr, nullptr);
    ms->setSpouse(js); js->setSpouse(ms);

    // second generation
    Woman* ps = new Woman({}, "Patricia",  nullptr, js, ms);
    Man* wj = new Man("Johnson", "William", nullptr, nullptr, nullptr);
    ps->setSpouse(wj); wj->setSpouse(ps);

    vector<Person* > marysKids  = {ps,
			             new Man("Smith", "Robert", nullptr, js, ms),
			             new Woman({}, "Linda", nullptr, js, ms)};
    ms->setChildren(marysKids);

    // third generation
    Man* mj = new Man("Johnson", "Michael", nullptr, wj, ps);
    vector<Person* > patsKids    = {mj, new Woman({}, "Barbara", nullptr, wj, ps)}; 
    ps->setChildren(patsKids);

    Woman* jj = new Woman({}, "Jennifer", nullptr, nullptr, nullptr);
    vector<Person* > jensKids = {new Woman({}, "Susan", nullptr, mj ,jj)};

    jj->setSpouse(mj); mj->setSpouse(jj);
    jj->setChildren(jensKids);
    

    // defining two visitors
    ChildrenPrinter* cp = new ChildrenPrinter;
    NamePrinter* np = new NamePrinter;
    MaidenNamePrinter* mp = new MaidenNamePrinter;

    // executing the traversal with the composite
    // and the specific visitor

    cout << "\nNAME LIST\n";
    ms->accept(np);

    cout << endl << endl;

    cout << "CHILDREN LIST\n";
    ms->accept(cp);
    
    cout << "\nJAMES' CHILDREN\n";
    js->accept(cp);

    cout << "MAIDEN NAMES\n";
    ms->accept(mp);
    
    string person1, person2;

    cout << "Enter first person: ";
    getline(cin, person1);
    cout << "Enter second person: ";
    getline(cin, person2);
    MarriageAdvisor* ma = new MarriageAdvisor(person1, person2);

    cout << "MARRIAGE ADVISOR\n";
    js->accept(ma);
    ma->makeDecision();
}
