
objects = $(patsubst %.c,%.o,$(wildcard *.c))
CC = gcc
CFLAGS = -g -Wall
TARGET = Msg_4G_client
$(TARGET):$(objects)
			$(CC) $(CFLAGS) -o $@ $^ -lsqlite3 -lpthread -ldl
clean:
		rm -rf *.o
		rm -rf cscope.*
