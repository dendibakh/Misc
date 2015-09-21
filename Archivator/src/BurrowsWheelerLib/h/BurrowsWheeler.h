#pragma once

#include "HuffmanCompression.h"
#include <boost/filesystem.hpp>

class BurrowsWheeler
{
public:
    typedef HuffmanAlgorithm::compressedResult compressedResult;

    BurrowsWheeler();
    virtual ~BurrowsWheeler();

    compressedResult encode(const std::string& text);
    std::string decode(const compressedResult& compressedText);
    void decode(const compressedResult& compressedText, std::string& result);
};

class BurrowsWheelerFile
{
public:
    BurrowsWheelerFile();
    virtual ~BurrowsWheelerFile();

    void encode(const boost::filesystem::path& fileName, const boost::filesystem::path& binaryName);
    void decode(const boost::filesystem::path& fileName, const boost::filesystem::path& binaryName);
};
