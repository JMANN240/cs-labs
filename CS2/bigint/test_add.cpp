// bigint Test Program
//
// Tests:  int constructor, uses ==
//
// NEED TO IMPLEMENT
//
#include <iostream>
#include <cassert>
#include "bigint.hpp"


//===========================================================================
int main () {
    {

        // VERY INCOMPLETE set of tests.


        //------------------------------------------------------
        // Setup fixture
        bigint left(0);
        bigint right(0);
        bigint result;

        // Test 
        result = left + right;

        // Verify
        assert(left   == 0);
        assert(right  == 0);
        assert(result == 0);
    }

    {
      //------------------------------------------------------
      // Setup fixture
      bigint left(1);
      bigint right(0);
      bigint result;

      // Test
      result = left + right;

      // Verify
      assert(left   == 1);
      assert(right  == 0);
      assert(result == 1);
    }
    {
      //------------------------------------------------------
      // Setup fixture
      bigint left(1);
      bigint right(1);
      bigint result;

      // Test
      result = left + right;

      // Verify
      assert(left   == 1);
      assert(right  == 1);
      assert(result == 2);
    }

    {
      bigint left(0);
      bigint right(135);
      bigint result;

      result = left + right;

      assert(left == 0);
      assert(right == 135);
      assert(result == 135);
    }

    {
      bigint left(135);
      bigint right(135);
      bigint result;

      result = left + right;

      assert(left == 135);
      assert(right == 135);
      assert(result == 270);
    }
    {
      bigint left(135);
      bigint right(935);
      bigint result;

      result = left + right;

      assert(left == 135);
      assert(right == 935);
      assert(result == "1070");
    }
    {
      bigint left("9071632459013645");
      bigint right("71623495136790613456919761236");
      bigint result;

      result = left + right;

      assert(left == "9071632459013645");
      assert(right == "71623495136790613456919761236");
      assert(result == "71623495136799685089378774881");
    }
    {
      bigint left("71623495136790613456919761236");
      bigint right("9071632459013645");
      bigint result;

      result = left + right;

      assert(left == "71623495136790613456919761236");
      assert(right == "9071632459013645");
      assert(result == "71623495136799685089378774881");
    }
    {
      bigint left(10);
      bigint right("999999999999999999999999999999999999");
      bigint result;

      result = left + right;

      assert(left == 10);
      assert(right == "999999999999999999999999999999999999");
      assert(result == "1000000000000000000000000000000000009");
    }
    {
      bigint left("71623495136790613456919761236");
      bigint right(0);
      bigint result;

      result = left + right;

      assert(left == "71623495136790613456919761236");
      assert(right == 0);
      assert(result == "71623495136790613456919761236");
    }
    {
      bigint left(0);
      bigint right("71623495136790613456919761236");
      bigint result;

      result = left + right;

      assert(left == 0);
      assert(right == "71623495136790613456919761236");
      assert(result == "71623495136790613456919761236");
    }
    {
      bigint left("1234589765431726289345348712634564738921349847564371896298374658475693198273645764837258493198287346574381928376458948839");
      bigint right("1348671360871369681734609138467245709387234635098267259284198316249624872139518365928346924867312597675456248724924696");
      bigint result;

      result = left + right;

      assert(left == "1234589765431726289345348712634564738921349847564371896298374658475693198273645764837258493198287346574381928376458948839");
      assert(right == "1348671360871369681734609138467245709387234635098267259284198316249624872139518365928346924867312597675456248724924696");
      assert(result == "1235938436792597659027083321773031984630737082199470163557658856791942823145785283203186840123154659172057384625183873535");
    }
    
    //Add test cases as needed.
    
    
    std::cout << "Done with testing addition." << std::endl;
}

