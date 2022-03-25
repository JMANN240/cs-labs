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
        String  str("abcde");

        // TEST
        int result = str.findch(0, 'c');

        // VERIFY
        assert(str    == "abcde");
        assert(result == 2);
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE
        String  str("abcde");

        // TEST
        int result = str.findch(0, 'd');

        // VERIFY
        assert(str    == "abcde");
        assert(result == 3);
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE
        String  str("abcde");

        // TEST
        int result = str.findch(0, 'a');

        // VERIFY
        assert(str    == "abcde");
        assert(result == 0);
    }

    // ADD ADDITIONAL TESTS AS NECESSARY
    
    std::cout << "Done testing find character." << std::endl;
}

