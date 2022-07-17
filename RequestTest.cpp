#include "RequestTest.hpp"
#include <chrono>
#include <iostream>
#include <algorithm>
#include <map>
#include <math.h>
#include <numeric>

void RequestTest ::start(const std ::string &uri)
{
    m_startTimes.push(std ::chrono ::system_clock ::now());
}
void RequestTest ::finish()
{
    std::chrono::system_clock::time_point endTime = std::chrono::system_clock::now();
    std::chrono::system_clock::time_point startTime = m_startTimes.front();
    m_startTimes.pop();
    m_requestTimes.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count());
    std::sort(m_requestTimes.begin(), m_requestTimes.end());
}
unsigned int RequestTest ::mean()
{
    unsigned int sum = 0;
    for (auto &requestTime : m_requestTimes)
        sum += requestTime;
    return sum / m_requestTimes.size();
}
unsigned int RequestTest ::standardDeviation()
{
    unsigned int sum = 0;
    unsigned int mean = RequestTest::mean();
    for (auto &requestTime : m_requestTimes)
        sum += (requestTime - mean) * (requestTime - mean);
    return sum / m_requestTimes.size();
}

std::map<int, int> RequestTest::generateHistogram()
{
    return generateHistogram(RequestTest::m_maxNumberOfBins);
}
std::map<int, int> RequestTest::generateHistogram(int numberOfBins)
{
    std::map<int, int> histogram;
    int minElement = *std::min_element(m_requestTimes.begin(), m_requestTimes.end());
    int maxElement = *std::max_element(m_requestTimes.begin(), m_requestTimes.end());
    int binSize = ceil((maxElement - minElement) / numberOfBins);

    for (auto &requestTime : m_requestTimes)
    {
        int binNumber = ceil((requestTime - minElement) / binSize);
        histogram[minElement + binNumber * binSize]++;
    }
    int binCount = floor((maxElement - minElement) / binSize);

    for (int i = minElement; i < minElement + binCount * binSize; i += binSize)
    {
        if (histogram.count(i) == 0)
        {
            return generateHistogram(numberOfBins - 1);
        }
    }
    histogram[minElement + (binCount + 1) * binSize] = 0;
    return histogram;
}

void RequestTest::drawHistogram()
{
    std::map<int, int> histogram = generateHistogram();
    std::cout << "Histogram:" << std::endl;
    for (auto &bin : histogram)
    {
        std::cout << bin.first << " - " << bin.first + bin.second << ": " << bin.second << std::endl;
    }
}
