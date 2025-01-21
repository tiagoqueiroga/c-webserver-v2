CFLAGS=-Wall -Wextra -std=c11 -pedantic 

all: server

server: server.c
	$(CC) $(CFLAGS) -o build/server server.c
	
clean:
	rm -f build/*