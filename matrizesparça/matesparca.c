#include <stdio.h>
#include <stdlib.h>

// Estrutura para armazenar cada elemento da matriz
typedef struct tempNo {
    float valor;            // Valor armazenado na célula
    int coluna;             // Índice da coluna
    struct tempNo* prox;    // Ponteiro para o próximo elemento na lista
} NO;

typedef NO* PONT;

// Estrutura da matriz com um arranjo de listas ligadas
typedef struct {
    PONT* A;       // Ponteiro para um arranjo de ponteiros (listas ligadas)
    int linhas;    // Número de linhas da matriz
    int colunas;   // Número de colunas da matriz
} MATRIZ;

// Função para inicializar a matriz esparsa
MATRIZ *inicializarMatriz(int lin, int col){
    int i;
    
    MATRIZ *novo;
    
    novo = (MATRIZ *) malloc (sizeof(MATRIZ)); // Aloca memória para a estrutura da matriz
    
    novo->A = (PONT *) malloc(lin * sizeof(PONT)); // Aloca memória para o arranjo de listas ligadas
    novo->linhas = lin;   // Define o número de linhas
    novo->colunas = col;  // Define o número de colunas
    
    // Inicializa cada ponteiro da matriz como NULL
    for(i = 0; i < lin; i++)
        novo->A[i] = NULL;
    
    return novo;
}

// Função para imprimir a matriz esparsa
void imprimeMatriz(MATRIZ* m){
    for(int l = 0; l < m->linhas; l++){
        if(m->A[l] != NULL){
            PONT c = m->A[l];
            while(c != NULL){
                printf("  [%f|(%d,%d)]", c->valor, l, c->coluna); // Imprime o valor, linha e coluna do elemento
                c = c->prox;
            }
            printf("\n");
        }
    }
}

// Função que insere um valor na matriz
int insereMatriz(MATRIZ* m, int lin, int col, float val){
    // Verifica se a linha e a coluna são válidas
    if (lin < 0 || lin >= m->linhas || col < 0 || col >= m->colunas)
        return 0;
    
    PONT ant = NULL;
    PONT atual = m->A[lin];
    
    // Percorre a lista até encontrar a posição correta para inserção
    while (atual != NULL && atual->coluna < col){
        ant = atual;
        atual = atual->prox;
    }
    
    // Caso o nó já exista, atualiza ou remove o valor
    if(atual != NULL && atual->coluna == col){
        if(val == 0){
            if(ant == NULL) 
                m->A[lin] = atual->prox;  // Se for o primeiro elemento da lista
            else 
                ant->prox = atual->prox;  // Remove o nó
            
            free(atual); // Libera a memória
        } else {
            atual->valor = val; // Atualiza o valor
        }
    } else { // Caso o nó não exista, insere um novo nó
        PONT novo = (PONT) malloc(sizeof(NO)); // Aloca memória para o novo nó
        
        novo->coluna = col; // Define a coluna
        novo->valor = val;  // Define o valor
        novo->prox = atual; // Aponta para o próximo nó
        
        if(ant == NULL){
            m->A[lin] = novo; // Insere no início da lista
        } else {
            ant->prox = novo; // Insere no meio ou no final da lista
        }
    }

    return 1;
}

// Função que retorna o valor na posição especificada da matriz
float ValorMatriz(MATRIZ* m, int lin, int col){
    // Verifica se a linha e a coluna são válidas
    if (lin < 0 || lin >= m->linhas || col < 0 || col >= m->colunas){
        return 0;
    }

    PONT atual = m->A[lin];
    
    // Percorre a lista até encontrar o nó na coluna especificada
    while (atual != NULL && atual->coluna < col){
        atual = atual->prox;
    }
    
    // Retorna o valor do nó encontrado ou 0 se não existir
    if(atual != NULL && atual->coluna == col){
        return atual->valor;
    } else {
        return 0;
    }
}

// Função que exclui um elemento da matriz
int excluirMatriz(MATRIZ *m, int lin, int col){
    // Verifica se a linha e a coluna são válidas
    if (lin < 0 || lin >= m->linhas || col < 0 || col >= m->colunas){
        return 0;
    }
    
    PONT ant = NULL;
    PONT atual = m->A[lin];

    // Percorre a lista até encontrar o nó na coluna especificada
    while (atual != NULL && col != atual->coluna) {
        ant = atual;
        atual = atual->prox;
    }

    // Se o nó for encontrado, remove-o
    if (atual != NULL) {
        if (ant == NULL)
            m->A[lin] = atual->prox; // Remove o primeiro nó
        else
            ant->prox = atual->prox; // Remove o nó do meio ou do final
        
        free(atual); // Libera a memória
        return 1;
    } else {
        printf("Elemento não encontrado na matriz.\n");
        return 0;
    }
}

MATRIZ* multEscalarMatriz(MATRIZ* m, int x){
    // Inicializa uma nova matriz para armazenar o resultado
    MATRIZ* resultado = inicializarMatriz(m->linhas, m->colunas);

    // Percorre todas as linhas da matriz original
    for(int i = 0; i < m->linhas; i++){
        PONT atual = m->A[i];

        // Percorre a lista ligada de cada linha
        while(atual != NULL){
            // Multiplica o valor pelo escalar e insere na matriz resultado
            insereMatriz(resultado, i, atual->coluna, atual->valor * x);
            atual = atual->prox;
        }
    }

    // Retorna a nova matriz com os valores multiplicados
    return resultado;
}

float somatorioMatriz(MATRIZ* m){
    float soma = 0; 
    
    for (int i = 0; i< m-> linhas; i++){
            PONT atual = m-> A[i];

        while (atual != NULL)
        {
            soma += atual-> valor;
            atual = atual -> prox;
        }
        
    }

    return soma;
}



// Função que soma duas matrizes esparsas
MATRIZ* soma2Matriz(MATRIZ* m, MATRIZ* n){
    // Verifica se as dimensões das matrizes são compatíveis
    if (m->linhas != n->linhas || m->colunas != n->colunas) {
        printf("As matrizes não têm as mesmas dimensões.\n");
        return NULL;
    }

    // Inicializa a matriz resultado
    MATRIZ* resultado = inicializarMatriz(m->linhas, m->colunas);

    // Percorre todas as linhas das matrizes
    for (int i = 0; i < m->linhas; i++) {
        PONT atualM = m->A[i];
        PONT atualN = n->A[i];

        // Percorre a linha da matriz m
        while (atualM != NULL) {
            insereMatriz(resultado, i, atualM->coluna, atualM->valor);
            atualM = atualM->prox;
        }

        // Percorre a linha da matriz n
        while (atualN != NULL) {
            float valorExistente = ValorMatriz(resultado, i, atualN->coluna);
            insereMatriz(resultado, i, atualN->coluna, valorExistente + atualN->valor);
            atualN = atualN->prox;
        }
    }

    return resultado;
}

int main(){
    
    MATRIZ *m, *n, *resultado;
    int col,lin,qtvalores;
    int colVal,linVal;
    float val,sum;
    scanf("%d",&qtvalores);
    scanf("%d",&lin);
    scanf("%d",&col);

    m = inicializarMatriz(lin,col);
    n = inicializarMatriz(lin,col);

    for(int i=0; i<qtvalores; i++){
        scanf("%d",&linVal);
        scanf("%d",&colVal);
        scanf("%f",&val);
        insereMatriz(m,linVal,colVal,val);
    }

    for(int i=0; i<qtvalores; i++){
        scanf("%d",&linVal);
        scanf("%d",&colVal);
        scanf("%f",&val);
        insereMatriz(n,linVal,colVal,val);
    }

    resultado = soma2Matriz(m,n);
    
    sum = somatorioMatriz(resultado);
    printf("%f",sum);

    return 0;
}