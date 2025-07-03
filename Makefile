flags=-O2 -Wall -std=c23


.PHONY: clean

all: clean allocater

allocater: allocater.o heap.o
	cc $(flags) $^ -o $@ 

allocater.o: allocater.c allocater.h
	cc $(flags) -c $<

heap.o: heap.asm
	nasm -f elf64 $<

clean: 
	rm -f *.o allocater