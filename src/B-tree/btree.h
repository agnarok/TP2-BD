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
#include "../definitions.h"
using namespace std;

template<typename T>
class ArvoreB;

// USAR -1 NO VETOR DE OFFSETS PARA INDICAR NULL
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
public:
    // verificar tamanho do no depois
    friend class ArvoreB<T>;

    // array of block offset integers
    unsigned int diskOffset;
    int num_chaves;
    unsigned long long int filhos[PRIMARY_ORDER_MAIN+2];
    T chaves[PRIMARY_ORDER_MAIN+1];
    bool folha;

    // filling so fwrite can read 4096 bytes
     char dump[PRIMARY_INDEX_DUMP];
};


// Declaração da classe para árvores B
template<typename T>
class ArvoreB {
public:
    ArvoreB(int ordem, string filename);

    void inserir(const T &chave, unsigned long long int dataOffset);
    
    // Desenha a árvore
    void desenhar() {
        desenhar(this->raizOffset, 0);
    }

    unsigned long long int busca(const T &chave){
        busca(raiz,chave);
    }

public:
    FILE* raizOffsetFile;
    NoB<T> *raiz;
    unsigned int raizOffset;
    int ordem;
    int max_chaves;

    FILE *b_file;

    void inserir(NoB<T> *no, NoB<T> *pai, const T &chave, unsigned long long int dataOffset);

    void dividir_no(NoB<T> *no, NoB<T> *pai, unsigned long long int dataOffset);

    int buscar_chave_maior(NoB<T> *no, const T &chave);

    void deslocar_chaves(NoB<T> *no, int pos);

    NoB<T> *criar_no(bool folha);

    void desenhar(unsigned int offset, int nivel);

    unsigned long long int busca(NoB<T> *no,const T &chave);

    void commitNodetoDisk(NoB<T> *no, unsigned long long int offset);

    int readNodefromDisk(NoB<T> *output, unsigned long long int offset);

    unsigned int getNextNodeOffset();
};

// New nodes are inserted at the end of the index file
template <typename T>
unsigned int ArvoreB<T>::getNextNodeOffset() {
    fseek(this->b_file, 0,SEEK_END);
    return ftell(this->b_file);
}

template<typename T>
void ArvoreB<T>::commitNodetoDisk(NoB<T> *no, unsigned long long int offset) {
    fseek(this->b_file, offset, SEEK_SET);
    fwrite(no, BLOCK_SIZE, 1, this->b_file);
}

template<typename T>
int ArvoreB<T>::readNodefromDisk(NoB<T> *outputNode, unsigned long long int offset) {
    fseek(this->b_file, offset, SEEK_SET);
    return fread(outputNode, BLOCK_SIZE, 1, this->b_file);
}


// Faz o desenho da árvore (arranjei por causa da monitoria hehehehe é top)
template<typename T>
void ArvoreB<T>::desenhar(unsigned int offset, int nivel)
{

    NoB<T> no;
    readNodefromDisk(&no, offset);
    // Insere espaços antes do nó
    printf("%*s", nivel * 4, "");

    // Desenha o nó
    no.imprimir_no();

    // Se não for uma folha, então chama recursivamente para
    // desenhar os filhos
    if (!no.folha) {
        for (int i = 0; i <= no.num_chaves; i++) {
            if(no.filhos[i] != -1){
                desenhar(no.filhos[i], nivel + 1);
            }
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
void ArvoreB<T>::inserir(const T &chave, unsigned long long int dataOffset)
{
    inserir(raiz, NULL, chave, dataOffset);
}


// Versão sobrecarregada com argumentos da inserção em
// árvore: privada, não pode ser utilizada pelo usuário
template<typename T>
void ArvoreB<T>::inserir(NoB<T> *no, NoB<T> *pai,
        const T &chave, unsigned long long int dataOffset)
{
    int pos = buscar_chave_maior(no, chave);
    if (no->folha) {
        // cout << "inserindo " << chave << " em " << dataOffset << endl;
        deslocar_chaves(no, pos);
        no->chaves[pos] = chave;
        no->num_chaves++;
        no->filhos[pos] = dataOffset;
        commitNodetoDisk(no,no->diskOffset);
    }
    else {
        NoB<T> nextNode;
        if(readNodefromDisk(&nextNode, no->filhos[pos])){
            inserir(&nextNode, no, chave, dataOffset);
        }
    }

    if (no->num_chaves > max_chaves) {
        dividir_no(no, pai, dataOffset);
    }
}


template<typename T>
void ArvoreB<T>::dividir_no(NoB<T> *no, NoB<T> *pai, unsigned long long int dataOffset)
{
    int i, j;
    int meio = no->num_chaves / 2;

    if (pai == NULL) {
        // Cria um novo nó não folha
        pai = criar_no(false);
        pai->diskOffset = getNextNodeOffset();
        raiz = pai;
        raiz->filhos[0] = no->diskOffset;
        commitNodetoDisk(raiz, raiz->diskOffset);
        this->raizOffset = raiz->diskOffset;
        cout << "OFFSET : " << this->raizOffset << endl;
        fseek(this->raizOffsetFile, 0, SEEK_SET);
        fwrite(&this->raizOffset,sizeof(this->raizOffset), 1, this->raizOffsetFile);
    }

    
    NoB<T> *novo = criar_no(no->folha);
    novo->diskOffset = getNextNodeOffset();
    commitNodetoDisk(novo, novo->diskOffset);

    for (i = meio + 1, j = 0; i < no->num_chaves; i++, j++) { //Nó da direita
        novo->chaves[j] = no->chaves[i];
        novo->filhos[j] = no->filhos[i];
    }

    novo->filhos[j] = no->filhos[i];

    // Aqui sera feita a alteração para transformar em Arvore B+
    for (int i = meio + 1; i <= no->num_chaves; i++) { //Nó da esquerda
        if(i==max_chaves && no->folha){
            no->filhos[i] = novo->diskOffset;
        } else {
            // colocar dados
            no->filhos[i] = -1;
        }
    }

    const T &promovida = no->chaves[meio];

    int pos = buscar_chave_maior(pai, promovida);

    deslocar_chaves(pai, pos);


    pai->chaves[pos] = promovida;
    pai->filhos[pos + 1] = novo->diskOffset;


    novo->num_chaves = no->num_chaves - meio - 1;
    no->num_chaves = meio + 1;
    pai->num_chaves++;

    commitNodetoDisk(no,no->diskOffset);
    commitNodetoDisk(novo, novo->diskOffset);
    commitNodetoDisk(pai, pai->diskOffset);
}


template<typename T>
ArvoreB<T>::ArvoreB(int ordem, string filePath)
{
    this->raiz = new NoB<T>;
    this->ordem = PRIMARY_ORDER_MAIN;
    this->max_chaves = PRIMARY_ORDER_MAIN;

    this->b_file = fopen(filePath.c_str(), "r+");
    if(this->b_file == nullptr){
        this->b_file = fopen(filePath.c_str(), "w+");
    }
    this->raizOffsetFile = fopen(PRIMARY_OFFSET_ROOT_PATH, "r+");
    if(this->raizOffsetFile == nullptr){
        this->raizOffsetFile = fopen(PRIMARY_OFFSET_ROOT_PATH, "w+");        
        this->raizOffset=0;
        fwrite(&this->raizOffset,sizeof(this->raizOffset), 1, this->raizOffsetFile);
    }
    fread(&(this->raizOffset),sizeof(this->raizOffset),1,this->raizOffsetFile);
    cout<< "raiz offset "<<this->raizOffset << endl;
    if(!readNodefromDisk(raiz,this->raizOffset)) {
        cout << "criar" << endl;
        raiz = criar_no(true);
        raiz->diskOffset = getNextNodeOffset();
        commitNodetoDisk(raiz,raiz->diskOffset);
    }
    cout<< "Root sucess\n";
}


// Cria um novo nó folha vazio
template<typename T>
NoB<T> *ArvoreB<T>::criar_no(bool folha)
{
    NoB<T> *novo = new NoB<T>;

    // novo->chaves = new T[max_chaves + 1];
    // novo->filhos = new unsigned int [max_chaves + 2];
    
    for (int i = 0; i <= max_chaves + 1; i++) {
        novo->filhos[i] = -1;
    }

    novo->num_chaves = 0;
    novo->folha = folha;

    return novo;
}

template<typename T>
unsigned long long int ArvoreB<T>::busca(NoB<T> *no,const T &chave){
    int meio;
    int limitSup = no->num_chaves - 1;
    int limitInf = 0;
    NoB<T> nextNode;
    while (limitInf<=limitSup){
        meio = (limitInf+limitSup)/2;
        if(chave == no->chaves[meio]){
            if (no->folha) {
                return no->filhos[meio];
            } 
        }
        if(chave > no->chaves[meio]){
            limitInf = meio +1;
            // std::cout<< limitInf << " maior\n";
        } else{
            limitSup = meio -1;
            // std::cout << limitSup <<" menor\n";
        }
    }
    if(no->filhos[limitInf]==-1){
        return -1;
    } else{

    if(readNodefromDisk(&nextNode, no->filhos[limitInf])){
        return busca(&nextNode,chave);
    }  else {
        // melhorar aqui
        return -1;
    }
    }
} 