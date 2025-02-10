#include <stdio.h>
#include <stdlib.h>

typedef struct eh_no
{
    int chave;
    struct eh_no *esq;
    struct eh_no *dir;
    

} TNoA;

// função que cria novo no 
TNoA *aloca_noh(int chave) {
        TNoA *novo_noh;
        novo_noh = (TNoA *)malloc(sizeof(TNoA));
        novo_noh->chave = chave;
        novo_noh->esq = NULL;
        novo_noh->dir = NULL;
        return novo_noh;
}


TNoA *cria(void)
{
	return NULL;
}

void imprime(TNoA *nodo, int tab) // função de impressão
{
	
	if (nodo != NULL)
	{

		imprime(nodo->esq, tab + 2);
		printf("%d\n", nodo->chave);
		imprime(nodo->dir, tab + 2);
	}
}



TNoA *tic(TNoA *no) { // funçao que rotação à direita 
    TNoA *aux = no->esq;
    no->esq = aux->dir;
    aux->dir = no;
    return aux;
}


TNoA *tac(TNoA *no) { // funçao que rotação à esquerda 
    TNoA *aux = no->dir;
    no->dir = aux->esq;
    aux->esq = no;
    return aux;
}


TNoA *busca(TNoA *no, int chave) // funcao que bsuca no e rotaciona ele para a raiz  
{
	 if (no == NULL || no->chave == chave)
    {
        return no;
    }
    if (chave > no->chave) // se chave que você busca for maior, desce para a direita 
    {

        no->dir = busca(no->dir, chave);
        no = tac(no);
        
    }
    else
    {
        no->esq = busca(no->esq, chave); // se chave que você busca for menor, desce para a esquerda 
        no = tic(no);
    }

    return no;
}



TNoA *insere(TNoA *no, int chave) {
    if (no == NULL) {
        return aloca_noh(chave);
    }

    if (chave < no->chave) {
        no->esq = insere(no->esq, chave);
        if (no->esq->chave == chave) {
            return tic(no);
        }

        if (no->esq->esq != NULL && no->esq->esq->chave == chave) {
            return tic(tic(no)); // rotação dupla
        }

        if (no->esq->dir != NULL && no->esq->dir->chave == chave) {
            return tic(tac(no)); // rotação dupla
        }
    } else if (chave > no->chave) {
        no->dir = insere(no->dir, chave);
        if (no->dir->chave == chave) {
            return tac(no);
        }

        if (no->dir->dir != NULL && no->dir->dir->chave == chave) {
            return tac(tac(no)); // rotação dupla
        }

        if (no->dir->esq != NULL && no->dir->esq->chave == chave) {
            return tac(tic(no)); // rotação dupla à direita
        }
    }

    return no;
}


// Main 
int main(void)
{
    TNoA *raiz;
	raiz = cria();
    int qt,value,x;

    scanf("%i",&qt);

    for(int i=0; i<qt;i++){

        scanf("%i",&value);
        raiz = insere(raiz,value);
    }
    scanf("%i",&x);
    raiz = busca(raiz, x);
	imprime(raiz,0);

 	return 0;
}