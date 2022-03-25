#include "hashmap.hpp"
#include <iostream>
#include <string>

using std::cin; using std::cout; using std::endl;
using std::string;

int main() {
   hashmap<int, int> myHash;

   cout << "Inserting..." << endl;

   auto insertResult1 = myHash.insert(pair<int,int>(4, 40));
   cout << '<' << (*insertResult1.first).first << ", " << (*insertResult1.first).second << ">, " << insertResult1.second << endl;
   auto insertResult2 = myHash.insert(pair<int,int>(4, 50));
   cout << '<' << (*insertResult2.first).first << ", " << (*insertResult2.first).second << ">, " << insertResult2.second << endl;
   auto insertResult3 = myHash.insert(pair<int,int>(105, 60));
   cout << '<' << (*insertResult3.first).first << ", " << (*insertResult3.first).second << ">, " << insertResult3.second << endl;
   auto insertResult4 = myHash.insert(pair<int,int>(100, 70));
   cout << '<' << (*insertResult4.first).first << ", " << (*insertResult4.first).second << ">, " << insertResult4.second << endl;
   myHash[0] = 10;
   cout << "myHash[0] = " << myHash[0] << endl;
   myHash[0] = 20;
   cout << "myHash[0] = " << myHash[0] << endl;

   // x will have type hashmap<int, int>::value_type*
   auto x = myHash.find(4);
   if (x != nullptr) 
      cout << "4 maps to " << x->second << endl;
   else 
      cout << "cannot find 4 in map" << endl;

    myHash.rehash(201);

   cout << "Erasing..." << endl;

   auto eraseResult1 = myHash.erase(4);
   if (eraseResult1.first == nullptr) {
      cout << eraseResult1.first << ", " << eraseResult1.second << endl;
   } else {
      cout << '<' << eraseResult1.first->first << ", " << eraseResult1.first->second << ">, " << eraseResult1.second << endl;
   }
   auto eraseResult2 = myHash.erase(4);
   if (eraseResult2.first == nullptr) {
      cout << eraseResult2.first << ", " << eraseResult2.second << endl;
   } else {
      cout << '<' << eraseResult2.first->first << ", " << eraseResult2.first->second << ">, " << eraseResult2.second << endl;
   }
   auto eraseResult3 = myHash.erase(105);
   if (eraseResult3.first == nullptr) {
      cout << eraseResult3.first << ", " << eraseResult3.second << endl;
   } else {
      cout << '<' << eraseResult3.first->first << ", " << eraseResult3.first->second << ">, " << eraseResult3.second << endl;
   }
   auto eraseResult4 = myHash.erase(0);
   if (eraseResult4.first == nullptr) {
      cout << eraseResult4.first << ", " << eraseResult4.second << endl;
   } else {
      cout << '<' << eraseResult4.first->first << ", " << eraseResult4.first->second << ">, " << eraseResult4.second << endl;
   }
   auto eraseResult5 = myHash.erase(100);
   if (eraseResult5.first == nullptr) {
      cout << eraseResult5.first << ", " << eraseResult5.second << endl;
   } else {
      cout << '<' << eraseResult5.first->first << ", " << eraseResult5.first->second << ">, " << eraseResult5.second << endl;
   }

}