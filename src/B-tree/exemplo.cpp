/* Programa de testes para a árvore B.
 *
 * Insere chaves repetidamente até que o usuário digite
 * uma chave sentinela.
 */

// Sentinela para a leitura
// Pré-condições: deve ter um tipo adequado para as chaves
// da árvore
#define SENTINELA '.'

// Ordem da árvore
#define ORDEM 2

#include <iostream>
#include "btree.h"
#include "../Line.h"
#include <fstream>
#include <sstream>
#include <vector>

using std::cout;
using std::cin;

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
    }
    word.push_back(';');

    stringstream s1(word);
    vector<string> lineIn;
    string internal;
    while (std::getline(s1, word, '"')) {
      if (word != ";" && word.size() != 0 && word != ";;") {
        internal.append(word);
      } else if (word == ";") {
        lineIn.push_back(internal);
        internal = "";
      } else if (word == ";;") {
        lineIn.push_back(internal);
        lineIn.push_back("NULL");
        internal = "";
      }
    }
    Line* out = new Line(stoi(lineIn[0]), lineIn[1], stoi(lineIn[2]), lineIn[3],
                         stoi(lineIn[4]), lineIn[5], lineIn[6]);

    return out;
  }
};

int main(int argc, char const* argv[]) 
{
	int c;
	ArvoreB<int> arvore(ORDEM, PRIMARY_INDEX_PATH);
	// CsvReader reader(argv[1]);
	// Line* line;
	// line = reader.getNextFormattedLine();
	// cout << line->id << endl; 
	int i = 0;
	while(i < 10) {
		cout << "\ninserir: " << i << endl;
		arvore.inserir(i);
		i ++;
	}
	cout << "Key test: " << arvore.raiz->chaves[0] << endl;
	
}
