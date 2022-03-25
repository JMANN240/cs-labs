//  Stack class test program
//
//  Tests: default constructor
//

#include "stack.hpp"
#include <cassert>
#include <iostream>

//===========================================================================
int main ()
{
    {
        //------------------------------------------------------
        // SETUP FIXTURE

        // TEST
        stack<int> x;

        // VERIFY
        assert(x.empty());
    }


    // ADD ADDITIONAL TESTS AS NECESSARY
    
    std::cout << "Done testing destructor." << std::endl;

}

