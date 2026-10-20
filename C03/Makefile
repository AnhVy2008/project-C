CC = gcc
CFLAGS = -Wall -g

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
TARGET = quiz_app

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)