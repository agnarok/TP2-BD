#include "Line.h"

using namespace std;

Line::Line(int id, string titulo, int ano, string autores, int citacoes,
           string atualiz, string snippet) {
  this->id = id;
  this->ano = ano;
  this->citacoes = citacoes;

  memcpy(this->titulo, titulo.c_str(), 300);
  memcpy(this->autores, autores.c_str(), 150);
  memcpy(this->atualiz, atualiz.c_str(), 50);
  memcpy(this->snippet, snippet.c_str(), 1024);
}

 void Line::print() {
  cout << "------------------\nline info: " << endl;
  cout << "id: " << this->id << endl;
  cout << "titulo: " << this->titulo << endl;
  cout << "Ano: " << this->ano << endl;
  cout << "autores: " << this->autores << endl;
  cout << "citacoes: " << this->citacoes << endl;
  cout << "atualização: " << this->atualiz << endl;
  cout << "snippet: " << this->snippet << endl;
}