
#ifndef SPL3_CLIENT_BGUENCDEC_H
#define SPL3_CLIENT_BGUENCDEC_H


#include "MessageObject.h"
#include <string>
#include "../include/utils.h"
class BGUencdec {
public:
    std::string decodeNextByte(char nextByte);
    std::string encode(std::string message);
private:
    MessageObject* toDecode;
    bool finish;
    short opCodeLen = 0;
    char opcodeArray[2];
};


#endif //SPL3_CLIENT_BGUENCDEC_H
