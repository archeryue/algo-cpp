#ifndef __BASE64__
#define __BASE64__

#include <vector>
#include <string>

std::string Encode(std::vector<uint8_t> bytes);

std::vector<uint8_t> Decode(std::string str);

#endif
