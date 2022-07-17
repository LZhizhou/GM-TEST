#include "RequestTest.hpp"
#include <chrono>
#include <iostream>
#include <algorithm>
#include <map>
#include <math.h>
#include <numeric>

void RequestTest ::start(const std ::string &uri)
{
    m_startTime = std ::chrono ::system_clock ::now();
}

void RequestTest ::finish()
{
    std::chrono::system_clock::time_point endTime = std::chrono::system_clock::now();
    // calculate the response time in milliseconds
    m_requestTimes.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_startTime).count());
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
    // Boundaries of bins should be int, and it should be rounded to the nearest int.
    // to avoid the situation that potentially makes the number of bins exceeds the limit
    int binSize = ceil((maxElement - minElement) / numberOfBins);

    for (auto &requestTime : m_requestTimes)
    {
        // calculate which bin the request time belongs to
        int binNumber = ceil((requestTime - minElement) / binSize);
        histogram[minElement + binNumber * binSize]++;
    }
    int binCount = floor((maxElement - minElement) / binSize);

    // Iterate the bins of histogram check if there is any empty bin
    // If there is, we should reduce the number of bins
    for (int i = minElement; i < minElement + binCount * binSize; i += binSize)
    {
        // check if the bin is empty
        if (histogram.count(i) == 0)
        {
            return generateHistogram(numberOfBins - 1);
        }
    }
    // add the upper bound of the last bin
    histogram[minElement + (binCount + 1) * binSize] = 0;
    return histogram;
}

void RequestTest::drawHistogram()
{
    std::map<int, int> histogram = generateHistogram();

    int maxElement = (*std::max_element(
                          histogram.begin(), histogram.end(),
                          [](const std::pair<int, int> &p1, const std::pair<int, int> &p2)
                          {
                              return p1.second < p2.second;
                          }))
                         .second;
    int sum = std::accumulate(histogram.begin(), histogram.end(), 0,
                              [](const int prevSum, const std::pair<int, int> &entry)
                              {
                                  return prevSum + entry.second;
                              });
    for (int i = maxElement; i > 0; i--)
    {
        std::cout.width(2);
        // print y-axis
        std::cout << std::right << 100 * i / sum << "% | ";
        // draw histogram from top to bottom
        for (auto &bin : histogram)
        {
            if (bin.second >= i)
            {
                std::cout << "   *   ";
            }
            else
            {
                std::cout << "       ";
            }
        }
        std::cout << "\n";
    }

    for (int i = 0; i < histogram.size(); i++)
    {
        std::cout << "-------";
    }

    std::cout << std::endl
              << "      ";

    // print x-axis
    for (auto &bin : histogram)
    {
        std::cout.width(7);
        std::cout << std::left << bin.first;
    }
    std::cout << std::endl;
}

void RequestTest::printResults()
{
    std::cout << "Mean: " << RequestTest::mean() << " milliseconds" << std::endl;
    std::cout << "Standard deviation: " << RequestTest::standardDeviation() << " milliseconds" << std::endl;
    RequestTest::drawHistogram();
}