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
using Interval = std::pair<double, double>; //[x0, x1]

constexpr double eps = 1e-6;
constexpr double ERROR_VAL = std::numeric_limits<double>::max();

double getPVSimple(const DoubleVec& cfTimes_, const DoubleVec& cfAmts_, double rate_);
double getPVPerpetuity(double fixedCF_, double rate_);

void sanityCheck(double rate_, const DoubleVec& cfTimes_, const DoubleVec& cfAmts_, bool checkRate_ = false);
void sanityCheck(const DoubleVec& cfTimes_, const DoubleVec& cfAmts_);
void sanityCheck(double rate_);
// TODO: Pass a function obj for the below 2 methods
// IRR is the rate at which the net PV of all cash flows is 0
double getIRR(const DoubleVec& cfTimes_, const DoubleVec& cfAmts_);
// Return a range of interest rates within which the PV changes sign
Interval getBracketedRange(const DoubleVec& cfTimes_, const DoubleVec& cfAmts_);

#endif /* BondCalc_h */
