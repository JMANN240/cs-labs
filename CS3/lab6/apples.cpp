// sorting apples
// non STL-algorithm code to be replaced by algorthms
// Mikhail Nesterenko
// 10/03/2018


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <numeric>
#include <math.h>
#include <functional>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector; using std::deque;
using std::generate; using std::count_if; 
using std::find_if; using std::max_element;
using std::accumulate; using std::for_each;
using std::remove_if; using std::sort;
using std::remove_copy_if; using std::back_inserter;
using std::advance; using std::bind;
using namespace std::placeholders;

struct Apples{
    double weight; // oz
    string color;  // red or green
    void print() const { cout << color << ", " <<  weight << endl; }
};



int main(){
    srand(time(nullptr));
    const double minWeight = 3.;
    const double maxWeight = 8.;

    cout << "Input crate size: ";
    int size;
    cin >> size;

    vector <Apples> crate(size);

    generate(crate.begin(), crate.end(), [minWeight, maxWeight]()->Apples{ // Fill the crate with apples
        Apples a; // Make an apple and set its attributes
        a.weight = minWeight + static_cast<double>(rand())/RAND_MAX*(maxWeight - minWeight);
        a.color = rand() % 2 == 1 ? "green" : "red";
        return a; // Put the apple in the crate
    });

 
    cout << "Enter weight to find: ";
    double toFind;
    cin >> toFind;

    auto overWeight = [toFind](const Apples& a)->bool { return a.weight > toFind; }; // Make lambda to detect overweight apples

    int cnt = count_if(crate.cbegin(), crate.cend(), overWeight); // Count overweight apples

    cout << "There are " << cnt << " apples heavier than " 
	<< toFind << " oz" <<  endl;

    vector<Apples>::iterator it = find_if(crate.begin(), crate.end(), overWeight); // Find the first overweight apple
    while(it != crate.end()) { // While there is an apple that is overweight
        cout << it - crate.begin() << ", ";
        it = find_if(++it, crate.end(), overWeight); // Find the next overweight apple
    }
    cout << endl;

    auto compareWeights = [](const Apples& lhs, const Apples& rhs)->bool { return lhs.weight < rhs.weight; }; // Make lambda for comparing weights (probably would have been better to overload <)

    cout << "Heaviest apple weighs: " << max_element(crate.begin(), crate.end(), compareWeights)->weight << " oz" << endl; // Find heaviest apple

    double sum = 0;
    sum = accumulate(crate.begin(), crate.end(), sum, [](const double& lhs, const Apples& rhs)->double{ return lhs + rhs.weight; }); // Add up all weights
    cout << "Total apple weight is: " << sum << " oz" << endl;

    // transform();
    cout << "How much should they grow: ";
    double toGrow;
    cin >> toGrow;

    transform(crate.begin(),  crate.end(), crate.begin(), [toGrow](Apples& a)->Apples { // Perform an operation on all apples and replace
        a.weight += toGrow; 
        return a;
    });

    

    // remove_if()
    cout << "Input minimum acceptable weight: ";
    double minAccept;
    cin >> minAccept;

    crate.assign(crate.begin(), remove_if(crate.begin(), crate.end(), [minAccept](const Apples& a)->bool{ return a.weight < minAccept; })); // Remove apples that are too small
        
    cout << "removed " << size - crate.size() << " elements" << endl;

    sort(crate.begin(), crate.end(), compareWeights);


    // moving all red apples from crate to peck
    // remove_copy_if() with back_inserter()/front_inserter() or equivalents
    deque<Apples> peck; // Create a deque
    remove_copy_if(crate.begin(), crate.end(), back_inserter(peck), [](const Apples& a)->bool{ return a.color != "red"; }); // If the apple is red, add it to the back of peck
    crate.assign(crate.begin(), remove_if(crate.begin(), crate.end(), [](const Apples& a)->bool{ return a.color == "red"; })); // assign the crate to be just red apples

    cout << "apples in the create"<< endl;
    for_each(crate.begin(), crate.end(), [](Apples a){a.print();}); // Print each apple
    cout << endl;
    cout << "apples in the peck"<< endl;
    for_each(peck.begin(), peck.end(), [](Apples a){a.print();});

    const int space=3; 
    cout << "\nevery " << space << "\'d apple in the peck"<< endl;
    auto pit=peck.cbegin(); int i = 0;   
    while(pit != peck.cend()){
        if(i == space){
            pit->print();
            i=0;
        }
        ++i; 
        advance(pit, 1); // Advance rather than incrementing
    }

    auto makeJam = bind([crate](double maxWeight)->double{ // Create a functor that can take a max weight
        return accumulate(crate.begin(), crate.end(), 0.0, [maxWeight](double lhs, const Apples& rhs)->double{ 
            return lhs + (rhs.weight < maxWeight ? rhs.weight : 0.0); 
        }); 
    }, _1); 

    double jam10 = makeJam(10.0); // Set maxweight to 10

    cout << "Weight of jam is: " << jam10 << endl;

}
