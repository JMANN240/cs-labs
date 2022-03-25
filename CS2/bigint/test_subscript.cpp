// bigint Test Program
//
// Tests:  subscript, uses ==
//
// NEED TO IMPLEMENT
//
#include <iostream>
#include <cassert>
#include "bigint.hpp"

//===========================================================================
int main () {
    
    {
        // Setup
        bigint bi("264");

        // Test 
        int onesDigit = bi[0];
        int tensDigit = bi[1];
        int hundredsDigit = bi[2];

        // Verify
        assert(bi    == 264);
        assert(onesDigit == 4);
        assert(tensDigit == 6);
        assert(hundredsDigit == 2);
    }
    {
        // Setup
        bigint bi("10001");

        // Test 
        int onesDigit = bi[0];
        int tensDigit = bi[1];
        int tenhundredsDigit = bi[4];

        // Verify
        assert(bi    == 10001);
        assert(onesDigit == 1);
        assert(tensDigit == 0);
        assert(tenhundredsDigit == 1);
    }
    
    //Add test cases!!

    std::cout << "Done testing subscript." << std::endl;
}

