#include "FactorModulus.h"

namespace
{
    mpz_class computeA(mpz_class N)
    {
    	mpz_class A;
        mpz_sqrt(A.get_mpz_t(), N.get_mpz_t()); // truncated sqrt(A)
        mpz_add_ui(A.get_mpz_t(), A.get_mpz_t(), 1); // + 1, like ceiling function would do
        return A;
    }

    mpz_class computeX(mpz_class A, mpz_class N)
    {
    	mpz_class x;
    	mpz_pow_ui(x.get_mpz_t(), A.get_mpz_t(), 2); // A^2
        mpz_sub(x.get_mpz_t(), x.get_mpz_t(), N.get_mpz_t()); // A^2 - N
        mpz_sqrt(x.get_mpz_t(), x.get_mpz_t()); // truncated sqrt(A^2 - N)
        return x;
    }

    std::pair<mpz_class, mpz_class> computeTwoFactorsFromX(mpz_class x, mpz_class A)
    {
    	mpz_class p = A - x;
        mpz_class q = A + x;
        return std::make_pair(p, q);
    }
}

std::pair<mpz_class, mpz_class> factorModulus(mpz_class N)
{
        mpz_class A = computeA(N);
        mpz_class x = computeX(A, N);
	return computeTwoFactorsFromX(x, A);
}

namespace
{
    bool isAFactorAvg(mpz_class A, mpz_class N)
    {
    	mpz_class x = computeX(A, N);
        mpz_class p = A - x;
        mpz_class q = A + x;
        return N == p * q;
    }
}

std::pair<mpz_class, mpz_class> factorModulusInBiggerRange(mpz_class N)
{
	mpz_class A = computeA(N);
	while (!isAFactorAvg(A, N))
	{
	    A += 1;
	}
	mpz_class x = computeX(A, N);
	return computeTwoFactorsFromX(x, A);
}

std::pair<mpz_class, mpz_class> factorModulus3P2Q(mpz_class N)
{
        mpz_class A = computeA(N * 24);
        mpz_class x = computeX(A, N * 24);
	mpz_class p = (A - x) / 6;
        mpz_class q = (A + x) / 4;
        return std::make_pair(p, q);
}

/*

// Here is solution via exhaustive search. It won't find answer for big numbers !!!

#include <iostream>

namespace
{
    mpf_class computeTarget(mpz_class N)
    {
    	mpf_class target;
    	mpf_class floatN(N);
        mpf_sqrt(target.get_mpf_t(), floatN.get_mpf_t()); // sqrt(6N)
        return target;
    }
    
    bool isTargetReached(mpz_class A, mpz_class N, mpf_class target)
    {
    	//mpz_class x = computeX(A, N) + 1;
    	mpz_class x = computeX(A, N);
    	std::cout << "cuurent A: " << A.get_mpz_t() << std::endl;
    	std::cout << "computed x: " << x.get_mpz_t() << std::endl;
        mpf_class p = A - x;
        mpf_class q = A + x;
        mpf_class actual = ( 3 * p + 2 * q ) / 2;
        std::cout << "actual: " << actual.get_mpf_t() << std::endl;
        mpf_class error = actual - target;
        std::cout << "error: " << error.get_mpf_t() << std::endl;
        mpf_class absError = abs(error);
        std::cout << "abs error: " << absError.get_mpf_t() << std::endl;
        return absError <= 0.125f && p * q == N;
    }
}

std::pair<mpz_class, mpz_class> factorModulus3P2Q(mpz_class N)
{
        mpz_class A = computeA(N);
        std::cout << "A: " << A.get_mpz_t() << std::endl;
        mpf_class target = computeTarget(N * 6);
        std::cout << "target: " << target.get_mpf_t() << std::endl;
        int i = 0;
        while (!isTargetReached(A, N, target))
	{
	    A += 1;
	    ++i;
	}
        //mpz_class x = computeX(A, N) + 1;
        mpz_class x = computeX(A, N);
	return computeTwoFactorsFromX(x, A);
}
*/
