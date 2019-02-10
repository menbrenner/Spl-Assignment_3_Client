
#ifndef SP3_C_SIDE_IOTHREAD_H
#define SP3_C_SIDE_IOTHREAD_H

#include <condition_variable>
#include <mutex>
#include <queue>
#include "../include/ConnectionHandler.h"
#include "BGUencdec.h"

class IOThread {
private:
        std::condition_variable &condition_variable;
        std::mutex &waitTillAnswer;
        ConnectionHandler &myConnectionHandler;
        BGUencdec &myencdec;
        std::atomic<bool> &shouldTerminate;
        std::atomic<bool> &waitTillGetAnswer;
public:
        IOThread(ConnectionHandler &connectionHandler , BGUencdec &encDec , std::mutex &wait,
                     std::atomic<bool> &terminate , std::atomic<bool> &waitTillGetAnswer ,
                     std::condition_variable &condition_variable);

        void operator()();
        bool getWaitTillGetAnswer() const ;


    };


#endif //SP3_C_SIDE_IOTHREAD_H
