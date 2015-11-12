#include "gtest/gtest.h"
#include "utils.h"

using namespace testing;

TEST(StreamCipher, 1)
{
     EXPECT_EQ("\x3", XORstrings("\x41", "\x42"));
     EXPECT_EQ("\x04\x04\x04\x0C", XORstrings("\x41\x42\x43\x44", "\x45\x46\x47\x48"));
     EXPECT_EQ("\x04\x04\x04", XORstrings("\x41\x42\x43\x44", "\x45\x46\x47"));
     EXPECT_EQ("\x04\x04\x04", XORstrings("\x41\x42\x43", "\x45\x46\x47\x48"));
     EXPECT_EQ("\x04\x04\x04\xD1", XORstrings("\x41\x42\x43\x99\x76\x50\xf2", "\x45\x46\x47\x48"));
}

TEST(StreamCipher, 2)
{
     EXPECT_EQ("ABCD", hex_to_string("41424344"));
     EXPECT_EQ("EFGA", hex_to_string("45464741"));
}

TEST(StreamCipher, 3)
{
     EXPECT_TRUE(isLetter('\x42'));
     EXPECT_TRUE(isLetter('\x6B'));
     EXPECT_FALSE(isLetter('\x13'));
     EXPECT_FALSE(isLetter('\x3D'));
     EXPECT_FALSE(isLetter('\x7D'));
}