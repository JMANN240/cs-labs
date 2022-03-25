//  String class test program
//
//  Tests: XXX
//

#include "string.hpp"
#include <cassert>
#include <iostream>
#include <vector>

//===========================================================================
int main ()
{
    {
        //------------------------------------------------------
        // SETUP FIXTURE
        
        String str("This is a test.");
        
        // TEST
        std::vector<String> result = str.split(' ');
        
        std::vector<String> correct{"This","is","a","test."};
        // VERIFY
        assert(str    == "This is a test.");
        assert(result == correct);
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE
        
        String str("-a---b-");
        
        // TEST
        std::vector<String> result = str.split('-');
        std::vector<String> correct{"","a","","","b",""};
        // VERIFY
        assert(str    == "-a---b-");
        assert(result == correct);
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE
        
        String str("test");
        
        // TEST
        std::vector<String> result = str.split('-');
        std::vector<String> correct{"test"};
        // VERIFY
        assert(str    == "test");
        assert(result == correct);
    }

    {
        //------------------------------------------------------
        // SETUP FIXTURE
        
        String str("-");
        
        // TEST
        std::vector<String> result = str.split('-');
        std::vector<String> correct{"",""};
        // VERIFY
        assert(str    == "-");
        assert(result == correct);
    }

    // ADD ADDITIONAL TESTS AS NECESSARY
    
    std::cout << "Done testing split." << std::endl;
}

