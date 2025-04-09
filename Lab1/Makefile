CC = gcc
CFLAGS = -Iinclude -Wall -Wextra

CFLAGS += -Isrc

SRC = ./src/main.c \
	  ./include/cmd.h
OBJ = $(SRC:.c=.o)
TARGET = ./bin/main

all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p $(dir $(TARGET))
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run: all
	@$(TARGET)

.PHONY: all clean run
