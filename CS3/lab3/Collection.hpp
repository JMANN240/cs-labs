// node class tempate used to contruct lists
// Mikhail Nesterenko
// 5/01/00

#ifndef LIST_HPP_
#define LIST_HPP_

#include <iostream>

// the pointer part of every list is the same
// lists differ by data part
template <typename T>
class node{
public:

  node(): next_(nullptr) {}

  // functions can be inlined
  T getData()const{return data_;}
  void setData(const T& data){data_=data;}

  // or can be defined outside
  node<T>* getNext() const;
  void setNext(node<T> *const);

private:
  T data_;
  node<T> *next_;
};

//
// member functions for node
//
template <typename T>
node<T>* node<T>::getNext()const{
  return next_;
}

template<typename T>
void node<T>::setNext(node<T> *const next){
   next_=next;
}



template<typename T>
class Collection {
public:

    Collection(): base_(nullptr) {}
    Collection(const Collection& old); 
    ~Collection();
    Collection& operator= (const Collection& old);
    void add(T item);
    void remove(T item);
    T last();
    void print();
    template<typename U>
    friend bool equal(const Collection<U>&, const Collection<U>&);

private:

    node<T>* base_;

};

template<typename T>
Collection<T>::Collection(const Collection<T>& old) { // Copy Constructor
    node<T>* current_node = old.base_; // Initialize the current node
    while (current_node != nullptr) { // While the current node exists
        add(current_node->getData()); // Add the current node's data to the collection
        current_node = current_node->getNext(); // Move to the next current node
    }
}

template<typename T>
Collection<T>::~Collection() { // Destructor
    node<T>* temp_node = base_; // Initialize the temporary node
    while (temp_node != nullptr) { // While the temporary node exists
        node<T>* old_node = temp_node; // Create a pointer to the temporary node
        temp_node = temp_node->getNext(); // Move to the next node
        delete old_node; // Deallocate the memory where the node was
    }
}

template<typename T>
Collection<T>& Collection<T>::operator= (const Collection<T>& other) { // Overloaded Assigment
    if (this != &other) { // Protect against self assignment
        // Destruct the current state
        node<T>* temp_node = base_;
        while (temp_node != nullptr) {
            node<T>* old_node = temp_node;
            temp_node = temp_node->getNext();
            delete old_node;
        }

        // Copy the other node's state
        node<T>* other_node = other.base_;
        while (other_node != nullptr) {
            add(other_node->getData());
            other_node = other_node->getNext();
        }
    }
    return *this; // Return the collection
}

template<typename T>
void Collection<T>::add(T item){
    node<T>* new_node = new node<T>(); // Create a new dynamically allocated node
    new_node->setData(item); // Put the item value in the data member of the new node

    if (base_ == nullptr) { // If the collection is empty
        base_ = new_node; // Just assign the base to the location of the new node
    } else { // Otherwise, count to the end of the collection
        node<T>* last_node = base_; // The last node in the collection is initialized to the base
        while (last_node->getNext() != nullptr) { // While there is a next node to get
            last_node = last_node->getNext(); // Set that next node to be the last found node
        }
        last_node->setNext(new_node); // Set the next node of the last node to the new node
    }
}

template<typename T>
void Collection<T>::remove(T item){
    node<T>* previous_node = base_; // Initialize the "previous" node to the base (for logic reasons)
    node<T>* current_node = base_; // Initialize the current node to the base
    node<T>* next_node; // Declare the next node, but don't initialize (in case there is none)

    while (current_node != nullptr) { // While the current node exists
        next_node = current_node->getNext(); // The next node is the node after the current node
        if (current_node->getData() == item) { // If the current node matches the item
            if (current_node == base_) { // If the current node is the base node
                base_ = next_node; // Set the new base node to the next node
                previous_node = base_; // Set the "previous" node to the new base
            } else { // If the current node is not the base node
                previous_node->setNext(next_node); // Just set the node after the previous node to the next node
            }
            delete current_node; // Whether it is the base or not, we always want to delete the current node if it matches
        } else { // If the current node does not match the item
            previous_node = current_node; // Set the previous node to the current node
        }
        current_node = next_node; // Set the current node to the next node
    }
}

template<typename T>
T Collection<T>::last(){
    node<T>* last_node = base_; // The last node we have found is the base
    while (last_node->getNext() != nullptr) { // While there is a next node to get
        last_node = last_node->getNext(); // Get the next node
    }
    return last_node->getData(); // Return the data of the true last node
}

template<typename T>
void Collection<T>::print(){
    node<T>* last_node = base_; // The last node we have found is the base
    while (last_node != nullptr) { // While the last node we have found exists
        std::cout << last_node->getData() << std::endl; // Print the nodes data
        last_node = last_node->getNext(); // Get the next node
    }
}

template<typename U>
bool equal(const Collection<U>& lhs, const Collection<U>& rhs) {
    node<U>* left_node = lhs.base_; // Get a pointer to the base of the left hand collection
    node<U>* right_node = rhs.base_; // Get a pointer to the base of the right hand collection
    while ((left_node != nullptr) && (right_node != nullptr)) { // While both nodes exist
        if (left_node->getData() != right_node->getData()) { // If they aren't equal
            return false;
        }
        left_node = left_node->getNext(); // Get the next left node
        right_node = right_node->getNext(); // Get the next right node
    }
    return ((left_node == nullptr) && (right_node == nullptr)); // Return true if they are both out of nodes (same length)
}

#endif // LIST_HPP_