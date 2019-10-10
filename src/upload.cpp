#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "definitions.h"
#include "hashFile.h"

//./upload ../data/sample_small.csv

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


// o primeiro argumento de argv e o proprio arquivo
int main(int argc, char const* argv[]) {
  cout << endl << argv[1] << endl;
  if (argc == 1) {
    cout << "No input file -- exiting." << endl;
    return 0;
  }
  CsvReader reader(argv[1]);
  Line line;
  Block block;
  HashFile hash;
  while (!reader.isAtEndOfFile()) {
    line = reader.getNextFormattedLine();
    if (!hash.insertItem(line)) {
      cout << endl << "n buto" << endl;
    }
    cout << "linha: " << line.id << endl;
  }
  Line *pLine = hash.getLineFromBlock(4);
  cout << endl << pLine->id << endl;

  return 0;
}
