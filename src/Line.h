#include <iostream>
#include <cstring>

using namespace std;

// data esta como string, nao sei o melhor jeito.
class Line {
 public:
  int id, ano, citacoes;
  char titulo[300]; 
  char autores[150];
  char atualiz[50]; 
  char snippet[1024];
  void print();
  Line(){};
  Line(int id, string titulo, int ano, string autores, int citacoes,
       string atualiz, string snippet);
};