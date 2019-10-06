#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "Block.h"
#include "Line.h"

// #define LARGE_PRIME 6700417
#define LARGE_PRIME 5

using namespace std;

class CsvReader {
 public:
  fstream fin;
  CsvReader(char const* fileName) { fin.open(fileName); }

  bool isAtEndOfFile() { return fin.peek() == EOF; }

  Line getNextFormattedLine() {
    string line;
    string word;
    getline(fin, line);
    stringstream s1(line);
    vector<string> lineIn;
    while (std::getline(std::getline(s1, word, '"'), word, '"')) {
      lineIn.push_back(word);
    }
    Line out(stoi(lineIn[0]), lineIn[1], stoi(lineIn[2]), lineIn[3],
             stoi(lineIn[4]), lineIn[5], lineIn[6]);
    return out;
  }
};

// a funcao hash encontra o bucket que um dado registro está. O número do bucket
// pode ser multiplicado por um offset (bytes) para encontrar o inicio do
// bucket.
void createHashFile(const char* path) {
  FILE* file = fopen(path, "wb+");
  Block placeHolder;
  try {
    for (int i = 0; i < LARGE_PRIME; i++) {
      fwrite(&placeHolder, BLOCK_SIZE, 1, file);
    }
    fclose(file);
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
}

int calculateHash(int id) { return id % LARGE_PRIME; }

// o primeiro argumento de argv e o proprio arquivo
int main(int argc, char const* argv[]) {
  if (argc == 1) {
    cout << "No input file -- exiting." << endl;
    return 0;
  }
  CsvReader reader(argv[1]);
  Line line;

  createHashFile("../data/sample_file.hash");

  while (!reader.isAtEndOfFile()) {
    line = reader.getNextFormattedLine();
    cout << "linha: " << calculateHash(line.id) << endl;
  }
  
  return 0;
}