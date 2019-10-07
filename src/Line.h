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
  Line(){};
  Line(int id, string titulo, int ano, string autores, int citacoes,
       string atualiz, string snippet) {
    this->id = id;
    this->ano = ano;
    this->citacoes = citacoes;

    memcpy(this->titulo,titulo.c_str(),300);
    memcpy(this->autores,autores.c_str(),150);
    memcpy(this->atualiz,atualiz.c_str(),50);
    memcpy(this->snippet,snippet.c_str(),1024);
  }
};