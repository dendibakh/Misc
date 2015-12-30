#pragma once

#include "gmpxx.h"
#include <utility>

std::pair<mpz_class, mpz_class> factorModulus(mpz_class N);
std::pair<mpz_class, mpz_class> factorModulusInBiggerRange(mpz_class N);
std::pair<mpz_class, mpz_class> factorModulus3P2Q(mpz_class N);
