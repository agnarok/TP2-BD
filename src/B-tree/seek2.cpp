#include <fstream>
#include <sstream>
#include <iostream>
#include "../definitions.h"
#include "secondary.h"

int main(int argc, char const* argv[]) {

  cout << argv[1] << endl;
  if (argc == 1) {
    cout << "No input file -- exiting." << endl;
    return 0;
  }

  fstream fin;
  fin.open("./data/sample_small.csv");

  char titulo[300];
  strcpy(titulo, argv[1]);
  int numBlocosLidos;
  int totalBlocos;
  ArvoreBSec<char[300]> arvore(2, SECONDARY_INDEX_PATH);
  unsigned long long int out = arvore.busca(titulo);
  cout << "resultado: " << out << endl;
  fin.seekg(out);
  
  string word;
  string wordOut;
  stringstream s1(word);
  getline(fin,wordOut);
  // do
  // {
  //   getline(fin, word);
  //   wordOut = word;
  //   // cout << "word " << word << endl;
  //   stringstream s1(word);  
  //   std::getline(std::getline(s1, word, '"'), word, '"');
  // } while (stoi(word) != id);

  cout << wordOut << endl;
  return 0;
}