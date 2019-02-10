
#include "../include/SocketThread.h"
SocketThread::SocketThread(ConnectionHandler &connectionHandler , BGUencdec &encDec ,
 std::mutex &wait, std::atomic<bool> &terminate , std::atomic<bool> &waitTillGetAnswer ,
  std::condition_variable &condition_variable)

        :condition_variable(condition_variable) , waitTillAnswer(wait) ,
         myConnectionHandler(connectionHandler), myencdec(encDec) , 
        shouldTerminate(terminate) , waitTillGetAnswer(waitTillGetAnswer){
}

void SocketThread::operator()() {
    while(!shouldTerminate) {
        std::string answer;
        // Get back an answer: by using the expected number of bytes (len bytes + newline delimiter)
        // We could also use: connectionHandler.getline(answer) and then get the answer without the newline char at the end
        if (!myConnectionHandler.getLine(answer)) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }
        std::cout << answer << std::endl;
        if (answer == "ACK 3 ") {
            shouldTerminate = true;
            std::lock_guard<std::mutex> guard(waitTillAnswer);
            waitTillGetAnswer = true;
            condition_variable.notify_all();//in order to wake the IoThread.
        }
        if (answer == "ERROR 3 ") {
            std::lock_guard<std::mutex> guard(waitTillAnswer);
            waitTillGetAnswer = true;
            condition_variable.notify_all();//in order to wake the IoThread.
        }
    }
    myConnectionHandler.close();
}
