//  String class test program
//
//  Name:  XXX
//  Tests: XXX
//

#include "string.hpp"
#include <cassert>
#include <iostream>
#include <fstream>

//===========================================================================
int main ()
{
    {
        //------------------------------------------------------
        // SETUP FIXTURE
        String str;
        std::ifstream in;
        in.open("inputTest.txt");

        // TEST
        in >> str;

        // VERIFY
        assert(str == "This");
        in.close();
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE
        String  str;
        std::ifstream in;
        in.open("inputTest.txt");

        // TEST
        in >> str;
        in >> str;

        // VERIFY
        assert(str == "is");
        in.close();
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE
        String  str;
        std::ifstream in;
        in.open("inputTest.txt");

        // TEST
        in >> str;
        in >> str;
        in >> str;

        // VERIFY
        assert(str == "a");
        in.close();
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE
        String  str;
        std::ifstream in;
        in.open("inputTest.txt");

        // TEST
        in >> str;
        in >> str;
        in >> str;
        in >> str;

        // VERIFY
        assert(str == "test.");
        in.close();
    }

    // ADD ADDITIONAL TESTS AS NECESSARY
    
    std::cout << "Done testing input." << std::endl;
}

