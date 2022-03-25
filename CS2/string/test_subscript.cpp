//  String class test program
//
//  Name:  XXX
//  Tests: XXX
//

#include "string.hpp"
#include <cassert>
#include <iostream>

//===========================================================================
int main ()
{
    {
        //------------------------------------------------------
        // SETUP FIXTURE
        String  str("test");

        // TEST
        char result = str[0];

        // VERIFY
        assert(result == 't');
        assert(str   == "test");
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE
        String  str("test");

        // TEST
        char result = str[1];

        // VERIFY
        assert(result == 'e');
        assert(str   == "test");
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE
        String  str("tesr");

        // TEST
        str[3] = 't';

        // VERIFY
        assert(str   == "test");
    }

    // ADD ADDITIONAL TESTS AS NECESSARY
    
    std::cout << "Done testing subscript." << std::endl;
}

