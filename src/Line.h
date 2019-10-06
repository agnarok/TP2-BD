#include <iostream>

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