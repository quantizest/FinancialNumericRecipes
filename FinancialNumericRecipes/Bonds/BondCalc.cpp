#include "BondCalc.h"

double BondCalc::getDiscFactor(double rate_, double time_)
{
   switch (_rateType) {
        case RateType::DISCRETE:
            return 1 / pow(1.0 + rate_, time_);
        case RateType::CONTINOUS:
            return exp(-rate_ * time_);
        default:
            break;
    }
}

double BondCalc::getPV(const DoubleVec& cfTimes_, const DoubleVec& cfAmts_, double rate_)
{
    double ret = 0.;
    for (int i = 0; i < cfTimes_.size(); ++i)
        ret += cfAmts_[i] * getDiscFactor(rate_, cfTimes_[i]);
    return ret;
}

double BondCalc::getPVPerpetuity(double fixedCF_, double rate_)
{
    utils::sanityCheck(rate_);
    return (rate_ != 0.) ? fixedCF_ / rate_ : 0.;
}

double BondCalc::getIRR(const DoubleVec& cfTimes_, const DoubleVec& cfAmts_)
{
    utils::sanityCheck(cfTimes_, cfAmts_);
    auto [x0, x1] = getBracketedRange(cfTimes_, cfAmts_);
    auto f = getPV(cfTimes_, cfAmts_, x0);
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
        auto fMid = getPV(cfTimes_, cfAmts_, xMid);
        if (fMid <= 0.) rtb = xMid;
        if(fabs(fMid) < eps || fabs(dx) < eps) return xMid;
    }
    return ERROR_VAL;
}

Interval BondCalc::getBracketedRange(const DoubleVec& cfTimes_, const DoubleVec& cfAmts_)
{
    //Taken from Numerical Recipes Chapter 9 on Bisection
    double x0 = 0., x1 = 2.; //0 - 200 % permissible range, should be passed as an arg_
    constexpr double maxIterations = 50;
    auto f1 = getPV(cfTimes_, cfAmts_, x0);
    auto f2 = getPV(cfTimes_, cfAmts_, x1);
    for (int i = 0; i< maxIterations; ++i) {
        if (f1 * f2 < 0.) break;
        if (fabs(f1) < fabs(f2)) f1 = getPV(cfTimes_, cfAmts_, x0 += 1.6 * (x0 - x1));
        else f2 = getPV(cfTimes_, cfAmts_, x1 += 1.6 * (x1 - x0));
    }
    if (f1 * f2 > 0.) throw ("Unable to find a bracket for IRR ");
    return {x0, x1};
}

double BondCalc::getYTMDiscrete(const DoubleVec& cfTimes_, const DoubleVec& cfAmts_, double bondDirtyPrice_)
{
    utils::sanityCheck(cfTimes_, cfAmts_);
    constexpr int maxIterations = 200;
    double low = 0., high = 1.;
    double mid = (low + high) / 2;
    for (int i = 0; i < maxIterations; ++i)
    {
        double diff = getPV(cfTimes_, cfAmts_, mid) - bondDirtyPrice_;
        if (fabs(diff) < eps) break;
        else if (diff > 0.) low = mid;
        else high = mid;
        mid = (low + high) / 2;
    }
    return mid;
}

double BondCalc::getDuration(const DoubleVec& cfTimes_, const DoubleVec& cfAmts_, double rate_)
{
    double num = 0., denom = 0.;
    for (int i = 0; i < cfTimes_.size(); ++i) {
        num += cfTimes_[i] * cfAmts_[i] * getDiscFactor(rate_, cfTimes_[i]);
    }
    denom = getPV(cfTimes_, cfAmts_, rate_);
    if (denom == 0.) throw ("Zero PV! Can't calc duration ");
    return num / denom;
}

double BondCalc::getMacDuration(const DoubleVec& cfTimes_, const DoubleVec& cfAmts_, double bondDirtyPrice_)
{
    double yield = getYTMDiscrete(cfTimes_, cfAmts_, bondDirtyPrice_);
    return getDuration(cfTimes_, cfAmts_, yield);
}

double BondCalc::getModifiedDuration(const DoubleVec& cfTimes_, const DoubleVec& cfAmts_, double bondDirtyPrice_)
{
    //Can't reuse MacDarution as yield is requied
    // MacDuration / 1 + y
    double yield = getYTMDiscrete(cfTimes_, cfAmts_, bondDirtyPrice_);
    double duration = getDuration(cfTimes_, cfAmts_, yield);
    return duration / (1 + yield);
}

double BondCalc::getConvexity(const DoubleVec& cfTimes_, const DoubleVec& cfAmts_, double rate_)
{
    double conv = 0.;
    bool isCont = (_rateType == RateType::CONTINOUS);
    for (int i = 0; i < cfTimes_.size(); ++i)
        conv += cfTimes_[i] * ( isCont ? (cfTimes_[i]) : 1 + cfTimes_[i]) * cfAmts_[i] * getDiscFactor(rate_, cfTimes_[i]);
    double pv = getPV(cfTimes_, cfAmts_, rate_);
    if (!isCont) pv *= (1 + rate_) * (1 + rate_);
    return conv / pv ;
}

double utils::getContRate(double discreteRate_, int numPeriods_)
{
    sanityCheck(discreteRate_);
    if (numPeriods_ == 0.) throw ("0 Num of periods specified ");
    return numPeriods_ * log(1 + discreteRate_ / numPeriods_);
}

double utils::getDiscreteRate(double contRate_, int numPeriods_)
{
    sanityCheck(contRate_);
    if (numPeriods_ == 0.) throw ("0 Num of periods specified ");
    return numPeriods_ * (exp(contRate_ / numPeriods_) - 1);
}

void utils::sanityCheck(double rate_, const DoubleVec& cfTimes_, const DoubleVec& cfAmts_, bool checkRate_)
{
    if ((rate_ == 0.  || rate_ <= -1.) && checkRate_) throw("0 rate supplied\n");
    if (cfTimes_.size() != cfAmts_.size()) throw("Cashflow vector and schedule have different sizes ");
}

void utils::sanityCheck(const DoubleVec& cfTimes_, const DoubleVec& cfAmts_)
{
    sanityCheck(0, cfTimes_, cfAmts_);
}

void utils::sanityCheck(double rate_)
{
    sanityCheck(rate_, {}, {}, true);
}
