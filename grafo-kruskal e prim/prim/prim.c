#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

#define true 1
#define false 0
#define INT_MAX 32000
typedef int bool;
typedef int TIPOPESO;

typedef struct adjacencia {
    int vertice;
    TIPOPESO peso;
    struct adjacencia *prox;
} ADJACENCIA;

typedef struct vertice {
    int grau;
    ADJACENCIA *cab;
} VERTICE;

typedef struct grafo {
    int vertices;
    int arestas;
    VERTICE *adj;
} GRAFO;

GRAFO *criarGrafo(int v) {
    GRAFO *g = (GRAFO *)malloc(sizeof(GRAFO));
    g->vertices = v;
    g->arestas = 0;
    g->adj = (VERTICE *)malloc(v * sizeof(VERTICE));

    for (int i = 0; i < v; i++) {
        g->adj[i].cab = NULL;
        g->adj[i].grau = 0;
    }
    return g;
}

ADJACENCIA *criaAdj(int v, int peso) {
    ADJACENCIA *temp = (ADJACENCIA *)malloc(sizeof(ADJACENCIA));
    temp->vertice = v;
    temp->peso = peso;
    temp->prox = NULL;
    return temp;
}

ADJACENCIA *inseriListAdj(ADJACENCIA *adj, int vi, int vf, TIPOPESO p) {
    ADJACENCIA *ant = adj;
    ADJACENCIA *atual = adj;
    int control = 0;

    ADJACENCIA *novo = criaAdj(vf, p);

    while (atual != NULL && atual->vertice < vf) {
        ant = atual;
        atual = atual->prox;
        control = 1;
    }

    if (ant == NULL && control == 0) {
        novo->prox = atual;
        return novo;
    } else if (control == 0) {
        novo->prox = atual;
        return novo;
    } else {
        novo->prox = atual;
        ant->prox = novo;
    }

    return adj;
}

bool criaAresta(GRAFO *gr, int vi, int vf, TIPOPESO p) {
    if (!gr) return false;
    if (vf < 0 || vf >= gr->vertices) return false;
    if (vi < 0 || vi >= gr->vertices) return false;

    gr->adj[vi].cab = inseriListAdj(gr->adj[vi].cab, vi, vf, p);
    gr->adj[vf].cab = inseriListAdj(gr->adj[vf].cab, vf, vi, p);
    gr->arestas++;
    return true;
}

void imprime(GRAFO *gr) {
    printf("Vertices: %d. Arestas: %d\n", gr->vertices, gr->arestas);
    
    for (int i = 0; i < gr->vertices; i++) {
        printf("v%d: ", i);
        ADJACENCIA *ad = gr->adj[i].cab;
        while (ad) {
            printf("v%d(%d) ", ad->vertice, ad->peso);
            ad = ad->prox;
        }
        printf("\n");
    }
}

int extrai_min(int *chave, bool *visitado, int vertices) {
    int min = INT_MAX, min_index = -1;
    for (int v = 0; v < vertices; v++) {
        if (!visitado[v] && chave[v] < min) {
            min = chave[v];
            min_index = v;
        }
    }
    return min_index;
}

void agm_prim(GRAFO *gr, int orig, int *pai, int *comparisons) {
    int *chave = (int *)malloc(gr->vertices * sizeof(int));
    bool *visitado = (bool *)malloc(gr->vertices * sizeof(bool));

    for (int i = 0; i < gr->vertices; i++) {
        chave[i] = INT_MAX;
        visitado[i] = false;
        pai[i] = -1;
    }

    chave[orig] = 0;

    for (int count = 0; count < gr->vertices - 1; count++) {
        int u = extrai_min(chave, visitado, gr->vertices);
        if (u == -1) break; 
        visitado[u] = true;

        ADJACENCIA *ad = gr->adj[u].cab;
        while (ad != NULL) {
            int v = ad->vertice;
            (*comparisons)++; 
            if (!visitado[v]) {
                (*comparisons)++; 
                if (ad->peso < chave[v]) {
                    pai[v] = u;
                    chave[v] = ad->peso;
                }
            }
            ad = ad->prox;
        }
    }

    printf("Edge \tWeight\n");
    for (int i = 1; i < gr->vertices; i++) {
        if (pai[i] != -1)
            printf("%d - %d \t%d\n", pai[i], i, chave[i]);
    }

    free(chave);
    free(visitado);
}

int main() {
    clock_t start, end;
    double cpu_time_used;

    start = clock();

    FILE *file = fopen("ny.gr", "r");
    if (file == NULL) {
        printf("Error: Could not open file cal.gr\n");
        return 1;
    }

    int numVertices = 1048578; 
    GRAFO *gr = criarGrafo(numVertices);

    char label;
    int vi, vf, peso;
    while (fscanf(file, " %c %d %d %d", &label, &vi, &vf, &peso) == 4) {
        criaAresta(gr, vi, vf, peso);
    }

    fclose(file);

    imprime(gr);

    int *pai = (int *)malloc(numVertices * sizeof(int));
    int comparisons = 0;
    agm_prim(gr, 0, pai, &comparisons);  

    printf("Total comparisons made: %d\n", comparisons);

    free(pai);

    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", cpu_time_used);

    return 0;
}
