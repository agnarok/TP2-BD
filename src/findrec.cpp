#include <iostream>
#include "definitions.h"
#include "hashFile.h"

// 1.549.146 registros
// testar para id 500000
int main(int argc, char const* argv[]) {
  if (argc == 1) {
    cout << "No input file -- exiting." << endl;
    return 0;
  }
  int id = stoi(argv[1]);
  int numBlocosLidos;
  int totalBlocos;
  HashFile hash(false);
  Line* pLine = hash.getLineFromBlock(id, numBlocosLidos, totalBlocos);
  if (pLine == nullptr) {
    cout << endl << "nao existe" << endl;
  } else {
    cout << "Número de blocos lidos: " << numBlocosLidos << endl;
    cout << "Número de blocos do arquivo de dados: " << totalBlocos << endl;
    pLine->print();
  }
  hash.closeFile();
  return 0;
}