

#include "BondTest.h"

void BondTest::testBonds()
{
    testPV();
    testPerpetuity();
    testIRR();
    testYTM();
    testDuration();
    testMacDuration();
    testModifiedDuration();
    testConvexity();
    
    bondCalc.rateType(BondCalc::RateType::CONTINOUS);
    testPVCont();
    testDurationCont();
    testConvexityCont();
    
    testContRateConversion();
    testDiscRateConversion();
}

void BondTest::testPV()
{
    DoubleVec cf = {-100, 75, 75};
    DoubleVec times = {0, 1, 2};
    double rate = 0.1;
    auto ret = bondCalc.getPV(times, cf, rate);
    assert(fabs(ret - 30.165289) < eps);
}

void BondTest::testPVCont()
{
    DoubleVec cf = {10, 10, 110};
    DoubleVec times = {1, 2, 3};
    double rate = 0.09;
    auto ret = bondCalc.getPV(times, cf, rate);
    assert(fabs(ret - 101.4637583) < eps);
}

void BondTest::testPerpetuity()
{
    double rate = 0.1;
    double cf = 100;
    auto ret = bondCalc.getPVPerpetuity(cf, rate);
    assert(fabs(ret - 1000) < eps);
}

void BondTest::testIRR()
{
    DoubleVec cf = {-100, 10, 110};
    DoubleVec times = {0, 1, 2};
    auto ret = bondCalc.getIRR(times, cf);
    assert(fabs(ret - 0.1) < eps);
}

void BondTest::testYTM()
{
    DoubleVec cf = { 10, 10, 110};
    DoubleVec times = { 1, 2, 3};
    double r = 0.09;
    auto bp = bondCalc.getPV(times, cf, r);
    auto ret = bondCalc.getYTMDiscrete(times, cf, bp);
    assert(fabs(ret - 0.09) < eps);
}

void BondTest::testDuration()
{
    DoubleVec cf = { 10, 10, 110};
    DoubleVec times = { 1, 2, 3};
    double r = 0.09;
    auto ret = bondCalc.getDuration(times, cf, r);
    assert(fabs(ret - 2.7389536) < eps);
}

void BondTest::testMacDuration()
{
    DoubleVec cf = { 10, 10, 110};
    DoubleVec times = { 1, 2, 3};
    double r = 0.09;
    auto bp = bondCalc.getPV(times, cf, r);
    auto ret = bondCalc.getMacDuration(times, cf, bp);
    assert(fabs(ret - 2.7389536) < eps);
}

void BondTest::testModifiedDuration()
{
    DoubleVec cf = { 10, 10, 110};
    DoubleVec times = { 1, 2, 3};
    double r = 0.09;
    auto bp = bondCalc.getPV(times, cf, r);
    auto ret = bondCalc.getModifiedDuration(times, cf, bp);
    assert(fabs(ret - 2.51280147) < eps);
}

void BondTest::testDurationCont()
{
    DoubleVec cf = { 10, 10, 110};
    DoubleVec times = { 1, 2, 3};
    double r = 0.09;
    auto ret = bondCalc.getDuration(times, cf, r);
    assert(fabs(ret - 2.7375286) < eps);
}


void BondTest::testConvexity()
{
    DoubleVec cf = { 10, 10, 110};
    DoubleVec times = { 1, 2, 3};
    double r = 0.09;
    auto ret = bondCalc.getConvexity(times, cf, r);
    assert(fabs(ret - 8.93247876) < eps);
}

void BondTest::testConvexityCont()
{
    DoubleVec cf = { 10, 10, 110};
    DoubleVec times = { 1, 2, 3};
    double r = 0.09;
    auto ret = bondCalc.getConvexity(times, cf, r);
    assert(fabs(ret - 7.8677927) < eps);
}

void BondTest::testContRateConversion()
{
    double fixedRate = .15;
    int numPeriods = 12;
    auto ret = utils::getContRate(fixedRate, numPeriods);
    assert(fabs(ret - .1490702) < eps);
}

void BondTest::testDiscRateConversion()
{
    double contRate = .12;
    int numPeriods = 4;
    auto ret = utils::getDiscreteRate(contRate, numPeriods);
    assert(fabs(ret - .121818) < eps);
}
