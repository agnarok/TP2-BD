/* Programa de testes para a árvore B.
 *
 * Insere chaves repetidamente até que o usuário digite
 * uma chave sentinela.
 */

// Sentinela para a leitura
// Pré-condições: deve ter um tipo adequado para as chaves
// da árvore
#define SENTINELA '.'

// Ordem da árvore
#define ORDEM 2

#include <iostream>
#include "btree.h"

using std::cout;
using std::cin;

int main()
{
	int c;

    // Cria uma árvore vazia
	ArvoreB<int> arvore(ORDEM);

	// while ((std::cin >> c) && c != SENTINELA) {
    //     // Caso o valor lido seja diferente do sentinela,
    //     // insere na árvore
	// 	arvore.inserir(c);

    //     // Exibe a mensagem e desenha a árvore
	// 	std::cout << "Apos inserir " << c << ":\n";
	// 	arvore.desenhar();
	// 	std::cout << "\n---------------------\n";
	// }
	int i=1;
	while (i<=17){
		arvore.inserir(i);
		if(i==17){
		std::cout << "Apos inserir " << i << ":\n";
		arvore.desenhar();
		std::cout << "\n---------------------\n";
		}
		i++;
	}
	arvore.busca(20);
}
