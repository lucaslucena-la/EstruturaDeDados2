#include "arvore_abb.h"

//Função que compara maior valor 

int max(int x, int y) {
    return (x > y) ? x : y;
}


//Função que retona altura da árvore 

int altura_no(tipo_abb *no) {
    if (no == NULL)
        return -1;
    else {
        int altura_esq = altura_no(no->esq);
        int altura_dir = altura_no(no->dir);
        return max(altura_esq, altura_dir) + 1; // calcula qual eh a altura maxima, se eh do ramd da esquerda ou do ramo da direita 
    }
}

// função que insere chave na arvore 

tipo_abb *insere(tipo_abb *no, int chave) {
    if (no == NULL) { // se a arvore for vazia, faça isso 
        tipo_abb *novo_no = (tipo_abb *)malloc(sizeof(tipo_abb));
        novo_no->chave = chave; // recebe chave 
        novo_no->esq = novo_no->dir = NULL; //aponta para nulo 
        return novo_no;
    }

    // caso a arvore nao seja vazia 
    if (chave < no->chave) { // verifica se a chave que queremos inserir eh menor que a chave do no atual 
        no->esq = insere(no->esq, chave); // se sim, inserimos na esquerda 
    } else if (chave > no->chave) {
        no->dir = insere(no->dir, chave); // analogamente, fazemos o menos a direita 
    }

    // se for igual nao faz nada porque nao podemos inserir chaves duplicadas

    return no;
}

// Busca noh  na arvore

tipo_abb *buscar(tipo_abb *raiz, int chave) {
    if (raiz == NULL || raiz->chave == chave) // se houver apenas a raiz na arvore
        return raiz; // caso base para a parada da recursao 
    if (chave < raiz->chave) 
        return buscar(raiz->esq, chave); // chamada recursiva que percorre todo o ramo esquedo da árvore para em busca do noh 
    return buscar(raiz->dir, chave); // chamada recursiva que percorre todo o ramo direito da árvore em busca do noh 
}



//função que percore em pré ordem
/*
Passos:
-Imprimir
-Chamar recursão a esquerda
-Chamar recursão a direita
*/
void PercursoPreOrdem(tipo_abb *arv){
    if (arv != NULL){
        printf (" %d ",  arv -> chave );
        PercursoPreOrdem(arv ->esq);
        PercursoPreOrdem(arv ->dir);
    }
}   

//função que percorre em ordem
/*
Passos:
-Chamar recursão a esquerda
-Imprimir
-Chamar recursão a direita
*/
void PercursoOrdem(tipo_abb *arv){
    if (arv != NULL){
        PercursoOrdem(arv -> esq);
        printf(" %d ", arv -> chave);
        PercursoOrdem(arv -> dir);

    }
}

//função que percorre em pós ordem
/*
Passos:
-Chamar recursão a esquerda
-Chamar recursão a direita
-Imprimir
*/
void PercursoPosOrdem(tipo_abb *arv){
    if (arv != NULL){
        PercursoPosOrdem(arv -> esq);
        PercursoPosOrdem(arv -> dir);
        printf(" %d ", arv -> chave);
        

    }
}


// Menu para o usuário interagir 


// Função para ler números de um arquivo e inseri-los na árvore de busca binária

tipo_abb* ler_e_inserir(const char *nome_arquivo, tipo_abb *raiz) {
    // Abre o arquivo no modo de leitura
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        // Se não conseguir abrir o arquivo, mostra uma mensagem de erro e encerra o programa
        fprintf(stderr, "Erro ao abrir o arquivo %s.\n", nome_arquivo);
        return NULL; // Encerra o programa com um código de erro
    }

    int numero;

    // lê cada número e insere na árvore
    while (fscanf(arquivo, "%d", &numero) == 1) {
            raiz = insere(raiz, numero);
    }
    fclose(arquivo); // Fecha o arquivo depois de ler todos os números
    
    // Retorna a raiz da árvore atualizada com todos os números inseridos
    return raiz; 
}


void liberar_arvore(tipo_abb *arvore) {
    if (arvore != NULL) {
        liberar_arvore(arvore->esq);
        liberar_arvore(arvore->dir);
        free(arvore);
    }
}

tipo_abb *buscamaior(tipo_abb *arv){
    if (arv == NULL){
        return arv;
    }else{
        if(arv -> dir == NULL){
            return arv;
        }else{
            buscamaior(arv-> dir);
        }
    }
}


tipo_abb *buscamenor(tipo_abb *arv){
    if (arv == NULL){
        return arv;
    }else{
        if(arv -> esq == NULL){
            return arv;
        }else{
            buscamaior(arv-> esq);
        }
    }
}


bool VerificaCheia(tipo_abb *arv){
    if(arv == NULL){
        return true;
    }

    if((arv -> esq != NULL) && (arv -> dir == NULL) || (arv -> esq == NULL) && (arv->dir !=NULL)){
        return false;
    }


    bool esquerdacheia = (VerificaCheia(arv ->esq));
    bool direitacheia = (VerificaCheia(arv->dir));

    return esquerdacheia && direitacheia;
}


tipo_abb *trocafilhos(tipo_abb *arv){
    if (arv == NULL){
        return NULL;
    }

    tipo_abb* aux = arv-> esq;
    arv -> esq = arv -> dir;
    arv -> dir = aux;

    trocafilhos(arv -> dir);
    trocafilhos(arv -> esq);

    return arv;
    
}

void imprime(tipo_abb *arv, int tab)
{
    if (arv != NULL)
    {
        // Aumenta a indentação para o próximo nível de profundidade
        imprime(arv->dir, tab + 4);

        // Imprime a chave com o número adequado de espaços
        for (int i = 0; i < tab; i++)
            printf(" ");
        printf("%d\n", arv->chave);

        // Chama recursivamente para o lado esquerdo
        imprime(arv->esq, tab + 4);
    }
}







