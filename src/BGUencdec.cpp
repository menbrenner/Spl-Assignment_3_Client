
#include "../include/BGUencdec.h"



std::string BGUencdec::encode(std::string message) {
    return MessageObject::encode(message);
}

std::string BGUencdec::decodeNextByte(char nextByte) {
    if(opCodeLen<2) {
        opcodeArray[opCodeLen] = nextByte;
        opCodeLen++;
        if (opCodeLen == 2) {//Message type is known create messageObject
            short opCode = utils::bytesToShort(opcodeArray);
            switch (opCode) {
                case 9:
                    toDecode = new NotificationMessage();
                    break;
                case 10:
                    toDecode = new ACKMessage();
                    break;
                case 11:
                    toDecode = new ErrorMessage();
                    break;
                default://should not reach here, illegal input
                    break;
            }
        }
        return "";//return empty string if decoding should continue
    }else{ //if Opcode is known, proceed decoding
        finish = toDecode->decode(nextByte);//boolean representing whether decoding is finished
        if(finish){
            this->opCodeLen = 0;
            this->finish = false;
            std::string answer = toDecode->getMessage();
            delete toDecode;
            return answer;
        }
        return ""; //return empty string if decoding should continue
    }
}
