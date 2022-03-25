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
        stack<int>  x;
        stack<int>  y;

        x.push(3);
        x.push(4);
        y.push(5);
        y.push(6);

        assert(x.top() == 4);
        assert(y.top() == 6);
        std::cout << "bef" << std::endl;
        // TEST
        x = y;
        std::cout << "aft" << std::endl;
        std::cout << x.top() << std::endl;
        std::cout << y.top() << std::endl;
        // VERIFY
        assert(x.top() == 6);
        assert(y.top() == 6);
     }


    // ADD ADDITIONAL TESTS AS NECESSARY
    
    std::cout << "Done testing assignment." << std::endl;
}

