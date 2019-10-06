#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

// #define LARGE_PRIME 6700417
#define LARGE_PRIME 5


using namespace std;

// data esta como string, nao sei o melhor jeito.
class Line {
 public:
  int id, ano, citacoes;
  string titulo, autores, atualiz, snippet;
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

// a funcao hash encontra o bucket que um dado registro está. O número do bucket pode ser multiplicado por um offset (bytes) para encontrar o inicio do bucket.
void createHashFile(const char *path) {
  FILE *file = fopen(path, "wb+");

  for (int i = 0; i < LARGE_PRIME; i++) {
    
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
  while (!reader.isAtEndOfFile()) {
    line = reader.getNextFormattedLine();
    cout << "linha: " << calculateHash(line.id) << endl;
  }
  return 0;
}
