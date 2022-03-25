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

        // TEST
        String  str("test");

        // VERIFY
        assert(str == "test");
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE

        // TEST
        String  str("test again");

        // VERIFY
        assert(str == "test again");
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE

        // TEST
        String  str("Screaming aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");

        // VERIFY
        assert(str == "Screaming aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    }

    // ADD ADDITIONAL TESTS AS NECESSARY
    
    std::cout << "Done testing character array constructor." << std::endl;

}

