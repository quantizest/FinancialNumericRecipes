

#include "BondTest.h"

void testBonds()
{
    testPV();
    testPerpetuity();
    testIRR();
    testContRateConversion();
    testDiscRateConversion();
}

void testPV()
{
    DoubleVec cf = {-100, 75, 75};
    DoubleVec times = {0, 1, 2};
    double rate = 0.1;
    auto ret = getPV(times, cf, rate);
    assert(fabs(ret - 30.165289) < eps);
}

void testPerpetuity()
{
    double rate = 0.1;
    double cf = 100;
    auto ret = getPVPerpetuity(cf, rate);
    assert(fabs(ret - 100.0999999) < eps);
}

void testIRR()
{
    DoubleVec cf = {-100, 10, 110};
    DoubleVec times = {0, 1, 2};
    auto ret = getIRR(times, cf);
    assert(fabs(ret - 0.1) < eps);
}

void testContRateConversion()
{
    double fixedRate = .15;
    int numPeriods = 12;
    auto ret = utils::getContRate(fixedRate, numPeriods);
    assert(fabs(ret - .1490702) < eps);
}

void testDiscRateConversion()
{
    double contRate = .12;
    int numPeriods = 4;
    auto ret = utils::getDiscreteRate(contRate, numPeriods);
    assert(fabs(ret - .121818) < eps);
}
