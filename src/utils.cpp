
#include "../include/utils.h"


	void utils::shortToBytes(short num, char* bytesArr)
	{
		bytesArr[0] = ((num >> 8) & 0xFF);
		bytesArr[1] = (num & 0xFF);
	}
	short utils::bytesToShort(char* bytesArr)
	{
		short result = (short)((bytesArr[0] & 0xff) << 8);
		result += (short)(bytesArr[1] & 0xff);
		return result;
	}
	void utils::splitWordByspaces(std::vector<std::string> &words , const std::string &toSplit){
		boost::split(words,toSplit,boost::is_any_of(" "));
}
	void utils::addStringOpCodeToMessageString(std::string &decodedmessage , short &MessageOpcode , std::string &message) {
		char myArray[decodedmessage.size()];
		int i= 0;
		for(char eachChar : decodedmessage){
		    myArray[i] = eachChar;
		    i++;
		}
		MessageOpcode = (utils::bytesToShort(myArray));
		message += std::to_string(MessageOpcode) + " ";
		decodedmessage.clear();
	}

	void utils::addOpCodeToString(short opCode , std::string &message){
		char opcodeArray[2];
		utils::shortToBytes(opCode ,opcodeArray);
		message += opcodeArray[0];
		message += opcodeArray[1];
}
