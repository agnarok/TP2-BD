#include <fstream>
#include <sstream>
#include <iostream>
#include "../definitions.h"
#include "btree.h"

int main(int argc, char const* argv[]) {
  if (argc == 1) {
    cout << "No input file -- exiting." << endl;
    return 0;
  }

  fstream fin;
  fin.open("./data/entrada.csv");

  int id = stoi(argv[1]);
  int numBlocosLidos;
  int totalBlocos;
  ArvoreB<int> arvore(2, PRIMARY_INDEX_PATH);
  unsigned int out = arvore.busca(id);
  cout << "Número de blocos lidos: " <<  arvore.blockNums << endl;
  fin.seekg(out);
  
  string word;
  string wordOut;
  stringstream s1(word);
  getline(fin,wordOut);

  cout << wordOut << endl;
  return 0;
}