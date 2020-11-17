#include <vector>
#include <cmath>
#include <thread>

#include "testCase.h"
#include "primeTable.h"

using namespace std;

const unsigned int THREAD_COUNT = thread::hardware_concurrency();

void thrTestCase(vector<bool>& result, const unsigned int id, const unsigned long int howMany){
    unsigned int low = (id*howMany/THREAD_COUNT);
    unsigned int high = (((id+1)*howMany/THREAD_COUNT)-1);

    for(unsigned int i=low; i<=high; i++){
        result.at(i) = primeCheck(i);
    }
}

vector<bool> manageThrTestCase(unsigned long int howMany){
    vector<bool> result(howMany);

    thread thr1[THREAD_COUNT];
    for(unsigned int i=0; i<THREAD_COUNT; i++){
        thr1[i] = thread(thrTestCase, ref(result), i, howMany);
    }
    for(unsigned int i=0; i<THREAD_COUNT; i++){
        thr1[i].join();
    }
    return result;
}
