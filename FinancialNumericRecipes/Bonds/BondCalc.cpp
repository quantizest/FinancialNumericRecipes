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

void sanityCheck(double rate_, const DoubleVec& cfTimes_, const DoubleVec& cfAmts_)
{
    if (rate_ == 0.) throw std::runtime_error("0 rate supplied\n");
    if (cfTimes_.size() != cfAmts_.size()) throw "Cashflow vector and schedule have different sizes ";
}
