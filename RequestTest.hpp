#include "Request.hpp"
#include <vector>
#include <chrono>
#include <map>
#include <queue>

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
    std::vector<int> m_requestTimes;
    /**
     * This queue holds the start time of all requests that have not yet finished,
     * the more front the earlier is processed
     */
    std::queue<std::chrono::system_clock::time_point> m_startTimes;
    /**
     * Convert the existing request response time into a mapping, where the key is
     * the value to the left of the bin and the value is the number within the bin.
     *
     * @param [in] numberOfBins The number of bins to use in the histogram
     */
    std::map<int, int> generateHistogram(int numberOfBins);
    /**
     * overloaded version of generateHistogram that uses the default number of bins
     *
     * of @see #m_maxNumberOfBins
     */
    std::map<int, int> generateHistogram();

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
    unsigned int mean();
    /**
     *
     * @return the standard deviation of the response times
     */
    unsigned int standardDeviation();
    /**
     *
     * print a histogram of the response times
     */
    void drawHistogram();
};