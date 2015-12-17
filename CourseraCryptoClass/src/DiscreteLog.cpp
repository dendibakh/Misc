#include "DiscreteLog.h"
#include <unordered_map>

mpz_class computeInvertedG(mpz_class p, mpz_class g)
{
	mpz_class gInv;
        mpz_invert(gInv.get_mpz_t(), g.get_mpz_t(), p.get_mpz_t()); // g^-1
        return gInv;
}

mpz_class computeLeftHandSide(mpz_class p, mpz_class g, mpz_class h, long int exp)
{
	mpz_class result;
        mpz_powm_ui(result.get_mpz_t(), g.get_mpz_t(), exp, p.get_mpz_t()); // g^x1
        mpz_mul(result.get_mpz_t(), h.get_mpz_t(), result.get_mpz_t());     // h * g^x1
        mpz_mod(result.get_mpz_t(), result.get_mpz_t(), p.get_mpz_t());
        return result;
}

mpz_class computeGRaisedToB(mpz_class p, mpz_class g, long int B)
{
	mpz_class result;
        mpz_powm_ui(result.get_mpz_t(), g.get_mpz_t(), B, p.get_mpz_t()); // g^B
        return result;
}

mpz_class computeRightHandSide(mpz_class p, mpz_class g, long int exp)
{
	mpz_class result;
        mpz_powm_ui(result.get_mpz_t(), g.get_mpz_t(), exp, p.get_mpz_t()); // g^x0
        return result;
}

mpz_class computeX(mpz_class x0, long int B, mpz_class x1)
{
	mpz_class result(x1);
        mpz_addmul_ui (result.get_mpz_t(), x0.get_mpz_t(), B); // result = x0 * B + x1
        return result;
}

namespace std
{
        template <> struct hash<mpz_class>
        {
          size_t operator()(const mpz_class& x) const
          {
            return x.get_mpz_t()[0]._mp_size != 0 ? static_cast<size_t>(x.get_mpz_t()[0]._mp_d[0]) : 0;
          }
        };
}

mpz_class computeDiscreteLog(mpz_class p, mpz_class g, mpz_class h, long int b)
{
        std::unordered_map<mpz_class, long int> set;

        mpz_class gInv(computeInvertedG(p, g));
        for (long int i = 0; i < b; ++i)
        {
                set.insert(std::make_pair(computeLeftHandSide(p, gInv, h, i), i));
        }

        mpz_class gToB(computeGRaisedToB(p, g, b));
        for (long int i = 0; i < b; ++i)
        {
                auto iter = set.find(computeRightHandSide(p, gToB, i));
                if (iter != set.end())
                        return computeX(i, b, iter->second);
        }

        return mpz_class(0);
}