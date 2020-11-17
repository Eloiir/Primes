//  standard function to check if single integer is a prime
bool primeCheck(unsigned long int input);

/**
*  input: how many elements
*  output: vector of boolean values - true for index being prime and false for index not being prime
*  being calculated using Sieve of Eratosthenes
**/
std::vector<bool> primeTable(const unsigned long int& howMany);

/*
//  used by primeTable(), sets all values in a vector true
void thrSetVectorTrue(std::vector<bool>& isPrime, const unsigned int id);

//  used by primeTable(), calculates primes in range 0 - sqrt(input)
void thrInit(std::vector<bool>& isPrime, std::vector<unsigned int>& initResult, const unsigned int id, const unsigned int& howManySqrt);

//  used by primeTable(), sets elements being multiples of primes(calculated in thrInit()) false
void thrFalsePrimeMultiples(std::vector<bool>& isPrime, const std::vector<unsigned int>& initResult, const int id);
*/
