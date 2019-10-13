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

// string problematic_arr[] = {"262150", "262299", "262299"};

// word
// word 262150
// word ;
// word
// word
// word two - 4 - six
// word
// word  - A Handheld Device for 3D-Presentations
// word ;
// word 2006
// word ;
// word Alexander Kulik|Bernd Fr&ouml;hlich|Roland Blach
// word ;
// word 9




// O ARQUIVO TA TERMINANDO EM CLRF, TROCAR PRA LF PORAAAAAAAAAAAA
class CsvReader {
 public:
  fstream fin;
  CsvReader(char const* fileName) { fin.open(fileName); }

  bool isAtEndOfFile() { return fin.peek() == EOF; }

  Line* getNextFormattedLine() {
    string word;
    getline(fin, word);

    // while (std::getline(std::getline(s1, word, '"'), word, ';')) {
    if(word.substr(word.size()-4,4) == "NULL") {
      // cout << "substr " << word.substr(word.size()-4,4) << endl;
      word.push_back('\"');
    }
    cout << word << endl;
    stringstream s1(word);
    vector<string> lineIn;
    string internal;
    while (std::getline(s1, word, '"')) {
      cout << word << endl;
      if (word != ";" && word.size() != 0) {
        internal.append(word);
      } else if (word == ";") {
        lineIn.push_back(internal);
        cout << "word " << internal << endl;
        internal = "";
      }
    }
    // problema no id 262150
    cout << endl;
    cout << "teste0 " << lineIn[0] << endl;
    cout << "teste1 " << lineIn[1] << endl;
    cout << "teste2 " << lineIn[2] << endl;
    cout << "teste4 " << lineIn[6] << endl;
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
  Line* pLine = hash.getLineFromBlock(2636);
  cout << endl << pLine->titulo << endl;
  hash.closeFile();
  return 0;
}
