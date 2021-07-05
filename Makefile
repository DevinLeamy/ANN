CC = gcc 
SRC = $(wildcard ./*.c)

all: build run

build:
	$(CC) $(SRC) -o main.o -Wall -g -fsanitize=address

run:
	./main.o 

debug: 
	gdb ./main.o