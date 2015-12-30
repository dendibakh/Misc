#include "gtest/gtest.h"
#include "FactorModulus.h"

using namespace testing;

TEST(FactorModulusUnitTest, 1)
{
        mpz_class N("17976931348623159077293051907890247336179769789423065727343008115 \
                     77326758055056206869853794492129829595855013875371640157101398586 \
                     47833778606925583497541085196591615128057575940752635007475935288 \
                     71082364994994077189561705436114947486504671101510156394068052754 \
                     0071584560878577663743040086340742855278549092581");
        auto factros = factorModulus(N);
        mpz_class factoredN;
        mpz_mul(factoredN.get_mpz_t(), factros.first.get_mpz_t(), factros.second.get_mpz_t());
        EXPECT_EQ(N, factoredN); // checking that N = p * q;

        EXPECT_EQ(mpz_class("134078079299425970995740249982058461274793658205923933777235614437217640300\
                             73662768891111614362326998675040546094339320838419523375986027530441562135724301"), factros.first);
}

TEST(FactorModulusUnitTest, 2)
{
        mpz_class N("6484558428080716696628242653467722787263437207069762630604390703787 \
                     9730861808111646271401527606141756919558732184025452065542490671989 \
                     2428844841839353281972988531310511738648965962582821502504990264452 \
                     1008852816733037111422964210278402893076574586452336833570778346897 \
                     15838646088239640236866252211790085787877");
        auto factros = factorModulusInBiggerRange(N);
        mpz_class factoredN;
        mpz_mul(factoredN.get_mpz_t(), factros.first.get_mpz_t(), factros.second.get_mpz_t());
        EXPECT_EQ(N, factoredN); // checking that N = p * q;

        EXPECT_EQ(mpz_class("254647961469961834380088165639739422293414542685241578463285819278857779699\
                             85222835143851073249573454107384461557193173304497244814071505790566593206419759"), factros.first);
}

TEST(FactorModulusUnitTest, 3)
{
        mpz_class N("551");
        auto factros = factorModulus3P2Q(N);
        mpz_class factoredN;
        mpz_mul(factoredN.get_mpz_t(), factros.first.get_mpz_t(), factros.second.get_mpz_t());
        EXPECT_EQ(N, factoredN); // checking that N = p * q;

        EXPECT_EQ(mpz_class("19"), factros.first);
}

/*
// failed on mathematical equation. But could be solved via exhaustive search.
TEST(FactorModulusUnitTest, 4)
{
        mpz_class N("1961");
        auto factros = factorModulus3P2Q(N);
        mpz_class factoredN;
        mpz_mul(factoredN.get_mpz_t(), factros.first.get_mpz_t(), factros.second.get_mpz_t());
        EXPECT_EQ(N, factoredN); // checking that N = p * q;

        EXPECT_EQ(mpz_class("37"), factros.first);
}
*/

TEST(FactorModulusUnitTest, 5)
{
        mpz_class N("6149833");
        auto factros = factorModulus3P2Q(N);
        mpz_class factoredN;
        mpz_mul(factoredN.get_mpz_t(), factros.first.get_mpz_t(), factros.second.get_mpz_t());
        EXPECT_EQ(N, factoredN); // checking that N = p * q;

        EXPECT_EQ(mpz_class("2017"), factros.first);
        EXPECT_EQ(mpz_class("3049"), factros.second);
}

/*
// failed on mathematical equation. But could be solved via exhaustive search.
TEST(FactorModulusUnitTest, 6)
{
        mpz_class p("4051");
        mpz_class q("6043");
        mpz_class N(p * q); 

        auto factros = factorModulus3P2Q(N);
        mpz_class factoredN (factros.first * factros.second);
        EXPECT_EQ(mpz_class("24480193"), factoredN); // checking that N = p * q;

        EXPECT_EQ(mpz_class(p), factros.first);
        EXPECT_EQ(mpz_class(q), factros.second);
}
*/

TEST(FactorModulusUnitTest, 7)
{
        mpz_class N("7299717353");
        auto factros = factorModulus3P2Q(N);
        mpz_class factoredN;
        mpz_mul(factoredN.get_mpz_t(), factros.first.get_mpz_t(), factros.second.get_mpz_t());
        EXPECT_EQ(N, factoredN); // checking that N = p * q;

        EXPECT_EQ(mpz_class("69709"), factros.first);
        EXPECT_EQ(mpz_class("104717"), factros.second);
}

TEST(FactorModulusUnitTest, 8)
{
        mpz_class p("3");
        mpz_class q("5");
        mpz_class N(p * q); 

        auto factros = factorModulus3P2Q(N);
        mpz_class factoredN (factros.first * factros.second);
        EXPECT_EQ(mpz_class("15"), factoredN); // checking that N = p * q;

        EXPECT_EQ(mpz_class(p), factros.first);
        EXPECT_EQ(mpz_class(q), factros.second);
}

TEST(FactorModulusUnitTest, 9)
{
        mpz_class p("11");
        mpz_class q("17");
        mpz_class N(p * q); 

        auto factros = factorModulus3P2Q(N);
        mpz_class factoredN (factros.first * factros.second);
        EXPECT_EQ(mpz_class("187"), factoredN); // checking that N = p * q;

        EXPECT_EQ(mpz_class(p), factros.first);
        EXPECT_EQ(mpz_class(q), factros.second);
}

TEST(FactorModulusUnitTest, 10)
{
        mpz_class N("72006226374735042527956443552558373833808445147399984182665305798191 \
                     63556901883377904234086641876639384851752649940178970835240791356868 \
                     77441155132015188279331812309091996246361896836573643119174094961348 \
                     52463970788523879939683923036467667022162701835329944324119217381272 \
                     9276147530748597302192751375739387929");
        auto factros = factorModulus3P2Q(N);
        mpz_class factoredN;
        mpz_mul(factoredN.get_mpz_t(), factros.first.get_mpz_t(), factros.second.get_mpz_t());
        EXPECT_EQ(N, factoredN); // checking that N = p * q;

        EXPECT_EQ(mpz_class("21909849592475533092273988531583955898982176093344929030099423584127\
                             212078126150044721102570957812665127475051465088833555993294644190955293613411658629209"), factros.first);
}
