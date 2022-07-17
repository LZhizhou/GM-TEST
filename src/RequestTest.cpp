#include "RequestTest.hpp"
#include <chrono>
#include <iostream>
#include <algorithm>
#include <map>
#include <cmath>
#include <numeric>

void RequestTest ::start(const std ::string &uri)
{
    m_startTime = std::make_pair(uri, std::chrono::system_clock::now());
}

void RequestTest ::finish()
{

    std::chrono::system_clock::time_point endTime = std::chrono::system_clock::now();
    // calculate the response time in milliseconds
    m_requestTimes[m_startTime.first].push_back(std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_startTime.second).count());
}

std::map<std::string, double> RequestTest ::mean()
{
    std::map<std::string, double> means;
    for (auto &request : m_requestTimes)
    {
        means[request.first] = std::accumulate(request.second.begin(), request.second.end(), 0.0) / request.second.size();
    }
    return means;
}

std::map<std::string, double> RequestTest ::standardDeviation()
{
    std::map<std::string, double> means = RequestTest::mean();
    std::map<std::string, double> standardDeviations;
    for (auto &request : m_requestTimes)
    {
        double mean = means[request.first];
        for (auto &responseTime : request.second)
        {
            standardDeviations[request.first] += pow(responseTime - mean, 2);
        }
        standardDeviations[request.first] = sqrt(standardDeviations[request.first] / request.second.size());
    }
    return standardDeviations;
}

std::map<std::string, std::map<int, int>> RequestTest ::generateHistograms()
{
    std::map<std::string, std::map<int, int>> histograms;
    for (auto &request : m_requestTimes)
    {
        histograms[request.first] = RequestTest::generateHistogram(request.second, m_maxNumberOfBins);
    }

    return histograms;
}

std::map<int, int> RequestTest::generateHistogram(std::vector<int> requestTimes, int numberOfBins)
{
    std::map<int, int> histogram;
    int minElement = *std::min_element(requestTimes.begin(), requestTimes.end());
    int maxElement = *std::max_element(requestTimes.begin(), requestTimes.end());

    // Boundaries of bins should be int, and it should be rounded to the nearest int.
    // to avoid the situation that potentially makes the number of bins exceeds the limit
    int binSize = ceil(1.0 * (maxElement - minElement) / numberOfBins);

    for (auto &requestTime : requestTimes)
    {
        // calculate which bin the request time belongs to
        int binNumber = ceil((requestTime - minElement) / binSize);
        histogram[minElement + binNumber * binSize]++;
    }

    // normalize the histogram
    for (auto &bin : histogram)
    {
        bin.second = ceil(100.0 * bin.second / requestTimes.size());
    }

    // Iterate the bins of histogram check if there is any empty bin
    // If there is, we should reduce the number of bins
    for (int i = minElement; i < minElement + numberOfBins * binSize; i += binSize)
    {
        // check if the bin is empty
        if (histogram.count(i) == 0 || histogram.at(i) == 0)
        {
            return generateHistogram(requestTimes, numberOfBins - 1);
        }
    }

    // add the upper bound of the last bin
    histogram[minElement + (numberOfBins + 1) * binSize] = 0;
    return histogram;
}

void RequestTest::drawHistogram(std::map<int, int> histogram)
{
    int maxElement = (*std::max_element(
                          histogram.begin(), histogram.end(),
                          [](const std::pair<int, int> &p1, const std::pair<int, int> &p2)
                          {
                              return p1.second < p2.second;
                          }))
                         .second;
    for (int i = maxElement; i > 0; i--)
    {
        std::cout.width(2);
        // print y-axis
        std::cout << std::right << i << "% | ";
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

    for (size_t i = 0; i < histogram.size(); i++)
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
    auto means = RequestTest::mean();
    auto standardDeviations = RequestTest::standardDeviation();
    auto histograms = RequestTest::generateHistograms();
    for (auto &request : m_requestTimes)
    {
        std::cout << "Request " << request.first << ": " << std::endl;
        std::cout << "mean: " << means[request.first] << "ms, " << std::endl;
        std::cout << "standard deviation: " << standardDeviations[request.first] << "ms, " << std::endl;
        std::cout << "histogram: " << std::endl;
        RequestTest::drawHistogram(histograms[request.first]);
        std::cout << std::endl;
    }
}