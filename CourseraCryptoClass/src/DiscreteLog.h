#pragma once

#include "gmpxx.h"

mpz_class computeDiscreteLog(mpz_class p, mpz_class g, mpz_class h, long int b);
mpz_class computeInvertedG(mpz_class p, mpz_class g);
mpz_class computeLeftHandSide(mpz_class p, mpz_class g, mpz_class h, long int exp);
mpz_class computeGRaisedToB(mpz_class p, mpz_class g, long int B);
mpz_class computeRightHandSide(mpz_class p, mpz_class g, long int exp);
mpz_class computeX(mpz_class x0, long int B, mpz_class x1);