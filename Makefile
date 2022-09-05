CC=g++
CFLAGS=-g -Wall -pthread -I . -I include/

server: src/server.cpp
	$(CC) $< -o bin/$@ $(CFLAGS)

client: src/client.cpp
	$(CC) $< -o bin/$@ $(CFLAGS)

clean: 
	$(RM) myprog
