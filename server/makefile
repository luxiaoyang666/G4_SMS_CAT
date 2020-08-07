
  
objects = $(patsubst %.c,%.o,$(wildcard *.c))
CC = gcc
CFLAGS = -g -Wall
TARGET = Msg_4G_server
$(TARGET):$(objects)
	$(CC) $(CFLAGS) -o $@ $^ -lsqlite3 -lcrypto -levent -lpthread -ldl
clean:
	rm -rf *.o
	rm -rf cscope.*
