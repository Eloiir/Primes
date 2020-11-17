/**
*  primeTable.cpp
*
*  Implementanion of Sieve of Eratosthenes.
*  input: one integer
*  output: a boolean vector, where true indicates that the index is prime, and false otherwise
*
*  sets all values in a vector true
*  calculates primes in range 0 - sqrt(input)
*  sets elements being multiples of primes(calculated in thrInit()) false
*  index of every element still true must be prime
*
*  Author:  Eloiir
*  Date:  November 17th, 2020
**/

#include <vector>
#include <cmath>
#include <thread>
#include <mutex>

#include "primeTable.h"

using namespace std;

const unsigned int THREAD_COUNT = thread::hardware_concurrency();
mutex initResLock;

bool primeCheck(unsigned long int input){
    if (input < 2) {
        return false;
    }
    else {
        for (int i=2; i <= sqrt(input); ++i) {
            if (input % i == 0) {
                return false;
            }
        }
    }
    return true;
}

vector<bool> vecPrimeCheck(const unsigned long int& howMany){
    vector<bool> result;
    for(unsigned int i = 0; i < howMany; i++){
        result.push_back(primeCheck(i));
    }
    return result;
}

void thrSetVectorTrue(vector<bool>& isPrime, const unsigned int id){
    unsigned int low = (id*isPrime.size()/THREAD_COUNT);
    unsigned int high = (((id+1)*isPrime.size()/THREAD_COUNT)-1);

    for(unsigned int i=low; i<=high; i++){
        isPrime.at(i) = true;
    }
}

void thrInit(vector<bool>& isPrime, vector<unsigned int>& initResult, const unsigned int id, const unsigned int& howManySqrt){
    unsigned int low = (id*howManySqrt/THREAD_COUNT);
    unsigned int high = (((id+1)*howManySqrt/THREAD_COUNT)-1);
    if(id == (THREAD_COUNT-1)) high++;

    for(unsigned int i=low; i<=high; i++){
        if(primeCheck(i)){
            initResLock.lock();
            initResult.push_back(i);
            initResLock.unlock();
        }
        else{
            isPrime.at(i) = false;
        }
    }
}

void thrFalsePrimeMultiples(vector<bool>& isPrime, const vector<unsigned int>& initResult, const int id){
    const int tempResultSize = initResult.size();
    for(int i=id; i<tempResultSize; i+=THREAD_COUNT){
        const unsigned long int howMuch = isPrime.size();
        const unsigned long int prime = initResult.at(i);
        for(unsigned int primeMultiple=(prime*2); primeMultiple<howMuch; primeMultiple+=prime){
            isPrime.at(primeMultiple) = false;
        }
    }
}

vector<bool> primeTable(const unsigned long int& howMany){
    if(howMany < (THREAD_COUNT*THREAD_COUNT)){
        return vecPrimeCheck(howMany);
    }

    vector<unsigned int> initResult;
    vector<bool> isPrime(howMany);
    unsigned int howManySqrt = floor(sqrt(howMany));

    thread thr1[THREAD_COUNT];
    for(unsigned int i=0; i<THREAD_COUNT; i++){
        thr1[i] = thread(thrSetVectorTrue, ref(isPrime), i);
    }
    for(unsigned int i=0; i<THREAD_COUNT; i++){
        thr1[i].join();
    }

    thread thr2[THREAD_COUNT];
    for(unsigned int i=0; i<THREAD_COUNT; i++){
        thr2[i] = thread(thrInit, ref(isPrime), ref(initResult), i, howManySqrt);
    }
    for(unsigned int i=0; i<THREAD_COUNT; i++){
        thr2[i].join();
    }

    thread thr3[THREAD_COUNT];
    for(unsigned int i=0; i<THREAD_COUNT; i++){
        thr3[i] = thread(thrFalsePrimeMultiples, ref(isPrime), ref(initResult), i);
    }
    for(unsigned int i=0; i<THREAD_COUNT; i++){
        thr3[i].join();
    }

    return isPrime;
}
