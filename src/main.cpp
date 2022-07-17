#include "RequestTest.hpp"
#include <cstring>
#include <iostream>

using namespace std;
/**
 * @brief The main function
 *
 * -b <number of bins> : The max number of bins to use in the histogram,
 * default is 10.
 *
 * -u <URL> : The URL to request
 *
 * -n <number of requests> : The number of requests to make,
 * default is 100.
 *
 */
int main(int argc, char *argv[])
{
    int maxNumberOfBins = 10;
    map<string, int> requests;
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-b") == 0 && i + 1 < argc)
        {
            maxNumberOfBins = atoi(argv[i + 1]);
            i++;
        }
        else if (strcmp(argv[i], "-u") == 0 && i + 1 < argc)
        {

            if (i + 3 < argc && strcmp(argv[i + 2], "-n") == 0 && atoi(argv[i + 3]) > 0)
            {
                requests[argv[i + 1]] = atoi(argv[i + 3]);
                i += 2;
            }
            else
            {
                requests[argv[i + 1]] = 100;
            }
            i++;
        }
    }

    RequestTest test(maxNumberOfBins);
    for (auto request : requests)
    {
        for (int i = 0; i < request.second; i++)
        {
            test.process(request.first);
        }
    }

    test.printResults();
    return 0;
}
