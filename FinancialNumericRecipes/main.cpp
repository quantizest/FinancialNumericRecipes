//
//  main.cpp
//  FinancialNumericRecipes
//
//  Created by Vaibhav Paliwal on 10/05/20.
//  Copyright © 2020 Vaibhav Paliwal. All rights reserved.
//

#include <iostream>
#include "Bonds/BondTest.h"
int main(int argc, const char * argv[]) {
    // insert code here...
    try {
        BondTest bondTests;
        bondTests.testBonds();
        std::cout << "Tests ran succesfully!\n";
    }
    catch(const std::exception& e_){
        std::cerr << "Exception : " << e_.what();
    }
    return 0;
}
