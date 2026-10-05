CC = gcc

CFLAGS = -Wall -Wextra -g -Iinclude

TARGET = bin/deadlockdoctor

SRC = src/main.c src/system.c src/process.c src/ipc.c
OBJ = $(SRC:src/%.c=obj/%.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f obj/*.o $(TARGET)

run: $(TARGET)
	./$(TARGET)
