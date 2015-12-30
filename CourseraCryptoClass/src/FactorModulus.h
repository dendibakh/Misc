#pragma once

#include "gmpxx.h"
#include <utility>
#include <string>

std::pair<mpz_class, mpz_class> factorModulus(mpz_class N);
std::pair<mpz_class, mpz_class> factorModulusInBiggerRange(mpz_class N);
std::pair<mpz_class, mpz_class> factorModulus3P2Q(mpz_class N);
std::string decryptRSA(mpz_class cipherText, mpz_class N, mpz_class e);
