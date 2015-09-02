#include "BurrowsWheeler.h"
#include "BurrowsWheelerTransform.h"
#include "MoveToFront.h"
#include "utils.h"

BurrowsWheeler::BurrowsWheeler()
{

}

BurrowsWheeler::~BurrowsWheeler()
{

}

BurrowsWheeler::compressedResult BurrowsWheeler::encode(const std::string& text)
{
    BurrowsWheelerTransform bwTransform(text);
    MoveToFront::encodedResult encodedStr = MoveToFront().encode(bwTransform.getTransformedStr());
    BurrowsWheeler::compressedResult compressed = HuffmanAlgorithm().getCompressedResult(encodedStr);
    
    std::vector<bool> originalStringRow = getBinaryRepresentation(bwTransform.getOriginalStringRow());
    compressed.insert(compressed.begin(), originalStringRow.begin(), originalStringRow.end());
    return compressed;
}

void BurrowsWheeler::decode(const compressedResult& compressedText, std::string& result)
{
    size_t OriginalStringRow = getValue(compressedText.begin(), compressedText.begin() + 8 * sizeof(size_t));
    
    std::string expanded;
    HuffmanAlgorithm().getExpandedResult(compressedText.begin() + 8 * sizeof(size_t), compressedText.end(), expanded);
    std::string decoded;
    MoveToFront().decode(expanded, decoded);
    BurrowsWheelerDecode bwDecode(OriginalStringRow, decoded, result);
}

std::string BurrowsWheeler::decode(const compressedResult& compressedText)
{
    std::string result;
    decode(compressedText, result);
    return result;
}
