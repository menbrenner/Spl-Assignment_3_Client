

#ifndef SPL3_CLIENT_UTILS_H
#define SPL3_CLIENT_UTILS_H

#include <vector>
#include <string>
#include <string>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
class utils{
public:
    static void shortToBytes(short num, char* bytesArr);
    static short bytesToShort(char* bytesArr);
    static void splitWordByspaces(std::vector<std::string> &words , const std::string &toSplit);
    static void addOpCodeToString(short opCode , std::string &message);
    static void addStringOpCodeToMessageString(std::string &decodedmessage , short &MessageOpcode , std::string &message);
};
#endif //SPL3_CLIENT_UTILS_H
