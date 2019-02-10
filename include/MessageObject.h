
#ifndef MESSAGEOBJECT_H
#define MESSAGEOBJECT_H
#include <sstream>
#include <iostream>
#include <boost/algorithm/string/classification.hpp> // Include boost::for is_any_of
#include <boost/algorithm/string/split.hpp> // Include for boost::split
#include <vector>
#include <string>
#include <cstring>
#include "utils.h"

class MessageObject{

public:
    MessageObject();
    short getOpCode();
    std::string getMessage();
    int getLen();
    virtual bool decode (char t)=0;
    virtual ~MessageObject();
    static std::string encode (std::string toEncode);
    virtual std::string encodeTheRest (std::string toEncode) =0;
protected:
    std::string decodedmessage;
    short opCode;
    std::string message;
    int len = 0;
    static const short RegisterOp = 1;
    static const short LoginOp = 2;
    static const short LogoutOp = 3;
    static const short FollowOp = 4;
    static const short PostOp = 5;
    static const short PmOp = 6;
    static const short UserlistOp = 7;
    static const short StatOp = 8;
    static const short NotificationOp = 9;
    static const short AckOp = 10;
    static const short ErrorOp = 11;
    static const char backSlashZero = '\0';
private:
    short t;
};


class ACKMessage : public MessageObject{
public:
    ACKMessage();
    std::string encodeTheRest (std::string toEncode);
    bool decode(char t);
private:
    short MessageOpcode;
    short numOfUsers;
    short numOfPosts;
    short numOfFollowers;
    short numOfFollowing;
    short i=0;
};

class ErrorMessage : public MessageObject{
public:
    ErrorMessage();
    std::string encodeTheRest (std::string toEncode);
    bool decode(char t);
private:
    std::string decodedmessage;
    short MessageOpcode;
};

class FollowMessage : public MessageObject{
public:
    FollowMessage();
    std::string encodeTheRest (std::string toEncode);
    bool decode (char t);
private:
};

class LoginMessage : public MessageObject{
public:
    LoginMessage();
    std::string encodeTheRest (std::string toEncode);
    bool decode (char t);
private:
};

class LogoutMessage : public MessageObject{
public:
    LogoutMessage();
    std::string encodeTheRest (std::string toEncode);
    bool decode (char t);
};

class NotificationMessage: public MessageObject {
public:
    NotificationMessage();
    bool decode(char t);
    std::string encodeTheRest (std::string toEncode);
private:
    char notificationType;
    int numOfZerosLeft;
    std::string PostingUser;
    std::string content;
};

class PmMessages: public MessageObject {
public:
    PmMessages();
    std::string encodeTheRest (std::string toEncode);
    bool decode (char t);

private:
};


class PostMessages: public MessageObject {
public:
    PostMessages();
    std::string encodeTheRest (std::string toEncode);
    bool decode(char t) ;
private:
};

class RegisterMessage : public MessageObject {
public:
    RegisterMessage();
    std::string encodeTheRest (std::string toEncode);
    bool decode (char t);

private:
};

class StatMessage: public MessageObject {
public:
    StatMessage();
    std::string encodeTheRest (std::string toEncode);
    bool decode (char t);

private:
};

class UserListMessage : public MessageObject {
public:
    UserListMessage();
    std::string encodeTheRest (std::string toEncode);
    bool decode (char t);
};



#endif
