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

        // TEST
        x.push(5);

        // VERIFY
        assert(x.pop()==5);
     }

     {
        //------------------------------------------------------
        // SETUP FIXTURE
        stack<int>  x;

        // TEST
        x.push(5);
        x.push(4);

        // VERIFY
        assert(x.pop()==4);
        assert(x.pop()==5);
     }

     {
        //------------------------------------------------------
        // SETUP FIXTURE
        stack<int>  x;

        // TEST
        x.push(5);
        x.push(4);

        // VERIFY
        assert(x.top()==4);
        assert(x.pop()==4);
        assert(x.top()==5);
        assert(x.pop()==5);
     }


    // ADD ADDITIONAL TESTS AS NECESSARY
    
    std::cout << "Done testing push pop." << std::endl;
}

