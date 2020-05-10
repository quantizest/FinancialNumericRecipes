

#include "BondTest.h"

void testBonds()
{
    testPV();
    testPerpetuity();
    testIRR();
}

void testPV()
{
    DoubleVec cf = {-100, 75, 75};
    DoubleVec times = {0, 1, 2};
    double rate = 0.1;
    auto ret = getPVSimple(times, cf, rate);
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
    auto irr = getIRR(times, cf);
    assert(fabs(irr - 0.1) < eps);
}
