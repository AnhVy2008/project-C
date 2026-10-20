CC = gcc
CFLAGS = -Wall -g

# Tự động quét tất cả file .c trong thư mục B13
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
TARGET = vending_app

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)