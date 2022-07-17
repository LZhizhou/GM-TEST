#include "RequestTest.hpp"
#include <iostream>

using namespace std;
int main() {
	RequestTest *test = new RequestTest(15);
    for(int i = 0 ; i < 100; i++){
        test->process("url1");
    }
    test->printResults();
    delete test;
    
    RequestTest *test2 = new RequestTest(15);
    for(int i = 0 ; i < 100; i++){
        test2->process("url2");
    }
    test->printResults();
    delete test2;
	return 0;
}
