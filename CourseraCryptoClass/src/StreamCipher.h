#pragma once
#include <vector>
#include <string>

typedef std::vector<std::string> stringSet;

stringSet decrypt_StreamManyTimeKey(const stringSet& ciphers);
