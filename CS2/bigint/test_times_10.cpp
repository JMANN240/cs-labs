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
        bigint bi(3);
        // Test 
        bi = bi.times10(0);
        // Verify
        assert(bi == 3);  //Wrong. Will FAIL, fix and add tests cases
    }
    {
        bigint bi(3);

        bi = bi.times10(1);

        assert(bi == 30);
    }
    {
        bigint bi(364);

        bi = bi.times10(2);

        assert(bi == 36400);
    }
    {
        bigint bi(364);

        bi = bi.times10(5);

        assert(bi == 36400000);
    }
    {
        bigint bi(0);

        bi = bi.times10(2);

        assert(bi == 0);
    }
    {
        bigint bi(364);

        bi = bi.times10(20);

        assert(bi == "36400000000000000000000");
    }
    
    //Add test cases as needed.

    std::cout << "Done testing times_10" << std::endl;
}

