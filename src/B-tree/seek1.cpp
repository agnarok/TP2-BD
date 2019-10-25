#include <iostream>
#include "../definitions.h"
#include "btree.h"


int main(int argc, char const* argv[]) {
  if (argc == 1) {
    cout << "No input file -- exiting." << endl;
    return 0;
  }
  int id = stoi(argv[1]);
  int numBlocosLidos;
  int totalBlocos;
  ArvoreB<int> arvore(2,PRIMARY_INDEX_PATH);
  // Line* pLine = hash.getLineFromBlock(id, numBlocosLidos, totalBlocos);
  int out = arvore.busca(id);
  cout << "resultado: " << out << endl;
  // if (pLine == nullptr) {
  //   cout << endl << "nao existe" << endl;
  // } else {
  //   cout << "Número de blocos lidos: " << numBlocosLidos << endl;
  //   cout << "Número de blocos do arquivo de dados: " << totalBlocos << endl;
  //   pLine->print();
  // }
  // hash.closeFile();
  return 0;
}