//
//  BondCalc.h
//  FinancialNumericRecipes
//
//  Created by Vaibhav Paliwal on 10/05/20.
//  Copyright © 2020 Vaibhav Paliwal. All rights reserved.
//

#ifndef BondCalc_h
#define BondCalc_h

#include <vector>
#include <cmath>

using DoubleVec = std::vector<double>;

double getPVSimple(const DoubleVec& cfTimes_, const DoubleVec& cfAmts_, double rate_);
double getPVPerpetuity(double fixedCF_, double rate_);

void sanityCheck(double rate_, const DoubleVec& cfTimes_= {}, const DoubleVec& cfAmts_= {});
#endif /* BondCalc_h */
