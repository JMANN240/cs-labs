#include <iostream>
#include "Collection.hpp"

int main() {
    Collection<int> list1 = Collection<int>();
    list1.add(1);
    list1.add(2);
    list1.add(3);
    list1.print();
}