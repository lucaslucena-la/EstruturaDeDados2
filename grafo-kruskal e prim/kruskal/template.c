#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define true 1
#define false 0
#define INT_MAX 2147483647  // Update INT_MAX for long integers if necessary
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

typedef struct aresta {
    int origem;
    int destino;
    TIPOPESO peso;
} ARESTA;

typedef struct {
    ARESTA *arestas;
    int numArestas;
} ARESTA_LISTA;

// Function prototypes
GRAFO *criarGrafo(int v);
ADJACENCIA *criaAdj(int v, int peso);
ADJACENCIA *inseriListAdj(ADJACENCIA *adj, int vf, TIPOPESO p);
bool criaAresta(GRAFO *gr, int vi, int vf, TIPOPESO p);
void imprime(GRAFO *gr);
ARESTA_LISTA *obterArestas(GRAFO *gr);
int comparar(const void *a, const void *b);
int find(int *pai, int i, int *operations);
void unionSets(int *pai, int *rank, int x, int y, int *operations);
void agm_kruskal(GRAFO *gr, int *operations);

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

ADJACENCIA *inseriListAdj(ADJACENCIA *adj, int vf, TIPOPESO p) {
    ADJACENCIA *novo = criaAdj(vf, p);
    novo->prox = adj;
    return novo;
}

bool criaAresta(GRAFO *gr, int vi, int vf, TIPOPESO p) {
    if (!gr) return false;
    if (vf < 0 || vf >= gr->vertices || vi < 0 || vi >= gr->vertices) return false;
    gr->adj[vi].cab = inseriListAdj(gr->adj[vi].cab, vf, p);
    gr->adj[vf].cab = inseriListAdj(gr->adj[vf].cab, vi, p);
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

ARESTA_LISTA *obterArestas(GRAFO *gr) {
    ARESTA_LISTA *arestas = (ARESTA_LISTA *)malloc(sizeof(ARESTA_LISTA));
    arestas->arestas = (ARESTA *)malloc(gr->arestas * sizeof(ARESTA));
    arestas->numArestas = 0;

    for (int i = 0; i < gr->vertices; i++) {
        ADJACENCIA *ad = gr->adj[i].cab;
        while (ad) {
            if (i < ad->vertice) {
                arestas->arestas[arestas->numArestas].origem = i;
                arestas->arestas[arestas->numArestas].destino = ad->vertice;
                arestas->arestas[arestas->numArestas].peso = ad->peso;
                arestas->numArestas++;
            }
            ad = ad->prox;
        }
    }
    return arestas;
}

int comparar(const void *a, const void *b) {
    ARESTA *arestaA = (ARESTA *)a;
    ARESTA *arestaB = (ARESTA *)b;
    return arestaA->peso - arestaB->peso;
}

int find(int *pai, int i, int *operations) {
    (*operations)++;  
    if (pai[i] != i) {
        pai[i] = find(pai, pai[i], operations);
    }
    return pai[i];
}

void unionSets(int *pai, int *rank, int x, int y, int *operations) {
    int raizX = find(pai, x, operations);
    int raizY = find(pai, y, operations);
    (*operations)++;  

    if (rank[raizX] < rank[raizY]) {
        pai[raizX] = raizY;
    } else if (rank[raizX] > rank[raizY]) {
        pai[raizY] = raizX;
    } else {
        pai[raizY] = raizX;
        rank[raizX]++;
    }
}

void agm_kruskal(GRAFO *gr, int *operations) {
    ARESTA_LISTA *arestas = obterArestas(gr);
    qsort(arestas->arestas, arestas->numArestas, sizeof(ARESTA), comparar);

    int *pai = (int *)malloc(gr->vertices * sizeof(int));
    int *rank = (int *)malloc(gr->vertices * sizeof(int));
    for (int i = 0; i < gr->vertices; i++) {
        pai[i] = i;
        rank[i] = 0;
    }

    printf("Arestas na AGM:\n");
    for (int i = 0, e = 0; e < gr->vertices - 1 && i < arestas->numArestas; i++) {
        ARESTA aresta = arestas->arestas[i];

        int x = find(pai, aresta.origem, operations);
        int y = find(pai, aresta.destino, operations);

        if (x != y) {
            printf("%d -- %d == %d\n", aresta.origem, aresta.destino, aresta.peso);
            unionSets(pai, rank, x, y, operations);
            e++;
        }
    }

    free(arestas->arestas);
    free(arestas);
    free(pai);
    free(rank);
}

int main() {
    clock_t start, end;
    double cpu_time_used;
    int operations = 0;  

    FILE *file = fopen("ny.gr", "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return 1;
    }

    int vi, vf, peso;
    char label[10];
    int max_vertex = 0;
    int num_edges = 0;

    while (fscanf(file, "%s", label) != EOF) {
        if (label[0] == 'a') {
            if (fscanf(file, "%d %d %d", &vi, &vf, &peso) == 3) {
                if (vi > max_vertex) max_vertex = vi;
                if (vf > max_vertex) max_vertex = vf;
                num_edges++;
            }
        } else if (label[0] == 'p') {
            
            char format[10];
            int vertices_from_p, edges_from_p;
            fscanf(file, "%s %d %d", format, &vertices_from_p, &edges_from_p);
            max_vertex = vertices_from_p;
            num_edges = edges_from_p;
            break;  
        } else {
           
            while (fgetc(file) != '\n' && !feof(file));
        }
    }

    int vertices = max_vertex;  
    printf("Number of vertices: %d\n", vertices);
    printf("Number of edges: %d\n", num_edges);

    GRAFO *grafo = criarGrafo(vertices);

    rewind(file);  

    while (fscanf(file, "%s", label) != EOF) {
        if (label[0] == 'a') {
            if (fscanf(file, "%d %d %d", &vi, &vf, &peso) == 3) {
                vi--;
                vf--;
                criaAresta(grafo, vi, vf, peso);
            }
        } else {
   
            while (fgetc(file) != '\n' && !feof(file));
        }
    }

    fclose(file);

 
    start = clock();
    agm_kruskal(grafo, &operations);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Execution time: %f seconds\n", cpu_time_used);
    printf("Number of operations: %d\n", operations);

    free(grafo->adj);
    free(grafo);

    return 0;
}
