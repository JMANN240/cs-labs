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
        String  str('a');

        // VERIFY
        assert(str == 'a');
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE

        // TEST
        String  str('z');

        // VERIFY
        assert(str == 'z');
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE

        // TEST
        String  str('A');

        // VERIFY
        assert(str == 'A');
    }

    // ADD ADDITIONAL TESTS AS NECESSARY
    
    std::cout << "Done testing single character constructor." << std::endl;

}

