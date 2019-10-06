#include <iostream>

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
  Line(int id, char titulo[], int ano, char autores[], int citacoes,
       char atualiz[], char snippet[]) {
    this->id = id;
    this->ano = ano;
    this->citacoes = citacoes;
    memcpy(this->titulo,titulo,sizeof(titulo));
    memcpy(this->autores,autores,sizeof(autores));
    memcpy(this->atualiz,atualiz,sizeof(atualiz));
    memcpy(this->snippet,snippet,sizeof(snippet));
  }
};