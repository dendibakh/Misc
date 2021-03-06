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
     EXPECT_EQ("ABCD", convertFromHex("41424344"));
     EXPECT_EQ("EFGA", convertFromHex("45464741"));

     EXPECT_EQ("41424344", convertToHex(convertFromHex("41424344")));
     EXPECT_EQ("45464741", convertToHex(convertFromHex("45464741")));
}

TEST(StreamCipher, 4)
{
     EXPECT_TRUE(isLetter('\x42'));
     EXPECT_TRUE(isLetter('\x6B'));
     EXPECT_FALSE(isLetter('\x13'));
     EXPECT_FALSE(isLetter('\x3D'));
     EXPECT_FALSE(isLetter('\x7D'));
}

TEST(StreamCipher, 5)
{
    std::string file1 = readFileAsString("./test/6 - 1 - Introduction (11 min).mp4");
    EXPECT_EQ('\x00', file1[0]);
    EXPECT_EQ('\x00', file1[1]);
    EXPECT_EQ('\x00', file1[2]);
    EXPECT_EQ('\x20', file1[3]);
    EXPECT_EQ('\x69', file1[16]);
    EXPECT_EQ('\x31', file1[31]);
}