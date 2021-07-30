CC = gcc 
SRC = $(wildcard ./*.c) $(wildcard ./**/*.c)

all: build run

build:
	$(CC) $(SRC) -o main.o -Wall -g -fsanitize=address -lz

run:
	./main.o 

debug: 
	gdb ./main.o