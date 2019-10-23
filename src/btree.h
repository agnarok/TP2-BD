/* Estrutura de dados para árvores B
 *
 * Utiliza templates para guardar tipos arbitrários de
 * chaves. Inclui funções de caminhamento e desenho com duas
 * versões: a versão pública não recebe argumentos. A versão
 * privada recebe a raiz da sub-árvore para a implementação
 * recursiva dos algoritmos.
 */

#pragma once

#include <cassert>
#include <iostream>
#include <cstdio>

template<typename T>
class ArvoreB;


// Declaração de um nó de árvore B contendo chaves e filhos
// privados. 
// A manipulação terá que ocorrer por conta da
// classe ArvoreB.
template<typename T>
class NoB {
public:
    void imprimir_no() {
        using std::cout;
        cout << "(" << num_chaves << ")";
        for (int i = 0; i < num_chaves; i++) {
            cout << " " << chaves[i];
        }
        if (folha) {
            cout << " [f]";
        }
        cout << "\n";
    }
private:
    friend class ArvoreB<T>;
    T *chaves;
    NoB **filhos;

    int num_chaves;
    bool folha;
};


// Declaração da classe para árvores B
template<typename T>
class ArvoreB {
public:
    ArvoreB(int ordem);

    void inserir(const T &chave);
    
    // Desenha a árvore
    void desenhar() {
        desenhar(raiz, 0);
    }
private:
    NoB<T> *raiz;
    int ordem;
    int max_chaves;

    void inserir(NoB<T> *no, NoB<T> *pai, const T &chave);

    void dividir_no(NoB<T> *no, NoB<T> *pai);

    int buscar_chave_maior(NoB<T> *no, const T &chave);

    void deslocar_chaves(NoB<T> *no, int pos);

    NoB<T> *criar_no(bool folha);

    void desenhar(NoB<T> *raiz, int nivel);
};


// Faz o desenho da árvore (arranjei por causa da monitoria hehehehe é top)
template<typename T>
void ArvoreB<T>::desenhar(NoB<T> *raiz, int nivel)
{
    // Insere espaços antes do nó
    printf("%*s", nivel * 4, "");

    // Desenha o nó
    raiz->imprimir_no();

    // Se não for uma folha, então chama recursivamente para
    // desenhar os filhos
    if (!raiz->folha) {
        for (int i = 0; i <= raiz->num_chaves; i++) {
            desenhar(raiz->filhos[i], nivel + 1);
        }
    }
}


// Função auxiliar para encontrar a posição da primeira
// chave maior ou igual a uma chave de referência; usada
// para achar a posição na qual uma nova chave deve ser
// inserida
template<typename T>
int ArvoreB<T>::buscar_chave_maior(NoB<T> *no,
        const T &chave)
{
    int pos = 0;
    while (pos < no->num_chaves &&
            no->chaves[pos] < chave) {
        pos++;
    }
    return pos;
}


// Função auxiliar: move todas as chaves a partir de uma
// certa posiçao, juntamente com seus ponteiros direitos,
// criando espaço para inserir novas chaves
template<typename T>
void ArvoreB<T>::deslocar_chaves(NoB<T> *no, int pos)
{
    int j = no->num_chaves;
    while (j > pos) {
        no->chaves[j] = no->chaves[j - 1];
        no->filhos[j + 1] = no->filhos[j];
        j--;
    }
}


// Função chamada pelo usuário para inserção
template<typename T>
void ArvoreB<T>::inserir(const T &chave)
{
    // Se a raiz está nula, então cria um novo nó folha
    if (raiz == NULL) {
        raiz = criar_no(true);
    }

    inserir(raiz, NULL, chave);
}


// Versão sobrecarregada com argumentos da inserção em
// árvore: privada, não pode ser utilizada pelo usuário
template<typename T>
void ArvoreB<T>::inserir(NoB<T> *no, NoB<T> *pai,
        const T &chave)
{

    int pos = buscar_chave_maior(no, chave);

    if (no->folha) {
        deslocar_chaves(no, pos);
        no->chaves[pos] = chave;
        no->num_chaves++;
    }
    else {
        inserir(no->filhos[pos], no, chave);
    }

    if (no->num_chaves > max_chaves) {
        dividir_no(no, pai);
    }
}


// Faz divisão de um nó (copiado na tora falo mermo)
template<typename T>
void ArvoreB<T>::dividir_no(NoB<T> *no, NoB<T> *pai)
{
    int i, j;
    int meio = no->num_chaves / 2;

    if (pai == NULL) {
        // Cria um novo nó não folha
        pai = criar_no(false);

        raiz = pai;
        raiz->filhos[0] = no;
    }

    NoB<T> *novo = criar_no(no->folha);
    
    for (i = meio + 1, j = 0; i < no->num_chaves; i++, j++) {
        novo->chaves[j] = no->chaves[i];
        novo->filhos[j] = no->filhos[i];
    }

    novo->filhos[j] = no->filhos[i];

    // Aqui sera feita a alteração para transformar em Arvore B+
    for (int i = meio + 1; i <= no->num_chaves; i++) {
        no->filhos[i] = NULL;
    }

    const T &promovida = no->chaves[meio];

    int pos = buscar_chave_maior(pai, promovida);

    deslocar_chaves(pai, pos);


    pai->chaves[pos] = promovida;
    pai->filhos[pos + 1] = novo;


    novo->num_chaves = no->num_chaves - meio - 1;
    no->num_chaves = meio;
    pai->num_chaves++;
}


template<typename T>
ArvoreB<T>::ArvoreB(int ordem)
{
    assert(ordem > 1);
    this->ordem = ordem;
    this->raiz = NULL;
    this->max_chaves = 2 * ordem - 1;
}


// Cria um novo nó folha vazio
template<typename T>
NoB<T> *ArvoreB<T>::criar_no(bool folha)
{
    NoB<T> *novo = new NoB<T>;

    novo->chaves = new T[max_chaves + 1];
    novo->filhos = new NoB<T>*[max_chaves + 2];
    
    for (int i = 0; i <= max_chaves + 1; i++) {
        novo->filhos[i] = NULL;
    }

    novo->num_chaves = 0;
    novo->folha = folha;

    return novo;
}
