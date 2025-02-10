#include "arvore_abb.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main() {
    tipo_abb *raiz = NULL;  // Inicializa a árvore vazia

    // Inserções na árvore
    raiz = insere(raiz, 50);
    raiz = insere(raiz, 30);
    raiz = insere(raiz, 70);
    raiz = insere(raiz, 20);
    raiz = insere(raiz, 40);
    

    // Imprime a árvore em ordem (in-order traversal)
    printf("Árvore original em ordem:");
    PercursoOrdem(raiz);
    printf("\n");
    printf("Árvore original em pos-ordem: ");
    
    
    PercursoPosOrdem(raiz);
    printf("\n");

    printf("Árvore original em pré-ordem: ");
    PercursoPreOrdem(raiz);
    
    printf("\n");
    printf("\n");
    imprime(raiz,0);
    printf("\n");

    int chave_busca1 = 60;
    tipo_abb *resultado_busca1 = buscar(raiz, chave_busca1);
    if (resultado_busca1 != NULL) {
        printf("Chave %d encontrada na árvore.\n\n", chave_busca1);
    } else {
        printf("Chave %d não encontrada na árvore.\n", chave_busca1);
    }

    tipo_abb *menor1 = buscamenor(raiz);
    tipo_abb *maior1 = buscamaior(raiz);

    if (menor1 != NULL) {
        printf("\nO menor valor na árvore original é: %d\n", menor1->chave);
    }

    if (maior1 != NULL) {
        printf("\nO maior valor na árvore original é: %d\n\n", maior1->chave);
    }
    

    trocafilhos(raiz);
    printf("Árvore espelhada em ordem: ");
    PercursoOrdem(raiz);
    printf("\n");
    printf("\n");
    imprime(raiz,0);
    printf("\n");

    // Verifica se a árvore é cheia
    if (VerificaCheia(raiz)) {
        printf("\nA árvore é cheia.\n");
    } else {
        printf("\nA árvore não é cheia.\n");
    }

    // Busca por um nó específico
    int chave_busca2 = 60;
    tipo_abb *resultado_busca2 = buscar(raiz, chave_busca2);
    if (resultado_busca2 != NULL) {
        printf("\nChave %d encontrada na árvore espelhada.\n", chave_busca2);
    } else {
        printf("\nChave %d não encontrada na árvore espelhada.\n", chave_busca2);
    }

    // Busca o menor e o maior valor na árvore
    tipo_abb *menor2 = buscamenor(raiz);
    tipo_abb *maior2 = buscamaior(raiz);

    if (menor2 != NULL) {
        printf("\nO menor valor na árvore esepelhada é: %d\n", menor2->chave);
    }

    if (maior2 != NULL) {
        printf("\nO maior valor na árvore espelhada é: %d\n", maior2->chave);
    }

    // Libera a memória alocada pela árvore
    liberar_arvore(raiz);

    return 0;
}
