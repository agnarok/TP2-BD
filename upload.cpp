#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

// data esta como string, nao sei o melhor jeito.
class Line {
 public:
  int id, ano, citacoes;
  string titulo, autores, atualiz,snippet;
  Line(){};
  Line(int id, string titulo, int ano, string autores, int citacoes,
       string atualiz, string snippet) {
    this->id = id;
    this->titulo = titulo;
    this->ano = ano;
    this->autores = autores;
    this->citacoes = citacoes;
    this->atualiz = atualiz;
    this->snippet = snippet;
  }
};

class CsvReader {
 public:
  CsvReader(char const* fileName) { fin.open(fileName); }
  fstream fin;

  Line getNextFormattedLine() {
    string line;
    string word;
    getline(fin, line);
    stringstream s1(line);
    vector<string> lineIn;
    while (std::getline(std::getline(s1,word,'"'), word, '"')) {
      lineIn.push_back(word);
    }
    Line out(stoi(lineIn[0]), lineIn[1], stoi(lineIn[2]), lineIn[3],
             stoi(lineIn[4]), lineIn[5], lineIn[6]);
    return out;
  }
};

// o primeiro argumento de argv e o proprio arquivo
int main(int argc, char const* argv[]) {
  if(argc == 1) {
    cout << "No input file -- exiting." << endl;
    return 0;
  }
  CsvReader reader(argv[1]);
  Line line = reader.getNextFormattedLine();
  line = reader.getNextFormattedLine();

  cout << "linha: " << line.id << endl;
  return 0;
}
