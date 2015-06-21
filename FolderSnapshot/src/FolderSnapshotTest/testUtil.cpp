#include "stdafx.h"
#include "util.h"
#include "testUtil.h"
#include <fstream>

using namespace std;
using namespace boost::filesystem;

bool compareTwoFiles(const path& rhs, const path& lhs)
{
        ifstream rhs_f(rhs.string(), ifstream::binary);
        ifstream lhs_f(lhs.string(), ifstream::binary);

        if (!rhs_f || !lhs_f)
                return false;

        if (file_size(rhs) != file_size(lhs))
                return false;

        uintmax_t size = file_size(rhs);
        while (size > 0)
        {
                size_t piecelength = 0;
                if (size < OneHundredMegabytes)
                {
                        piecelength = static_cast<size_t>(size);
                        size = 0;
                }
                else
                {
                        piecelength = static_cast<size_t>(OneHundredMegabytes);
                        size -= OneHundredMegabytes;
                }

                std::string buffer_lhs, buffer_rhs;
                buffer_lhs.resize(piecelength);
                buffer_rhs.resize(piecelength);
                
                lhs_f.read(const_cast<char*>(buffer_lhs.data()), piecelength);
                if (!lhs_f.good())
                        throw domain_error("Error while reading left-hand-side file.");

                rhs_f.read(const_cast<char*>(buffer_rhs.data()), piecelength);
                if (!rhs_f.good())
                        throw domain_error("Error while reading right-hand-side file.");

                if (memcmp(buffer_lhs.data(), buffer_rhs.data(), piecelength))
                        return false;
        }

        rhs_f.close();
        lhs_f.close();

        return true;
}

bool compareTwoDirectories(const path& rhs, const path& lhs)
{
        typedef vector<path> dirVector;

        dirVector rhsVec;
        dirVector lhsVec;
        
        copy(directory_iterator(rhs), directory_iterator(), CommonInserter(rhsVec));
        copy(directory_iterator(lhs), directory_iterator(), CommonInserter(lhsVec));

        if (rhsVec.size() != lhsVec.size())
                return false;

        sort(rhsVec.begin(), rhsVec.end());
        sort(lhsVec.begin(), lhsVec.end());
        
        dirVector::const_iterator rhsIter(rhsVec.begin());
        dirVector::const_iterator lhsIter(lhsVec.begin());
        for (; rhsIter != rhsVec.end() && lhsIter != lhsVec.end(); ++lhsIter, ++rhsIter)
        {
                if (rhsIter->filename() != lhsIter->filename())
                        return false;

                if ( !( (is_directory(*rhsIter) && is_directory(*lhsIter) ) || (is_regular_file(*rhsIter) && is_regular_file(*lhsIter) ) ) )
                        return false;

                if ( is_directory(*rhsIter) && is_directory(*lhsIter) ) 
                        if (!compareTwoDirectories (*rhsIter, *lhsIter))
                                return false;
                        
                if ( is_regular_file(*rhsIter) && is_regular_file(*lhsIter) )
                        if (!compareTwoFiles(*rhsIter, *lhsIter))
                                return false;
        }
        return true;
}