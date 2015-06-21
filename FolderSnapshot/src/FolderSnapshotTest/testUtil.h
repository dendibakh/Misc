#pragma once
#include <boost/filesystem.hpp>

struct CommonInserter : public std::iterator<std::output_iterator_tag, void, void, void, void>
{
                typedef std::vector<boost::filesystem::path> dirVector;

                explicit CommonInserter(dirVector& v) : vect(v)
                {}
                CommonInserter(const CommonInserter& rs) : vect(rs.vect)
                {}
                CommonInserter& operator= (const CommonInserter& rs)
                {
                                vect = rs.vect;
                                return *this;
                }
                CommonInserter& operator= (const boost::filesystem::path& p)
                {
                                vect.push_back(p);
                                return *this;
                }
                CommonInserter& operator++ ()
                {
                                return *this;
                }
                CommonInserter& operator* ()
                {
                                return *this;
                }
protected:
                dirVector& vect;
};

bool compareTwoFiles(const boost::filesystem::path& rhs, const boost::filesystem::path& lhs);
bool compareTwoDirectories(const boost::filesystem::path& rhs, const boost::filesystem::path& lhs);