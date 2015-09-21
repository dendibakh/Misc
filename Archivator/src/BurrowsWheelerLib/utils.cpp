#include "utils.h"
#include <fstream>
#include <stdexcept>

std::vector<bool> getBinaryRepresentation(char symbol)
{
	std::vector<bool> retVect;
	for (short j = 7; j >= 0; --j)
	{
		bool currentBit = (symbol >> j) & 1;
		retVect.push_back(currentBit);
	}
	return retVect;
}

char getSymbolStrict(const std::vector<bool>& BinaryRepresentation)
{
	return getSymbolStrict(BinaryRepresentation.begin(), BinaryRepresentation.end());
}

char getSymbolStrict(const std::vector<bool>::const_iterator& BinaryRepresentation_begin, const std::vector<bool>::const_iterator& BinaryRepresentation_end)
{
	if (BinaryRepresentation_end - BinaryRepresentation_begin != 8)
		return 0;

	return getSymbol(BinaryRepresentation_begin, BinaryRepresentation_end);
}

char getSymbol(const std::vector<bool>& BinaryRepresentation)
{
	return getSymbol(BinaryRepresentation.begin(), BinaryRepresentation.end());
}

char getSymbol(const std::vector<bool>::const_iterator& BinaryRepresentation_begin, const std::vector<bool>::const_iterator& BinaryRepresentation_end)
{
	if (BinaryRepresentation_begin == BinaryRepresentation_end)
		return 0;

	char result = 0;
	for (short j = 0; j < BinaryRepresentation_end - BinaryRepresentation_begin; ++j)
	{
		result |= *(BinaryRepresentation_begin + j) << (7 - j);
	}
	return result;
}

std::vector<bool> getBinaryRepresentation(size_t value)
{
    std::vector<bool> binRep;
    for (size_t i = 0; i < sizeof(value); ++i)
    {
        char* c = (char*)&value + i;
        std::vector<bool> oneByte = getBinaryRepresentation(*c);
        binRep.insert(binRep.end(), oneByte.begin(), oneByte.end());
    }
    return binRep;
}

size_t getValue(const std::vector<bool>& BinaryRepresentation)
{
    return getValue(BinaryRepresentation.begin(), BinaryRepresentation.end());
}

size_t getValue(const std::vector<bool>::const_iterator& BinaryRepresentation_begin, const std::vector<bool>::const_iterator& BinaryRepresentation_end)
{
    if (BinaryRepresentation_begin == BinaryRepresentation_end)
    	return 0;
    if (BinaryRepresentation_end - BinaryRepresentation_begin != sizeof(size_t) * 8)
    	return 0;

    size_t OriginalStringRow = 0u;
    unsigned short bytes = sizeof(OriginalStringRow);
    for (size_t i = 0; i < bytes; ++i)
    {
        char* c = (char*)&OriginalStringRow + i;
        *c = getSymbol(BinaryRepresentation_begin + 8 * i, BinaryRepresentation_begin + 8 * (i + 1));
    }
    return OriginalStringRow;
}

std::string readFile(const std::string& fileName)
{
    std::ifstream file(fileName.c_str(), std::ifstream::in);
    if (!file.good())
        throw std::runtime_error("Can't open the file: " + fileName + ".");

    std::string fileContents;
    while(file.good() && !file.eof())
    {
        std::string str;
        std::getline(file, str);
        if (!str.empty())
            fileContents += str;
        if (!file.eof())
            fileContents += '\n';
    }
    return fileContents;
}

std::string convertToString(const std::vector<bool>& boolVect)
{
   size_t bytes = ( boolVect.size() - 1 ) / 8 + 1;
   std::string retStr(bytes, 0);

   std::vector<bool>::const_iterator BinaryRepresentation_begin = boolVect.begin();

   for (size_t i = 0; i < bytes; ++i)
   {
       std::vector<bool>::const_iterator begin = boolVect.begin() + 8 * i;
       std::vector<bool>::const_iterator end = boolVect.begin() + 8 * (i + 1);
       if (boolVect.end() - begin < 8)
           end = boolVect.end();
       retStr[i] = getSymbol(begin, end);
   }
   return retStr;
}
