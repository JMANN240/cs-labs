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
        String  str("120");

        // TEST
        int result = str.toint();

        // VERIFY
        assert(str    == "120");
        assert(result == 120);
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE
        String  str("12135624");

        // TEST
        int result = str.toint();

        // VERIFY
        assert(str    == "12135624");
        std::cout << result;
        assert(result == 12135624);
    }

    std::cout << "Done testing toint." << std::endl;
}

