#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <thread>

#include "testCase.h"
#include "primeTable.h"

using namespace std;

const unsigned int THREAD_COUNT = thread::hardware_concurrency();

int main(){
    unsigned long int howMany;
    while((cout << "\nHow many elements(0 to exit): ") &&
          (cin >> howMany) &&
          (howMany)){
        clock_t start = clock();
        vector <bool> primes = primeTable(howMany);
        clock_t stop = clock();

        cout << "\nTime elapsed: " << ((stop - start) / double(CLOCKS_PER_SEC)) << '\n';

        bool write;
        if((cout << "Write primes? (1-yes, 0-no): ") &&
        (cin >> write) && (write)){
            for(unsigned int i=0; i<howMany; i++){
                if(primes.at(i))
                    cout << setw(12) << i;
            }
        }


        bool test;
        if((cout << "\nCalculate test case? (1-yes, 0-no): ") &&
        (cin >> test) && (test)){
            cout << "\nTest case:\n";
            start = clock();
            vector <bool> primes2 = manageThrTestCase(howMany);
            stop = clock();

            cout << "\nTime elapsed: " << ((stop - start) / double(CLOCKS_PER_SEC)) << '\n';

            if((cout << "Write primes? (1-yes, 0-no): ") &&
                (cin >> write) && (write)){
                for(unsigned int i=0; i<howMany; i++){
                    if(primes2.at(i))
                        cout << setw(12) << i;
                }
            }
        }

        cout << endl;
    }
    return 0;
}
