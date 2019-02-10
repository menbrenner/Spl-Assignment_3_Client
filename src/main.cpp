#include <iostream>
#include <thread>
#include "../include/SocketThread.h"
#include "../include/IOThread.h"
#include "../include/ConnectionHandler.h"

using namespace std;

int main(int argc, char** argv){

    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " host port" << std::endl << std::endl;
        return -1;
    }
    std::string host = argv[1];
    short port = atoi(argv[2]);
    BGUencdec myEncDec;
    ConnectionHandler handler(host, port , myEncDec);
    handler.connect();
    std::mutex waitTillGetAnswerLock;
    //wait till get ans
    std::atomic<bool> terminate (false);
    std::atomic<bool> waitTillGetAnswer (true);
    std::condition_variable condition_variable;
    IOThread ioThread(handler, myEncDec , waitTillGetAnswerLock , terminate , waitTillGetAnswer , condition_variable);
    SocketThread SocketThread(handler, myEncDec  , waitTillGetAnswerLock  , terminate , waitTillGetAnswer , condition_variable);

    std::thread threadofTheIo(ioThread);
    std::thread ThreadOfTheSocket(SocketThread);

//wait here until termination
    threadofTheIo.join();
    ThreadOfTheSocket.join();
    return 0;
}
