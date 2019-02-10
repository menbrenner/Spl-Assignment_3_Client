
#include "../include/IOThread.h"

IOThread::IOThread(ConnectionHandler &connectionHandler , BGUencdec &encDec , 
std::mutex &wait, std::atomic<bool> &terminate , 
std::atomic<bool> &waitTillGetAnswer , std::condition_variable &condition_variable)
        :  condition_variable(condition_variable) , waitTillAnswer(wait) ,
         myConnectionHandler(connectionHandler), myencdec(encDec) , 
        shouldTerminate(terminate) , waitTillGetAnswer(waitTillGetAnswer){
}



bool IOThread::getWaitTillGetAnswer() const {
    return waitTillGetAnswer;
}

void IOThread::operator()() {
    while (!shouldTerminate) {
        const short bufsize = 1024;
        char buf[bufsize];
        std::cin.getline(buf, bufsize);
        std::string line(buf);
        std::string lineToSend = myencdec.encode(line);
        if (!myConnectionHandler.sendLine(lineToSend)) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }
        if(line == "LOGOUT"){//need to wait and get answer from server in order to determine if should terminate or not.
            waitTillGetAnswer =false;
            std::unique_lock<std::mutex> mlock(waitTillAnswer);
            condition_variable.wait(mlock, std::bind(&IOThread::getWaitTillGetAnswer, this));
        }
    }

}
