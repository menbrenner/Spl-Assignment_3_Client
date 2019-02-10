
#ifndef SP3_C_SIDE_SOCKETTHREAD_H
#define SP3_C_SIDE_SOCKETTHREAD_H

#include <condition_variable>
#include <mutex>
#include <queue>
#include "ConnectionHandler.h"
#include "BGUencdec.h"

class SocketThread {
private:
    std::condition_variable &condition_variable;
    std::mutex &waitTillAnswer;
    ConnectionHandler &myConnectionHandler;
    BGUencdec &myencdec;
    std::atomic<bool> &shouldTerminate;
    std::atomic<bool> &waitTillGetAnswer;

public:
    SocketThread(ConnectionHandler &connectionHandler , BGUencdec &encDec , std::mutex &wait,
            std::atomic<bool> &terminate , std::atomic<bool> &waitTillGetAnswer ,
            std::condition_variable &condition_variable);

    void operator()();


};


#endif //SP3_C_SIDE_SOCKETTHREAD_H
