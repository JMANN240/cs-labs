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
        String  left;
        String  right;

        // TEST
        bool result = (left == right);

        // VERIFY
        assert(result == true);
        assert(left   == '\0');
        assert(right  == '\0');
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE
        String  left('a');
        String  right('a');

        // TEST
        bool result = (left == right);

        // VERIFY
        assert(result == true);
        assert(left   == 'a');
        assert(right  == 'a');
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE
        String  left('A');
        String  right('A');

        // TEST
        bool result = (left == right);

        // VERIFY
        assert(result == true);
        assert(left   == 'A');
        assert(right  == 'A');
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE
        String  left("test");
        String  right("test");

        // TEST
        bool result = (left == right);

        // VERIFY
        assert(result == true);
        assert(left   == "test");
        assert(right  == "test");
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE
        String  left("test again");
        String  right("test again");

        // TEST
        bool result = (left == right);

        // VERIFY
        assert(result == true);
        assert(left   == "test again");
        assert(right  == "test again");
    }

    // ADD ADDITIONAL TESTS AS NECESSARY
    
    std::cout << "Done testing equal." << std::endl;
}

