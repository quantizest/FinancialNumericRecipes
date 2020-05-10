#include "BondCalc.h"

double getPVSimple(const DoubleVec& cfTimes_, const DoubleVec& cfAmts_, double rate_)
{
    sanityCheck(rate_, cfTimes_,cfAmts_);
    double ret = 0.;
    for (int i = 0; i < cfTimes_.size(); ++i)
        ret += cfAmts_[i] / pow(1.0 + rate_, cfTimes_[i]);
    return ret;
}

double getPVPerpetuity(double fixedCF_, double rate_)
{
    sanityCheck(rate_);
    return fixedCF_ / 1 + rate_;
}

double getIRR(const DoubleVec& cfTimes_, const DoubleVec& cfAmts_)
{
    sanityCheck(cfTimes_, cfAmts_);
    auto [x0, x1] = getBracketedRange(cfTimes_, cfAmts_);
    auto f = getPVSimple(cfTimes_, cfAmts_, x0);
    double rtb = 0., dx = 0.;
    if (f < 0.) {
        rtb = x0;
        dx = x1 - x0;
    }
    else {
        rtb = x1;
        dx = x0 - x1;
    }
    constexpr int maxIter = 50;
    double xMid = 0.;
    for (int i = 0; i < maxIter; ++i) {
        dx *= .5;
        xMid = rtb + dx;
        auto fMid = getPVSimple(cfTimes_, cfAmts_, xMid);
        if (fMid <= 0.) rtb = xMid;
        if(fabs(fMid) < eps || fabs(dx) < eps) return xMid;
    }
    return ERROR_VAL;
}

Interval getBracketedRange(const DoubleVec& cfTimes_, const DoubleVec& cfAmts_)
{
    //Taken from Numerical Recipes Chapter 9 on Bisection
    double x0 = 0., x1 = 2.; //0 - 20 % permissible range, should be passed as an arg_
    constexpr double maxIterations = 50;
    auto f1 = getPVSimple(cfTimes_, cfAmts_, x0);
    auto f2 = getPVSimple(cfTimes_, cfAmts_, x1);
    for (int i = 0; i< maxIterations; ++i) {
        if (f1 * f2 < 0.) break;
        if (fabs(f1) < fabs(f2)) f1 = getPVSimple(cfTimes_, cfAmts_, x0 += 1.6* (x0 - x1));
        else f2 = getPVSimple(cfTimes_, cfAmts_, x1 += 1.6* (x1 - x0));
    }
    if (f1 * f2 > 0.) throw ("Unable to find a bracket for IRR ");
    return {x0, x1};
}

void sanityCheck(double rate_, const DoubleVec& cfTimes_, const DoubleVec& cfAmts_, bool checkRate_)
{
    if (rate_ == 0. && checkRate_) throw("0 rate supplied\n");
    if (cfTimes_.size() != cfAmts_.size()) throw("Cashflow vector and schedule have different sizes ");
}

void sanityCheck(const DoubleVec& cfTimes_, const DoubleVec& cfAmts_)
{
    sanityCheck(0, cfTimes_, cfAmts_);
}

void sanityCheck(double rate_)
{
    sanityCheck(rate_, {}, {}, true);
}
