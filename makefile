# My first makefile

all: printy
	./printy && rm -rf src/*.o printy
 
printy: src/upload.o src/Block.o
	g++ -o printy src/upload.o src/Block.o

uploadn: usrc/ploud.cpp Bsrc/lock.cpp
	g++ src/upload.cpp src/Block.cpp src/upload.cpp -o upload

Block.o: Block.cpp Block.h
	g++ -o Block.o src/Block.cpp -c -W -Wall -ansi -pedantic

clean:
	rm -rf src/*.o printy
