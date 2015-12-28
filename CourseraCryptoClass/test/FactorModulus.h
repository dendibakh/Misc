#pragma once

#include "gmpxx.h"
#include <utility>

std::pair<mpz_class, mpz_class> factorModulus(mpz_class N);
