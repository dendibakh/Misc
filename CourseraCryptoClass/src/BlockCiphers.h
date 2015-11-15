#pragma once
#include <string>

namespace LibImplementation
{
	std::string encrypt_AES_CBC(const std::string& key, const std::string& iv, const std::string& plainText);
	std::string decrypt_AES_CBC(const std::string& key, const std::string& cipher);

	std::string encrypt_AES_CTR(const std::string& key, const std::string& iv, const std::string& plainText);
	std::string decrypt_AES_CTR(const std::string& key, const std::string& cipher);
}

namespace MyModesImplementation
{
	std::string encrypt_AES_CBC(const std::string& key, const std::string& iv, const std::string& plainText);
	std::string decrypt_AES_CBC(const std::string& key, const std::string& cipher);

	std::string encrypt_AES_CTR(const std::string& key, const std::string& iv, const std::string& plainText);
	std::string decrypt_AES_CTR(const std::string& key, const std::string& cipher);
}

