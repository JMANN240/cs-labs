#include <fstream>
#include <iostream>
#include <string>
#include "WordList.hpp"

WordOccurrence::WordOccurrence(const std::string& word, int num):word_(word), num_(num) {}
bool WordOccurrence::matchWord(const std::string& test_word) {return test_word == word_; } // returns true if word matches stored
void WordOccurrence::increment() { ++num_; } // Increment occurrences
std::string WordOccurrence::getWord() const { return word_; }
int WordOccurrence::getNum() const { return num_; }


WordList::WordList() {
    size_ = 0; // Set the number of words found to 0
    capacity_ = 1; // Set the number of words we are able to store to 1
    wordArray_ = new WordOccurrence[1]; // Create the array of words
}

// add copy constructor, destructor, overloaded assignment
WordList::WordList(const WordList& old) {
    size_ = old.size_;
    wordArray_ = size_ > 0 ? new WordOccurrence[size_] : new WordOccurrence[1]; // Create the new word array with the proper size
    std::copy(old.wordArray_, old.wordArray_ + size_, wordArray_); // Copy the values from the old array into the new
}

WordList::~WordList() { delete [] wordArray_; }

WordList& WordList::operator= (const WordList& other) {
    if (this != & other) { // protection against self assingment
        delete [] wordArray_; // Delete the array
        size_ = other.size_; // Set the size to the size of the other list
        wordArray_ = size_ > 0 ? new WordOccurrence[size_] : new WordOccurrence[1]; // Create the new word array with the proper size
        std::copy(other.wordArray_, other.wordArray_ + size_, wordArray_); // Copy the values from the old array into the new
    }
    return *this; // Return the object for compounding assignments
}

bool equal(const WordList& left, const WordList& right) {
    if (left.size_ != right.size_) { // Make sure they aren't a different size first
        return false;
    }
    for (int i = 0; i < left.size_; ++i) { // Loop through each word occurrence
        if (left.wordArray_[i].getWord() != right.wordArray_[i].getWord()) { 
            return false; // Return false if the word occurrences aren't the exact same
        }
    }
    return true; // If we have gotten this far, they lists are equal
}

void WordList::addWord(const std::string& new_word) {
    for (int i = 0; i < size_; ++i) { // Loop to make sure we don't already have this word
        if (wordArray_[i].matchWord(new_word)) { // If we do, just add to its count and return
            wordArray_[i].increment();
            return;
        }
    }
    WordOccurrence new_occurrence = WordOccurrence(new_word, 1); // If we got here, it is a new word
    wordArray_[size_] = new_occurrence; // Add the new word occurrence to the end of the word array
    ++size_;
    if (size_ == capacity_) { // If we have reached capacity
        capacity_*=2; // Double the capacity
        WordOccurrence* new_wordArray_ = new WordOccurrence[capacity_]; // Create a new array with the bigger capacity
        std::copy(wordArray_, wordArray_ + size_, new_wordArray_); // Copy the words into the new array
        delete[] wordArray_; // Delete the old array
        wordArray_ = new_wordArray_; // Make wordArray_ point to the new array
    }
}

void WordList::print() {
    // Some Algorithm I came up with
    // int max = 1;
    // for (int i = 0; i < size_; ++i) {
    //     if (wordArray_[i].getNum() > max) {
    //         max = wordArray_[i].getNum();
    //     }
    // }
    // for (int i = 1; i <= max; ++i) {
    //     for (int j = 0; j < size_; ++j) {
    //         if (wordArray_[j].getNum() == i) {
    //             std::cout << wordArray_[j].getWord() << " " << wordArray_[j].getNum() << std::endl;
    //         }
    //     }
    // }

    // Insertion sort
    int j;
    WordOccurrence word;
    for (int i = 1; i < size_; ++i) {
        word = wordArray_[i];
        j = i - 1;
        while (j >= 0 && wordArray_[j].getNum() > word.getNum()) {
            wordArray_[j + 1] = wordArray_[j];
            j = j - 1;
        }
        wordArray_[j + 1] = word;
    }
    for (int i = 0; i < size_; ++i) {
        std::cout << wordArray_[i].getWord() << " " << wordArray_[i].getNum() << std::endl;
    }
}
