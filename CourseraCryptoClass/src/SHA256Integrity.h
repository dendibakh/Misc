#pragma once
#include <string>

std::string computeFirstSHA256(const std::string& fileAsStr);
std::string injectSHA256Blocks(const std::string& fileAsStr);
std::string recoverSHA256InjectedFile(const std::string& fileAsStr);
