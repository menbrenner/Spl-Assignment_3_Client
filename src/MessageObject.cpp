#include "../include/MessageObject.h"
#include <iostream>
#include "../include/MessageObject.h"

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;

 short MessageObject:: getOpCode() {
        return opCode;
    }

MessageObject::MessageObject() {
     message =u8"";
 }
MessageObject::~MessageObject() {
}
std::string MessageObject::getMessage() {
    return message;
}


int MessageObject::getLen() {
    return len;
}

std::string MessageObject::encode(std::string message) {
    MessageObject* encoder=nullptr;
    std::string first_token = message.substr(0, message.find(' '));
    if(first_token.compare("REGISTER")== 0){
        encoder = new RegisterMessage();
    }
    if(first_token.compare("LOGIN")== 0){
        encoder = new LoginMessage();
    }
    if(first_token.compare("LOGOUT")== 0){
        encoder = new LogoutMessage();
    }
    if(first_token.compare("FOLLOW")== 0){
        encoder = new FollowMessage();
    }
    if(first_token.compare("POST")== 0){
        encoder = new PostMessages();
    }
    if(first_token.compare("PM")== 0){
        encoder = new PmMessages();
    }
    if(first_token.compare("USERLIST")== 0){
        encoder = new UserListMessage();
    }
    if(first_token.compare("STAT")== 0){
        encoder = new StatMessage();
    }
    std::string ans = encoder->encodeTheRest(message.substr(message.find(' ')+1 , message.length()));//let messageObject finish parsing
    delete encoder;
    return ans;
}

std::string ErrorMessage::encodeTheRest(std::string toEncode) {
    return message;
}
std::string NotificationMessage::encodeTheRest(std::string toEncode) {
    return message;
}
std::string ACKMessage::encodeTheRest(std::string toEncode) {
    return message;
}
ACKMessage::ACKMessage():MessageObject() ,MessageOpcode(-1),numOfUsers(-1) , 
        numOfPosts(-1), numOfFollowers(-1),numOfFollowing(-1)
                         {
    message="ACK ";
}

bool ACKMessage::decode(char t) {
    if(MessageOpcode == -1) {//opcode not yet known
        decodedmessage += t;
        i++;
        if (decodedmessage.size() == 2) {//opcode known here
            utils::addStringOpCodeToMessageString(decodedmessage,MessageOpcode , message);
            i = 0;
            if (MessageOpcode != 8 && MessageOpcode != 4 && MessageOpcode != 7) {//most cases require no further action
                return true;
            }
        }
    }
    else {
        switch (MessageOpcode) {
            case 4:
            case 7: //follow and userlist
                if(i<2) {
                    decodedmessage += t;
                    i++;
                    if (i == 2) {//size of list is known now
                        utils::addStringOpCodeToMessageString(decodedmessage,numOfUsers , message);
                        i++;
                    }
                }else if (t != backSlashZero)//username character
                    message += t;
                else {
                    numOfUsers--;
                    if (numOfUsers == 0)
                        return true;
                    else
                        message += " ";
                }
                break;

            default: //case 8- stat
                decodedmessage += t;
                i++;
                if (i == 2 && numOfPosts == -1) {//Recovering data
                    utils::addStringOpCodeToMessageString(decodedmessage,numOfPosts , message);
                    i = 0;
                } else if (i == 2 && numOfFollowers == -1) {
                    utils::addStringOpCodeToMessageString(decodedmessage,numOfFollowers , message);
                    i = 0;
                } else if (i == 2 && numOfFollowing == -1) {
                    utils::addStringOpCodeToMessageString(decodedmessage,numOfFollowing , message);
                    i = 0;
                    return true;
                }
        }
    }
    return false;
}




ErrorMessage::ErrorMessage():MessageObject(),decodedmessage(){}

bool ErrorMessage:: decode(char t)  {
    decodedmessage += t;
    if(decodedmessage.size() == 2)//Opcode is known
    {
        message = "ERROR ";
        utils::addStringOpCodeToMessageString(decodedmessage,MessageOpcode , message);
        return true;
    }
    return false;
}

std::string FollowMessage::encodeTheRest(std::string toEncode) {
    utils::addOpCodeToString(FollowOp ,message);
    std::vector<std::string> words;
    utils::splitWordByspaces(words,toEncode);
    if(words[0] == "0"){ //first character to follow of unfollow
        message += '\0';
    }else{
        message += '\1';
    }
    short numtoFollow = std::stoi(words[1]);
    char numToFollowarray[2];
    utils::shortToBytes(numtoFollow,numToFollowarray);//bytes translation
    message +=numToFollowarray[0];
    message += numToFollowarray[1];
    for(unsigned int i = 2; i < words.size() ; i++ ){
        message += words[i];//add every name to the string
        message += backSlashZero;//add seperator
    }
    return message;
}

bool FollowMessage::decode(char t) {//virtual implementation
    return false;
 }

std::string LoginMessage::encodeTheRest(std::string toEncode) {
    utils::addOpCodeToString(LoginOp ,message);
    std::vector<std::string> words;
    utils::splitWordByspaces(words,toEncode);
    for(std::string eachWord : words){
        message += eachWord;//username and password+ seperator
        message += backSlashZero;
    }
    return message;
}

bool LoginMessage::decode(char t) {
    return false;
}


std::string LogoutMessage::encodeTheRest(std::string toEncode) {
    utils::addOpCodeToString(LogoutOp ,message);//write opcode only
    return message;
}
bool LogoutMessage::decode(char t) {
    return false;
}



NotificationMessage::NotificationMessage():MessageObject() , notificationType('d'),numOfZerosLeft(2),PostingUser(""),content("") {}

bool NotificationMessage::decode(char t){
     message = "NOTIFICATION ";
    if(notificationType=='d')//control character for initialization, for first decoding
        notificationType=t;
    else if(numOfZerosLeft==2)
        if(t!=backSlashZero)
            PostingUser+=t;
        else
            numOfZerosLeft--;
    else if(numOfZerosLeft==1){
        if(t!=backSlashZero)
            content+=t;
        else
        {
            numOfZerosLeft--;
            if(notificationType == '\1'){
                message += "Public ";
            }else{
                message += "PM ";

            }
            message +=  PostingUser+" "+content;
            return true;   
        }
    }
    return false;
}

std::string PmMessages::encodeTheRest(std::string toEncode) {
    utils::addOpCodeToString((short)PmOp ,message);
    std::string t = toEncode.substr(0, toEncode.find(' '));
    message +=t;//username
    message += backSlashZero;
    message += toEncode.substr(toEncode.find(' ')+1,toEncode.size());//content
    message += backSlashZero;
    return message;
}

bool PmMessages::decode(char t) {
    return false;
}


std::string PostMessages::encodeTheRest(std::string toEncode) {
    utils::addOpCodeToString(PostOp ,message);
    message += toEncode;
    message += backSlashZero;//end marker
    return message;
}


bool PostMessages::decode(char t) {
    return false;
}


bool RegisterMessage::decode(char t) {
    return false;
 }

std::string RegisterMessage::encodeTheRest(std::string toEncode) {
    utils::addOpCodeToString(RegisterOp ,message);
    std::vector<std::string> words;
    utils::splitWordByspaces(words,toEncode);
    for(std::string eachWord : words){//username and password
        message += eachWord;
        message += backSlashZero;
    }
    return message;
}


std::string StatMessage::encodeTheRest(std::string toEncode) {
    utils::addOpCodeToString(StatOp ,message);//opcode and username only
    message += toEncode;
    message += backSlashZero;
    return message;
}

bool StatMessage::decode(char t) {
    return false;
 }

std::string UserListMessage::encodeTheRest(std::string toEncode) {
    utils::addOpCodeToString(UserlistOp ,message);//opcode only
    return message;
}

bool UserListMessage::decode(char t) {
    return false;
 }

RegisterMessage::RegisterMessage() = default;
LoginMessage::LoginMessage() = default;
LogoutMessage::LogoutMessage() = default;
FollowMessage::FollowMessage() = default;
PostMessages::PostMessages() = default;
PmMessages::PmMessages() = default;
UserListMessage::UserListMessage() = default;
StatMessage::StatMessage() = default;
