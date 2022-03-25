// sorting oranges
// converting vectors to multimaps
// Mikhail Nesterenko
// 2/17/2020


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <map>
#include <vector>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector;
using std::multimap;

enum class Variety {orange, pear, apple};
vector<string> colors = {"red", "green", "yellow"};

struct Fruit{
   Variety v;
   string color; // red, green or orange
};


int main(){
    srand(time(nullptr));
    int tree_size = rand()%100+1; // Set the size of the tree

    multimap<Variety, string> tree; // Create the multimap

    for(int i = 0; i < tree_size; ++i) {
        tree.emplace(static_cast<Variety>(rand() % 3), colors[rand()%3]); // Emplace random elements into the multimap
    }
    
    cout << "Colors of the oranges: ";
    for(auto f=tree.lower_bound(Variety::orange); f!=tree.upper_bound(Variety::orange); ++f) // For ever orange tree
        cout << f->second << ", ";
    cout << endl;

}
