cmake_minimum_required(VERSION 3.12)
project(Client)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(include)
include_directories(src)
find_package(Boost COMPONENTS system filesystem thread REQUIRED)
IF (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
endif()

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -lboost_thread")
add_executable(Client
        include/BGUencdec.h
        include/ConnectionHandler.h
        include/IOThread.h
        include/MessageObject.h
        include/SocketThread.h
        include/utils.h
        src/BGUencdec.cpp
        src/ConnectionHandler.cpp
        src/IOThread.cpp
        src/main.cpp
        src/MessageObject.cpp
        src/SocketThread.cpp
        src/utils.cpp)


target_link_libraries(Client LINK_PUBLIC ${Boost_LIBRARIES} )