// bigint Test Program
//
// Tests:  times_10, uses ==
//
// NEED TO IMPLEMENT
//
#include <iostream>
#include <cassert>
#include "bigint.hpp"

//===========================================================================
int main () {
    {
        //------------------------------------------------------
        // Setup fixture
        bigint bi(32);

        // Test 
        bi = bi.timesDigit(5);

        // Verify
        assert(bi == 160);  
    }
    {
        bigint bi(32);

        bi = bi.timesDigit(0);

        assert(bi == 0);  
    }
    {
        bigint bi(0);

        bi = bi.timesDigit(32);

        assert(bi == 0);  
    }
    {
        bigint bi(32);

        bi = bi.timesDigit(9);

        assert(bi == 288);  
    }
    {
        bigint bi(0);

        bi = bi.timesDigit(9);

        assert(bi == 0);  
    }
    {
        bigint bi(137);

        bi = bi.timesDigit(4);

        assert(bi == 548);  
    }
    {
        bigint bi("8910365091365918364189237846135");

        bi = bi.timesDigit(7);

        assert(bi == "62372555639561428549324664922945");  
    }


    //Add test cases as needed.
    
    std::cout << "Done testing bigint * digit" << std::endl;

}