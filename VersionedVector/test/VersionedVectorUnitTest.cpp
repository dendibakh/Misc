#include "gtest/gtest.h"
#include "VersionedVector.h"

using namespace testing;

namespace
{
    template <class T>
    void checkTwoVectorsAreEqual(const T& lhs, const T& rhs)
    {
         EXPECT_EQ(lhs.size(), rhs.size());
         EXPECT_TRUE(std::equal(lhs.begin(), lhs.end(), rhs.begin()));
    }
}

TEST(VersionedVector, 1)
{
    
}
