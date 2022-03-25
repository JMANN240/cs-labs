//  Stack class test program
//
//  Tests: XXX
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
        stack<int>  x;
        x.push(3);
        x.push(4);
        stack<int> y(x);

        // VERIFY
        assert(y.pop() == 4);
        assert(x.pop() == 4);
        assert(y.pop() == 3);
        assert(x.pop() == 3);
    }


    // ADD ADDITIONAL TESTS AS NECESSARY
    
    std::cout << "Done testing copy constructor." << std::endl;

}

