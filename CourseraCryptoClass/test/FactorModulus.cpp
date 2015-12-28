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
}

std::pair<mpz_class, mpz_class> factorModulus(mpz_class N)
{
        mpz_class A = computeA(N);
        mpz_class x = computeX(A, N);
        mpz_class p;
        mpz_sub(p.get_mpz_t(), A.get_mpz_t(), x.get_mpz_t()); // p = A - x;
        mpz_class q;
        mpz_add(q.get_mpz_t(), A.get_mpz_t(), x.get_mpz_t()); // q = A + x;
	return std::make_pair(p, q);
}