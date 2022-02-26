#ifndef __BASE64__
#define __BASE64__

#include <vector>
#include <string>
#include <stdexcept>

std::string Encode(std::vector<uint8_t> bytes);

std::vector<uint8_t> Decode(std::string str);

std::vector<char> kTable {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};

uint8_t getIndex(char ch) {
    if (ch >= 'A' && ch <= 'Z') return ch - 'A';
    else if (ch >= 'a' && ch <= 'z') return 26 + ch - 'a';
    else if (ch >= '0' && ch <= '9') return 52 + ch - '0';
    else if (ch == '+') return 62;
    else if (ch == '/') return 63;
    else if (ch == '=') return 0; // padding
    else throw std::runtime_error("invalid base64 char: " + std::to_string(ch));
}

std::string Encode(std::vector<uint8_t> bytes) {
    std::string ret;
    // 24 bits for a group
    int groupSize = bytes.size() / 3;
    // padding
    groupSize += bytes.size() % 3 == 0 ? 0 : 1;
    uint32_t buf = 0;
    for (int i = 0; i < groupSize; i++) {
        for (int j = 0; j < 3; j++) {
            if (3 * i + j < bytes.size()) {
                buf = buf | bytes[3 * i + j];
            }
            buf = buf << 8;
        }
        for (int j = 0; j < 4; j++) {
            if ((4 * i + j + 1) * 6 <= bytes.size() * 8) {
                ret.push_back(kTable[buf >> 26]);
            } else {
                ret.push_back('=');
            }
            buf = buf << 6;
        }
    }
    return ret;
}

std::vector<uint8_t> Decode(std::string str) {
    std::vector<uint8_t> ret;
    // 24 bits for a group
    int groupSize = str.length() / 4;
    // get unpadding length
    int unpaddingLen = str.length();
    while (str[unpaddingLen - 1] == '=') unpaddingLen--;
    // decode
    uint32_t buf = 0;
    for (int i = 0; i < groupSize; i++) {
        for (int j = 0; j < 4; j++) {
            buf = buf | getIndex(str[4 * i + j]);
            buf = buf << 6;
        }
        // left align
        buf = buf << 2;
        for (int j = 0; j < 3; j++) {
            if ((3 * i + j) * 8 < unpaddingLen * 6) {
                ret.push_back(0xff & (buf >> 24));
            }
            buf = buf << 8;
        }
    }
    return ret;
}

#endif
