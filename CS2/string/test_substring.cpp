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
        String result = str.substr(0,0);
        
        // VERIFY
        assert(str    == "abcde");
        assert(result == "a");
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE
        String  str("abcde");

        // TEST
        String result = str.substr(0,1);

        // VERIFY
        assert(str    == "abcde");
        assert(result == "ab");
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE
        String  str("abcde");

        // TEST
        String result = str.substr(1,2);

        // VERIFY
        assert(str    == "abcde");
        assert(result == "bc");
    }

    // ADD ADDITIONAL TESTS AS NECESSARY
    
    std::cout << "Done testing substring." << std::endl;
}

