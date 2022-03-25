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
        String  right("test");

        // TEST
        bool result = (left < right);

        // VERIFY
        assert(result == true);
        assert(left   == "te");
        assert(right  == "test");
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE
        String  left("test");
        String  right("te");

        // TEST
        bool result = (left < right);

        // VERIFY
        assert(result == false);
        assert(left   == "test");
        assert(right  == "te");
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE
        String  left("test");
        String  right("test");

        // TEST
        bool result = (left < right);

        // VERIFY
        assert(result == false);
        assert(left == "test");
        assert(right == "test");
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE
        String  left("te");
        String  right("test");

        // TEST
        bool result = (left > right);

        // VERIFY
        assert(result == false);
        assert(left   == "te");
        assert(right  == "test");
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE
        String  left("test");
        String  right("te");

        // TEST
        bool result = (left > right);

        // VERIFY
        assert(result == true);
        assert(left   == "test");
        assert(right  == "te");
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE
        String  left("test");
        String  right("test");

        // TEST
        bool result = (left > right);

        // VERIFY
        assert(result == false);
        assert(left   == "test");
        assert(right  == "test");
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE
        String  left("te");
        String  right("test");

        // TEST
        bool result = (left <= right);

        // VERIFY
        assert(result == true);
        assert(left   == "te");
        assert(right  == "test");
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE
        String  left("test");
        String  right("te");

        // TEST
        bool result = (left <= right);

        // VERIFY
        assert(result == false);
        assert(left   == "test");
        assert(right  == "te");
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE
        String  left("test");
        String  right("test");

        // TEST
        bool result = (left <= right);

        // VERIFY
        assert(result == true);
        assert(left   == "test");
        assert(right  == "test");
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE
        String  left("te");
        String  right("test");

        // TEST
        bool result = (left >= right);

        // VERIFY
        assert(result == false);
        assert(left   == "te");
        assert(right  == "test");
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE
        String  left("test");
        String  right("te");

        // TEST
        bool result = (left >= right);

        // VERIFY
        assert(result == true);
        assert(left   == "test");
        assert(right  == "te");
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE
        String  left("test");
        String  right("test");

        // TEST
        bool result = (left >= right);

        // VERIFY
        assert(result == true);
        assert(left   == "test");
        assert(right  == "test");
    }
    
    // ADD ADDITIONAL TESTS AS NECESSARY
    
    std::cout << "Done testing less than." << std::endl;
}

