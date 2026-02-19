CC=gcc
TARGET=build/main

main: src/main.c
	$(CC) -fsanitize=address -Wall -Wextra -o0 -g -std=c11 -o $(TARGET) src/main.c

clean:
	rm build/main
