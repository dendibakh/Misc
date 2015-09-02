#pragma once

#include <list>
#include <vector>
#include <string>

class MoveToFront
{
public:
    typedef std::string encodedResult;
    typedef std::list<unsigned char> RadixArray;
    MoveToFront();

    static const unsigned char radix = 255;
    
    encodedResult encode(const std::string& input);
    std::string decode(const encodedResult& input);
    void decode(const encodedResult& input, std::string& result);
protected:
    static RadixArray radixArray;
};
