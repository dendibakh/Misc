#include "StreamCipher.h"
#include "utils.h"

stringSet decrypt_StreamManyTimeKey(const stringSet& ciphers)
{
     size_t ciphers_size = ciphers.size();

     size_t maxLenght = 0;
     for (auto i : ciphers)
     {
          maxLenght = std::max(maxLenght, i.size());
     }

     std::vector<std::vector<size_t>> spaceMatrix(ciphers_size, std::vector<size_t>(maxLenght, 0));
     for (size_t i = 0; i < ciphers_size; ++i)
     {
         for (size_t j = 0; j < ciphers_size; ++j)
         {
             if (i != j)
             {
                 auto xorStr = XORstrings(ciphers[i], ciphers[j]); 
                 for (size_t k = 0; k < xorStr.size(); ++k)
                 {
                      if (isLetter(xorStr[k]))
                          spaceMatrix[i][k]++;
                 }
	     }
         }
     }

     /*
     for (auto i : spaceMatrix)
     {
         for (auto j : i)
         {
             std::cout << j << " ";              
         }
         std::cout << std::endl;
     }
     */

     std::string key(maxLenght, 0);
     std::vector<size_t> keyStrength(maxLenght, 0);
     for (size_t i = 0; i < ciphers_size; ++i)
     {
         for (size_t j = 0; j < maxLenght; ++j)
         {
             if (spaceMatrix[i][j] > 4)
             {
                 if (spaceMatrix[i][j] > keyStrength[j])
                 {
                     keyStrength[j] = spaceMatrix[i][j];
                     key[j] = '\x20' ^ ciphers[i][j];// space
                 }
             }
         }
     }
     
     //std::cout << key << std::endl;

     stringSet messages;
     for (auto i : ciphers)
     {
         messages.push_back(XORstrings(i, key));
     }

     return messages;
}
