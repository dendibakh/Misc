#include "gtest/gtest.h"
#include "DiscreteLog.h"

using namespace testing;

TEST(DiscreteLogUnitTest, 1)
{
    mpz_t integ;
    mpz_init (integ);
    mpz_set_ui(integ, 10u);

    EXPECT_EQ(10u, mpz_get_ui(integ));

    mpz_t rop1;
    mpz_init (rop1);
    mpz_add_ui(rop1, integ, 8);

    EXPECT_EQ(18u, mpz_get_ui(rop1));

    mpz_t rop2;
    mpz_init (rop2);
    mpz_add_ui(rop2, integ, 2);

    EXPECT_EQ(12u, mpz_get_ui(rop2));

    mpz_t gcd;
    mpz_init (gcd);
    mpz_gcd (gcd, rop1, rop2);

    EXPECT_EQ(6u, mpz_get_ui(gcd));
}

TEST(DiscreteLogUnitTest, 2)
{
        mpz_class p("13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649006084171");
        mpz_class g("11717829880366207009516117596335367088558084999998952205599979459063929499736583746670572176471460312928594829675428279466566527115212748467589894601965568");
        mpz_class h("3239475104050450443565264378728065788649097520952449527834792452971981976143292558073856937958553180532878928001494706097394108577585732452307673444020333");
        EXPECT_EQ(mpz_class("375374217830"), computeDiscreteLog(p, g, h, std::pow(2, 20)));
}

TEST(DiscreteLogUnitTest, 3)
{
        mpz_class p("1073676287");
        mpz_class g("1010343267");
        mpz_class h("857348958");
        EXPECT_EQ(mpz_class("658308031"), computeLeftHandSide(p, computeInvertedG(p, g), h, 783));
	EXPECT_EQ(mpz_class("658308031"), computeRightHandSide(p, computeGRaisedToB(p, g, std::pow(2, 10)), 1002));
	EXPECT_EQ(mpz_class("1026831"), computeX(1002, std::pow(2, 10), 783));
}

TEST(DiscreteLogUnitTest, 4)
{
        mpz_class p("1073676287");
        mpz_class g("1010343267");
        mpz_class h("857348958");
        EXPECT_EQ(mpz_class("1026831"), computeDiscreteLog(p, g, h, std::pow(2, 10)));
}
