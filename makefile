all: upload
	./upload data/$(data) && rm -rf upload
# printy: src/upload.o src/Block.o
# 	g++ -o printy src/upload.o src/Block.o 
upload:
	g++ src/upload.cpp src/Block.cpp src/hashFile.cpp src/Line.cpp -o upload
# Block.o: Block.cpp Block.h
# 	g++ -o Block.o src/Block.cpp

btree:
	g++ src/B-tree/exemplo.cpp src/Line.cpp -o btree && ./btree && rm -rf btree


find: createFind
	./findrec $(id)

seek1: createSeek
	./seek1 $(id)

seek2: createSeek2
	./seek2 $(titu)

createSeek:
	g++ src/B-tree/seek1.cpp -o seek1

createSeek2:
	g++ src/B-tree/seek2.cpp -o seek2

createFind:
	g++ src/findrec.cpp src/Block.cpp src/hashFile.cpp src/Line.cpp -o findrec

clean:
	rm -rf src/*.o upload