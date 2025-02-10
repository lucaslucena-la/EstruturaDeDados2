#include <stdio.h>
#include <stdlib.h>

typedef struct EstNo
{
    int chave;
    struct EstNo *esq;
    struct EstNo *dir;
    int h;

    // Se necessário pode adicionar elementos na struct
    

} tipo_no;

tipo_no *AlocaNo(int );
void imprime(tipo_no *, int );
tipo_no *busca(tipo_no *, int );
tipo_no *insere(tipo_no *, int );
tipo_no *rsd(tipo_no *);
tipo_no *rse(tipo_no *);


tipo_no *rsd(tipo_no* arv){
    tipo_no *aux;
    aux = arv->esq;
    arv ->esq = aux ->dir;
    aux -> dir = arv;
    return aux;
}

tipo_no *rse(tipo_no *arv){
    tipo_no *aux;
    aux = arv->dir;
    arv -> dir = aux -> esq;
    aux -> esq = arv;
    return aux;
}

tipo_no *AlocaNo(int chave) // cria um ponteiro nulo para a raiz 
{
    tipo_no *novo_no;

    novo_no =(tipo_no*) malloc(sizeof(tipo_no)); // aloca memoria 
    novo_no->dir = NULL;
    novo_no->esq = NULL;
    novo_no->chave = chave;
    return novo_no;

}

void imprime(tipo_no *arv, int tab) {
    if (arv != NULL) {
        // Indentação para visualização hierárquica
        for (int i = 0; i < tab; i++) {
            printf("\t");
        }
        
        // Imprime a chave do nó atual
        printf("Chave: %d\n", arv->chave);
        
        // Imprime subárvore esquerda com mais uma tabulação
        imprime(arv->esq, tab + 1);
        
        // Imprime subárvore direita com mais uma tabulação
        imprime(arv->dir, tab + 1);
    }
}




tipo_no *busca(tipo_no *no, int chave)
{
	// implemente seu código de busca aqui
}

tipo_no *insere(tipo_no *arv, int chave) {
    if (arv == NULL) {
        return AlocaNo(chave);
    }

    if (chave < arv->chave) {
        arv->esq = insere(arv->esq, chave);
        arv = rsd(arv);
    } else if (chave > arv->chave) {
        arv->dir = insere(arv->dir, chave);
        arv = rse(arv);
    }
    // Caso chave == arv->chave, não inserimos novamente o valor na árvore
    // e simplesmente retornamos o nó atual

    return arv;
}


/*TNoA *insere(TNoA *no, int chave)
{
	if (no == NULL) {
        TNoA *novo = (TNoA *)malloc(sizeof(TNoA));
        novo->chave = chave;
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    }

    if (chave < no->chave) {
        no->esq = insere(no->esq, chave);
        if (no->esq->chave == chave) {
            return rotacaoDireita(no);
        }

        if (no->esq->esq != NULL && no->esq->esq->chave == chave) {
            return rotacaoDireita(rotacaoDireita(no));
        }

        if (no->esq->dir != NULL && no->esq->dir->chave == chave) {
            return rotacaoDireita(rotacaoEsquerda(no));
        }
    } else if (chave > no->chave) {
        no->dir = insere(no->dir, chave);
        if (no->dir->chave == chave) {
            return rotacaoEsquerda(no);
        }

        if (no->dir->dir != NULL && no->dir->dir->chave == chave) {
            return rotacaoEsquerda(rotacaoEsquerda(no));
        }

        if (no->dir->esq != NULL && no->dir->esq->chave == chave) {
            return rotacaoEsquerda(rotacaoDireita(no));
        }
    }

    return no;
}*/


int main(void) {
    tipo_no *raiz = NULL;
    int qt, value;
    raiz = AlocaNo(50);


    printf("Insira quantos elementos você quer: ");
    scanf("%d", &qt);

    for (int i = 0; i < qt; i++) {
        printf("Insira o valor: ");
        scanf("%d", &value);
        raiz = insere(raiz, value);
    }

    printf("Árvore:\n");
    imprime(raiz, 0);

    return 0;
}
