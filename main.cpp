#include "RequestTest.hpp"
#include <iostream>

using namespace std;
int main()
{
    RequestTest test(15);
    for (int i = 0; i < 100; i++)
    {
        test.process("url1");
    }
    for (int i = 0; i < 200; i++)
    {
        test.process("url2");
    }
    test.printResults();
    return 0;
}
