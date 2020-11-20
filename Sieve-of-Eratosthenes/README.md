The function in primeTable.cpp is the file you're interested in, or specifically - the primeTable() function inside primeTable.cpp.

primeTable():

input: one integer

output: a boolean vector, where true indicates that the index is prime, and false otherwise

main.cpp shows an example of use

Calculations are done using the Sieve of Eratosthenes, and using all threads. 
If the input is lesser than THREAD_COUNT^2 it switches to other function, because threads.
