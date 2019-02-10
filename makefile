CFLAGS:=-c -Wall -g -std=c++11 -Iinclude
LDFLAGS:=-lboost_system

all: BGSclient
	g++ -pthread -o bin/BGSclient bin/ConnectionHandler.o bin/BGUencdec.o bin/IOThread.o bin/main.o bin/MessageObject.o bin/SocketThread.o bin/utils.o $(LDFLAGS) 
	
BGSclient: bin/ConnectionHandler.o bin/BGUencdec.o bin/IOThread.o bin/main.o bin/MessageObject.o bin/SocketThread.o bin/utils.o
	
bin/BGUencdec.o: src/BGUencdec.cpp
	g++ $(CFLAGS) -o bin/BGUencdec.o src/BGUencdec.cpp
	
bin/ConnectionHandler.o: src/ConnectionHandler.cpp
	g++ $(CFLAGS) -o bin/ConnectionHandler.o src/ConnectionHandler.cpp
	
bin/IOThread.o: src/IOThread.cpp
	g++ $(CFLAGS) -o bin/IOThread.o src/IOThread.cpp
	
bin/main.o: src/main.cpp
	g++ $(CFLAGS) -o bin/main.o src/main.cpp

bin/MessageObject.o: src/MessageObject.cpp
	g++ $(CFLAGS) -o bin/MessageObject.o src/MessageObject.cpp
	
bin/SocketThread.o: src/SocketThread.cpp
	g++ $(CFLAGS) -o bin/SocketThread.o src/SocketThread.cpp

	
bin/utils.o: src/utils.cpp
	g++ $(CFLAGS) -o bin/utils.o src/utils.cpp
	
.PHONY: clean
clean:
	rm -f bin/*
