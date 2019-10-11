# My first makefile

all: upload
	./upload data/sample_small.csv && rm -rf upload
# printy: src/upload.o src/Block.o
# 	g++ -o printy src/upload.o src/Block.o 
upload:
	g++ src/upload.cpp src/Block.cpp src/hashFile.cpp -o upload
# Block.o: Block.cpp Block.h
# 	g++ -o Block.o src/Block.cpp

clean:
	rm -rf src/*.o upload
