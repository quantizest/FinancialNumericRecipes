//
//  BondTest.h
//  FinancialNumericRecipes
//
//  Created by Vaibhav Paliwal on 10/05/20.
//  Copyright © 2020 Vaibhav Paliwal. All rights reserved.
//

#ifndef BondTest_h
#define BondTest_h
#include "BondCalc.h"
#include <iostream>

class BondTest {
    
public:
    void testBonds();
    
private:
    void testPV();
    void testPVCont();
    void testPerpetuity();
    void testIRR();
    void testYTM();
    void testDuration();
    void testMacDuration();
    void testModifiedDuration();
    void testDurationCont();
    void testConvexity();
    void testConvexityCont();
    void testContRateConversion();
    void testDiscRateConversion();

private:
    BondCalc bondCalc;
};

#endif /* BondTest_h */
