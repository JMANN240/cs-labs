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
        String  str("abcde fghij");

        // TEST
        int result = str.findstr(0, "a");

        // VERIFY
        assert(str    == "abcde fghij");
        assert(result == 0);
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE
        String  str("abcde fghij");

        // TEST
        int result = str.findstr(0, "fgh");

        // VERIFY
        assert(str    == "abcde fghij");
        assert(result == 6);
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE
        String  str("abcde fghij");

        // TEST
        int result = str.findstr(1, "fgh");

        // VERIFY
        assert(str    == "abcde fghij");
        assert(result == 6);
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE
        String  str("abcde fghij");

        // TEST
        int result = str.findstr(0, "fhg");

        // VERIFY
        assert(str    == "abcde fghij");
        assert(result == -1);
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE
        String  str("abcde fghij");

        // TEST
        int result = str.findstr(5, "bcd");

        // VERIFY
        assert(str    == "abcde fghij");
        assert(result == -1);
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE
        String  str("abcde fghij");

        // TEST
        int result = str.findstr(1, "bcd");

        // VERIFY
        assert(str    == "abcde fghij");
        assert(result == 1);
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE
        String  str("abcde fghij");

        // TEST
        int result = str.findstr(1, "abc");

        // VERIFY
        assert(str    == "abcde fghij");
        assert(result == -1);
    }

    

    // ADD ADDITIONAL TESTS AS NECESSARY
    
    std::cout << "Done testing find string." << std::endl;
}

