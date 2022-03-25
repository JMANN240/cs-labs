//  String class test program
//
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
        String str("test");

        // TEST
        int result = str.length();

        // VERIFY
        assert(str    == "test");
        assert(result == 4);
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE
        String  str("test");

        // TEST
        int result = str.capacity();

        // VERIFY
        assert(str    == "test");
        assert(result == 4);
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE
        String  str("testtesttest");

        // TEST
        int result = str.length();

        // VERIFY
        assert(str    == "testtesttest");
        assert(result == 12);
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE
        String  str("test test test");

        // TEST
        int result = str.length();

        // VERIFY
        assert(str    == "test test test");
        assert(result == 14);
    }

    // ADD ADDITIONAL TESTS AS NECESSARY
    
    std::cout << "Done testing length and capacity." << std::endl;
}

