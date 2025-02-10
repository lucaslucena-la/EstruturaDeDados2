#ifndef __ARVORE_ABB_H
#define __ARVORE_ABB_H

#include <time.h> // para funções de rand 
#include <unistd.h>  // para a função sleep 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



typedef struct est_abb {
    int valor;
    int chave;
    struct est_abb *esq;
    struct est_abb *dir;
} tipo_abb;

//prototipação de funções
int max(int x, int y);

int altura_no(tipo_abb *no);

tipo_abb *insere(tipo_abb *no, int chave);

int obter_contador_rotacoes();

void PercursoPreOrdem(tipo_abb *arv);

void PercursoOrdem(tipo_abb *arv);

void PercursoPosOrdem(tipo_abb *arv);

void imprime(tipo_abb *arv, int tab);

tipo_abb* ler_e_inserir(const char *nome_arquivo, tipo_abb *arvore);

void selecionar_amostra(int *chaves, int *amostra, int total, int amostra_size);

void mostrar_amostra(int *amostra, int tamanho);

void liberar_arvore(tipo_abb *arvore);

tipo_abb *buscamaior(tipo_abb *arv);

tipo_abb *buscamenor(tipo_abb *arv);

bool VerificaCheia(tipo_abb *arv);

tipo_abb *trocafilhos(tipo_abb *arv);

tipo_abb *buscar(tipo_abb *raiz, int chave);



#endif
