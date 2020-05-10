

#include "BondTest.h"
constexpr double eps = 1e-6;

void testBonds()
{
    testPV();
    testPerpetuity();
}

void testPV()
{
    DoubleVec cf = {-100, 75, 75};
    DoubleVec times = {0, 1, 2};
    double rate = 0.1;
    auto ret = getPVSimple(times, cf, rate);
    assert(abs(ret - 30.165289) < eps);
}

void testPerpetuity()
{
    double rate = 0;
    double cf = 100;
    auto ret = getPVPerpetuity(cf, rate);
    assert(abs(ret - 100.0999999) < eps);
}
