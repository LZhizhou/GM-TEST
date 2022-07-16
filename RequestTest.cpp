#include "RequestTest.hpp"
#include <chrono>
#include <iostream>
#include <algorithm>
#include <map>
#include <math.h>
#include <numeric>

void RequestTest ::start(const std ::string &uri)
{
}
void RequestTest ::finish()
{
}
unsigned int RequestTest ::mean()
{
}
unsigned int RequestTest ::standardDeviation()
{
}

std::map<int, int> RequestTest::generateHistogram()
{
    return generateHistogram(RequestTest::m_maxNumberOfBins);
}
std::map<int, int> RequestTest::generateHistogram(int numberOfBins)
{
}

void RequestTest::drawHistogram()
{
}
