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
        String str;

        // VERIFY
        assert(str == "");
    }

    // ADD ADDITIONAL TESTS AS NECESSARY
    
    std::cout << "Done testing default constructor." << std::endl;

}

