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
        String  left("te");
        String  right("st");

        // TEST
        String result = left + right;
        
        // VERIFY
        assert(result == "test");
        assert(left   == "te");
        assert(right  == "st");
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE
        String  left("t");
        String  right("est");

        // TEST
        String result = (left + right);

        // VERIFY
        assert(result == "test");
        assert(left   == "t");
        assert(right  == "est");
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE
        String  left("tes");
        String  right("t");

        // TEST
        String result = (left + right);

        // VERIFY
        assert(result == "test");
        assert(left   == "tes");
        assert(right  == "t");
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE
        String  left("test");
        String  right("again");

        // TEST
        String result = (left + right);

        // VERIFY
        assert(result == "testagain");
        assert(left   == "test");
        assert(right  == "again");
    }

    // ADD ADDITIONAL TESTS AS NECESSARY
    
    std::cout << "Done testing concatenation." << std::endl;
}

