#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "definitions.h"
#include "hashFile.h"


// para printar partes do csv.
// sed -n '2635p' entrada.csv | awk -F ';' '{print $3 $4}'
// make all data=sample_small.csv

using namespace std;

class CsvReader {
 public:
  fstream fin;
  CsvReader(char const* fileName) { fin.open(fileName); }

  bool isAtEndOfFile() { return fin.peek() == EOF; }

  static bool checkNumberofAtt(string word) {
    stringstream* s1 = new stringstream(word);
    int x = 0;
    string aux;
    while (std::getline(*s1, aux, '"')) {
      x++;
    }
    if (x < 13) {
      delete s1;
      // cout << "X: " << x << endl;
      return false;
    }
    delete s1;
    return true;
  }

  Line* getNextFormattedLine() {
    string word;
    string nextWord;
    getline(fin, word);

    // Error checking routines. checkNumberofAtt checks 
    // the amount of attributes read from a line. If its too small,
    // it appends the next line. (This catches multi-line strings).
    if (!this->checkNumberofAtt(word)) {
      word.erase(word.size()-1);
      getline(fin, nextWord);
      // ate a linha de cima word e uma string nao valida se cair nessa if (nao termina)
      word.append(nextWord);
    }

    // input file uses CLRF as newlines. Why? :(
    if (word.at(word.size() - 1) == '\r') {
      word.erase(word.size() - 1);
    }
    // For NULL snippets.
    if (word.substr(word.size() - 4, 4) == "NULL") {
      word.erase(word.end() - 4, word.end());
      word.push_back(';');
    } else {
      word.push_back(';');
    }

    stringstream s1(word);
    vector<string> lineIn;
    string internal;
    while (std::getline(s1, word, '"')) {
      // cout << endl << "input " << word << endl;
      if (word != ";" && word.size() != 0 && word != ";;") {
        internal.append(word);
      } else if (word == ";") {
        lineIn.push_back(internal);
        // cout << "word " << internal << endl;
        internal = "";
      } else if (word == ";;") {
        lineIn.push_back(internal);
        // cout << "word " << internal << endl;
        lineIn.push_back("NULL");
        internal = "";
      }
    }
    // cout << endl;
    // cout << "teste0 " << lineIn[0] << endl;
    // cout << "teste1 " << lineIn[1] << endl;
    // cout << "teste2 " << lineIn[2] << endl;
    // cout << "teste3 " << lineIn[3] << endl;
    // cout << "teste4 " << lineIn[4] << endl;
    // cout << "teste5 " << lineIn[5] << endl;
    // cout << "teste6 " << lineIn[6] << endl;
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
  HashFile hash(true);
  int col;
  while (!reader.isAtEndOfFile()) {
    line = reader.getNextFormattedLine();
    if (!hash.insertItem(*line)) {
      // cout << endl << "n buto" << endl;
      col++;
    }
    delete line;
    // cout << "linha: " << line->id << endl;
  }
  cout << "numcol: " << col << endl;
  hash.closeFile();
  return 0;
}
