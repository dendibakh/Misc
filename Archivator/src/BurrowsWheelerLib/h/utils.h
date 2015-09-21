#pragma once

#include <vector>
#include <string>

std::vector<bool> getBinaryRepresentation(unsigned char symbol);
unsigned char getSymbol(const std::vector<bool>& BinaryRepresentation);
unsigned char getSymbol(const std::vector<bool>::const_iterator& BinaryRepresentation_begin, const std::vector<bool>::const_iterator& BinaryRepresentation_end);

unsigned char getSymbolStrict(const std::vector<bool>& BinaryRepresentation);
unsigned char getSymbolStrict(const std::vector<bool>::const_iterator& BinaryRepresentation_begin, const std::vector<bool>::const_iterator& BinaryRepresentation_end);

std::vector<bool> getBinaryRepresentation(size_t value);
size_t getValue(const std::vector<bool>& BinaryRepresentation);
size_t getValue(const std::vector<bool>::const_iterator& BinaryRepresentation_begin, const std::vector<bool>::const_iterator& BinaryRepresentation_end);

std::string readFile(const std::string& fileName);

std::string convertToString(const std::vector<bool>& boolVect);
std::vector<bool> convertToBoolVect(const std::string& str);
