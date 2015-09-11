CC = g++
LIBEVENT = 
CFLAGS = -g
LIBS = -lpthread -levent

SERVER = chat-server
CLIENT = chat-client

all:$(SERVER) $(CLIENT)

$(SERVER):chat-server.cc
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(CLIENT):chat-client.cc
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean :
	rm -f chat-server chat-client
