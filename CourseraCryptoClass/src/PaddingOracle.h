#pragma once
#include <string>

enum ERROR_TYPE
{
    ERROR_TYPE_SUCCESS = 0,
    ERROR_TYPE_PADDING,
    ERROR_TYPE_MAC
};

ERROR_TYPE sendHTTPRequest(const std::string& str);
std::string decodeLastBlock(const std::string& response, const std::string& text);

