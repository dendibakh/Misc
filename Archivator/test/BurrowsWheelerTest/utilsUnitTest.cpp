#include "gtest/gtest.h"

#include "utils.h"
#include <algorithm>

#include <iostream>

using namespace testing;

template <class T>
void checkTwoVectorsAreEqual(const T& lhs, const T& rhs)
{
     EXPECT_EQ(lhs.size(), rhs.size());
     EXPECT_TRUE(std::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

TEST(utilsUnitTest, test1)
{
     bool expectedArray[] = { 0, 1, 0, 0, 0, 0, 0, 1};
     std::vector<bool> expected(expectedArray, expectedArray + sizeof(expectedArray) / sizeof(expectedArray[0]));

     std::vector<bool> actual = getBinaryRepresentation(static_cast<unsigned char>('A'));
     checkTwoVectorsAreEqual(expected, actual);
}

TEST(utilsUnitTest, test2)
{
     bool expectedArray[] = { 0, 1, 0, 0, 1, 0, 0, 1 };
     std::vector<bool> expected(expectedArray, expectedArray + sizeof(expectedArray) / sizeof(expectedArray[0]));
     std::vector<bool> actual = getBinaryRepresentation(static_cast<unsigned char>('I'));
     checkTwoVectorsAreEqual(expected, actual);
}

TEST(utilsUnitTest, test3)
{
     bool binaryRepresentationArray[] = { 0, 1, 0, 0, 0, 0, 0, 1 };
     std::vector<bool> binaryRepresentation(binaryRepresentationArray, binaryRepresentationArray + sizeof(binaryRepresentationArray) / sizeof(binaryRepresentationArray[0]));
     EXPECT_EQ('A', getSymbolStrict(binaryRepresentation));
}

TEST(utilsUnitTest, test4)
{
     bool binaryRepresentationArray[] = { 0, 1, 0, 0, 1, 0, 0, 1 };
     std::vector<bool> binaryRepresentation(binaryRepresentationArray, binaryRepresentationArray + sizeof(binaryRepresentationArray) / sizeof(binaryRepresentationArray[0]));
     EXPECT_EQ('I', getSymbolStrict(binaryRepresentation));
}

TEST(utilsUnitTest, test5)
{
     bool binaryRepresentationArray[] = { 0, 1, 0, 0, 1, 0, 0 };
     std::vector<bool> binaryRepresentation(binaryRepresentationArray, binaryRepresentationArray + sizeof(binaryRepresentationArray) / sizeof(binaryRepresentationArray[0]));
     EXPECT_EQ('\0', getSymbolStrict(binaryRepresentation));
}

TEST(utilsUnitTest, test6)
{
     bool binaryRepresentationArray[] = { 0, 1, 0, 0, 1, 0, 0, 0, 0};
     std::vector<bool> binaryRepresentation(binaryRepresentationArray, binaryRepresentationArray + sizeof(binaryRepresentationArray) / sizeof(binaryRepresentationArray[0]));
     EXPECT_EQ('\0', getSymbolStrict(binaryRepresentation));
}

TEST(utilsUnitTest, test7)
{
     size_t value = 7u;
     std::vector<bool> binaryRepresentation(sizeof(value) * 8, 0);
     binaryRepresentation[5] = 1;
     binaryRepresentation[6] = 1;
     binaryRepresentation[7] = 1;
     checkTwoVectorsAreEqual(binaryRepresentation, getBinaryRepresentation(value));
}

TEST(utilsUnitTest, test8)
{
     size_t value = 0x20042020;
     std::vector<bool> binaryRepresentation(sizeof(value) * 8, 0);
     binaryRepresentation[2] = 1;
     binaryRepresentation[10] = 1;
     binaryRepresentation[21] = 1;
     binaryRepresentation[26] = 1;
     checkTwoVectorsAreEqual(binaryRepresentation, getBinaryRepresentation(value));
}

TEST(utilsUnitTest, test9)
{
     size_t value = 0x20042020;
     std::vector<bool> binaryRepresentation = getBinaryRepresentation(value);
     size_t expanded = getValue(binaryRepresentation);
     EXPECT_EQ(value, expanded);
}

TEST(utilsUnitTest, test10)
{
     size_t value = 0xDE17285F;
     std::vector<bool> binaryRepresentation = getBinaryRepresentation(value);
     size_t expanded = getValue(binaryRepresentation);
     EXPECT_EQ(value, expanded);
}

TEST(utilsUnitTest, test11)
{
     std::string fileContents = readFile("./test/BurrowsWheelerTest/samples/abbbaabbbbaccabbaaabc.txt");
     std::string etalon = "abbbaabbbbaccabbaaabc";
     EXPECT_EQ(etalon, fileContents);
}

TEST(utilsUnitTest, test12)
{
     std::string fileContents = readFile("./test/BurrowsWheelerTest/samples/nomatch.txt");
     std::string etalon = "abcdefg\nhijklmnopqrstuvw\nxyzABCDEFGHIJKLMNOPQRS\nTUVWXYZ1234567890!@#$%^&*()\n";
     EXPECT_EQ(etalon, fileContents);
}

TEST(utilsUnitTest, test13)
{
     bool binaryRepresentationArray[] = { 0, 1, 0, 0, 1 };
     std::vector<bool> binaryRepresentation(binaryRepresentationArray, binaryRepresentationArray + sizeof(binaryRepresentationArray) / sizeof(binaryRepresentationArray[0]));
     EXPECT_EQ(72, getSymbol(binaryRepresentation));
}

TEST(utilsUnitTest, test14)
{
     bool binaryRepresentationArray[] = { 0, 1, 0, 0, 1, 0, 0, 1 };
     std::vector<bool> binaryRepresentation(binaryRepresentationArray, binaryRepresentationArray + sizeof(binaryRepresentationArray) / sizeof(binaryRepresentationArray[0]));
     EXPECT_EQ('I', getSymbol(binaryRepresentation));
}

TEST(utilsUnitTest, test15)
{
     bool binaryRepresentationArray[] = { 1, 1, 1 };
     std::vector<bool> binaryRepresentation(binaryRepresentationArray, binaryRepresentationArray + sizeof(binaryRepresentationArray) / sizeof(binaryRepresentationArray[0]));
     EXPECT_EQ(static_cast<unsigned char>(-32), getSymbol(binaryRepresentation));
}

TEST(utilsUnitTest, test16)
{
     bool binaryRepresentationArray[] = { 1, 1, 1 };
     std::vector<bool> binaryRepresentation(binaryRepresentationArray, binaryRepresentationArray + sizeof(binaryRepresentationArray) / sizeof(binaryRepresentationArray[0]));
     std::string etalon;
     etalon += static_cast<char>(-32);
     EXPECT_EQ(etalon, convertToString(binaryRepresentation));
}

TEST(utilsUnitTest, test17)
{
     bool binaryRepresentationArray[] = { 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1 };
     std::vector<bool> binaryRepresentation(binaryRepresentationArray, binaryRepresentationArray + sizeof(binaryRepresentationArray) / sizeof(binaryRepresentationArray[0]));
     std::string etalon("IA");
     EXPECT_EQ(etalon, convertToString(binaryRepresentation));
}

TEST(utilsUnitTest, test18)
{
     bool binaryRepresentationArray[] = { 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1 };
     std::vector<bool> binaryRepresentation(binaryRepresentationArray, binaryRepresentationArray + sizeof(binaryRepresentationArray) / sizeof(binaryRepresentationArray[0]));
     std::string etalon("IA");
     etalon += static_cast<char>(-128);
     EXPECT_EQ(etalon, convertToString(binaryRepresentation));
}

TEST(utilsUnitTest, test19)
{
     bool binaryRepresentationArray[] = { 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1 };
     std::vector<bool> binaryRepresentation(binaryRepresentationArray, binaryRepresentationArray + sizeof(binaryRepresentationArray) / sizeof(binaryRepresentationArray[0]));
     std::string etalon("IA");
     etalon += static_cast<char>(-2);
     EXPECT_EQ(etalon, convertToString(binaryRepresentation));
}

TEST(utilsUnitTest, test20)
{
     std::vector<bool> binaryRepresentation;
     std::vector<bool> temp = getBinaryRepresentation(static_cast<unsigned char>('c'));
     binaryRepresentation.insert(binaryRepresentation.end(), temp.begin(), temp.end());
     temp = getBinaryRepresentation(static_cast<unsigned char>('+'));
     binaryRepresentation.insert(binaryRepresentation.end(), temp.begin(), temp.end());
     binaryRepresentation.insert(binaryRepresentation.end(), temp.begin(), temp.end());
     std::string etalon("c++");
     EXPECT_EQ(etalon, convertToString(binaryRepresentation));
}

TEST(utilsUnitTest, test21)
{
     std::string str("IA");
     str += static_cast<char>(-2);
     bool binaryRepresentationArray[] = { 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0 };
     std::vector<bool> etalon(binaryRepresentationArray, binaryRepresentationArray + sizeof(binaryRepresentationArray) / sizeof(binaryRepresentationArray[0]));
     EXPECT_EQ(etalon, convertToBoolVect(str));
}

TEST(utilsUnitTest, test22)
{
     std::string str("c++");
     std::vector<bool> etalon;
     std::vector<bool> temp = getBinaryRepresentation(static_cast<unsigned char>('c'));
     etalon.insert(etalon.end(), temp.begin(), temp.end());
     temp = getBinaryRepresentation(static_cast<unsigned char>('+'));
     etalon.insert(etalon.end(), temp.begin(), temp.end());
     etalon.insert(etalon.end(), temp.begin(), temp.end());
     EXPECT_EQ(etalon, convertToBoolVect(str));
}

TEST(utilsUnitTest, test23)
{
     bool binaryRepresentationArray[] = { 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0 };
     std::vector<bool> etalon(binaryRepresentationArray, binaryRepresentationArray + sizeof(binaryRepresentationArray) / sizeof(binaryRepresentationArray[0]));
     std::string str("IA");
     str += static_cast<char>(-128);
     EXPECT_EQ(etalon, convertToBoolVect(str));
}

TEST(utilsUnitTest, test24)
{
     bool binaryRepresentationArray[] = { 1, 1, 1, 0, 0, 0, 0, 0 };
     std::vector<bool> etalon(binaryRepresentationArray, binaryRepresentationArray + sizeof(binaryRepresentationArray) / sizeof(binaryRepresentationArray[0]));
     std::string str;
     str += static_cast<char>(-32);
     EXPECT_EQ(etalon, convertToBoolVect(str));
}

TEST(utilsUnitTest, test25)
{
     std::string str(readFile("./test/BurrowsWheelerTest/samples/abbbaabbbbaccabbaaabc.txt"));
     EXPECT_EQ(str, convertToString(convertToBoolVect(str)));
}

TEST(utilsUnitTest, test26)
{
     std::string str(readFile("./test/BurrowsWheelerTest/samples/nomatch.txt"));
     EXPECT_EQ(str, convertToString(convertToBoolVect(str)));
}
