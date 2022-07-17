#include "Request.hpp"
#include <vector>
#include <chrono>
#include <map>
#include <queue>
#include <string>

/**
 * Resource request testing class
 *
 * Instantiations of this class do state based processing of resource requests .
 * To use , instantiate an object and call process () on a URI to get the response
 * data.
 * @see #Constructor(int)
 */
class RequestTest : public Request
{
private:
    /**
     * The maximum number of bins per histogram, passed from the constructor

     */
    int m_maxNumberOfBins;
    /**
     * The response time of requests processed in milliseconds
     */
    std::map<std ::string, std::vector<int>> m_requestTimes;
    /**
     * The start time of the current request
     */
    std::pair<std::string, std::chrono::system_clock::time_point> m_startTime;
    /**
     *
     * Compute histograms of the given vector of response times.
     * Start with the maximum number of bins and reduce the number of bins until
     * all bins are filled.
     *
     * @param [in] requestTimes The vector of request response times
     *
     * @param [in] numberOfBins The max number of bins to use in the histogram
     */
    std::map<int, int> generateHistogram(std::vector<int> requestTimes, int numberOfBins);

    /**
     *
     * print a given histogram.
     *
     * @param [in] histogram The histogram to print,
     * should be the result of @see #generateHistogram
     */
    void drawHistogram(std::map<int, int> histogram);

protected:
    /**
     * Start processing the request
     *
     * push start time onto queue @see #m_startTimes
     *
     * @param [in] uri The URI of the request endpoint
     */
    void start(const std ::string &uri) override;
    /** Finish processing the request, pop start time from queue @see #m_startTimes
     * calculate the response time and push it onto @see #m_requestTimes
     */
    void finish() override;

public:
    /**
     * Constructor
     *
     * @param [in] maxNumberOfBins The maximum number of bins per histogram
     */
    RequestTest(int maxNumberOfBins) : m_maxNumberOfBins(maxNumberOfBins) {}

    /**
     *
     * @return the mean response time of all requests
     */
    std::map<std::string, double> mean();

    /**
     *
     * @return the standard deviation of the response times
     */
    std::map<std::string, double> standardDeviation();

    /**
     * use @see #generateHistogram to compute the histogram of the @see #m_requestTimes
     *
     * @return The map of URL to The histogram of its response times
     *
     */
    std::map<std::string, std::map<int, int>> generateHistograms();
    /**
     *
     * print summary statistics of the response times
     * including the mean, standard deviation and histogram
     */
    void printResults();
};