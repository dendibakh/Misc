#pragma once
#include <fstream>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <boost/filesystem.hpp>
#include <iterator>
#include <limits>

const char FLAG_FILE = 0;
const char FLAG_FOLDER = 1;

const char FLAG_END_FOLDER = 101;

const uintmax_t OneHundredMegabytes = 100 * 1024 * 1024;

const int MAX_DEPTH = std::numeric_limits<int>::max();

struct SeparateInserter : public std::iterator<std::output_iterator_tag, void, void, void, void>
{
        typedef std::vector<boost::filesystem::path> pathVector;

        explicit SeparateInserter(pathVector& dVect, pathVector& fVect) : dirvect(dVect), filevect(fVect)
        {}
        SeparateInserter(const SeparateInserter& rhs) : dirvect(rhs.dirvect), filevect(rhs.filevect)
        {}
        SeparateInserter& operator= (const SeparateInserter& rhs)
        {
                dirvect = rhs.dirvect;
                filevect = rhs.filevect;
                return *this;
        }
        SeparateInserter& operator= (const boost::filesystem::path& p)
        {
                if (is_directory(p))
                        dirvect.push_back(p);
                else if (is_regular_file(p))
                        filevect.push_back(p);
                return *this;
        }
        SeparateInserter& operator++ ()
        {
                return *this;
        }
        SeparateInserter& operator* ()
        {
                return *this;
        }
private:
        pathVector& dirvect;
        pathVector& filevect;
};

void storeFileContent(std::ifstream& source, std::ofstream& destination, uintmax_t size);
char getFlagFromBinary(std::ifstream& binary);
boost::filesystem::path removeLastSlash(const boost::filesystem::path& path);