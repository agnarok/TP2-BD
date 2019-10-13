#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "definitions.h"
#include "hashFile.h"

//./upload ../data/sample_small.csv

// para printar partes do csv.
// sed -n '2635p' entrada.csv | awk -F ';' '{print $3 $4}'
//  make all data=sample_small.csv

using namespace std;

class CsvReader {
 public:
  fstream fin;
  CsvReader(char const* fileName) { fin.open(fileName); }

  bool isAtEndOfFile() { return fin.peek() == EOF; }

  Line* getNextFormattedLine() {
    string word;
    getline(fin, word);
    stringstream s1(word);
    vector<string> lineIn;
    while (std::getline(s1, word, '"')) {
      // getline dessa forma le uma string vazia na primeira vez
      if (word[0] != ';' && word.size() != 0) {
        lineIn.push_back(word);
      } else {
        if (word[1] == 'N') {
          lineIn.push_back("NULL");
        }
      }
    }
    Line* out = new Line(stoi(lineIn[0]), lineIn[1], stoi(lineIn[2]), lineIn[3],
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
  Line* line;
  Block block;
  HashFile hash;
  while (!reader.isAtEndOfFile()) {
    line = reader.getNextFormattedLine();
    if (!hash.insertItem(*line)) {
      cout << endl << "n buto" << endl;
    }
    delete line;
    // cout << "linha: " << line->id << endl;
  }
  Line *pLine = hash.getLineFromBlock(2636);
  cout << endl << pLine->titulo << endl;
  hash.closeFile();
  return 0;
}
