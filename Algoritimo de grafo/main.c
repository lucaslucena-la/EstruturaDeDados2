#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define true 1
#define false 0
#define INT_MAX 32000
#define START 1
typedef int bool;
typedef int TIPOPESO;

typedef struct adjacencia
{
    int vertice;
    TIPOPESO peso;
    struct adjacencia *prox;
} ADJACENCIA;

typedef struct vertice
{
    ADJACENCIA *cab;
} VERTICE;

typedef struct grafo
{
    int vertices;
    int arestas;
    VERTICE *adj;
} GRAFO;

/* Criando um grafo */
GRAFO *criarGrafo(int v)
{
    GRAFO *g = (GRAFO *)malloc(sizeof(GRAFO));
    g->vertices = v;
    g->arestas = 0;
    g->adj = (VERTICE *)malloc(v * sizeof(VERTICE));
    for (int i = 0; i < v; i++)
        g->adj[i].cab = NULL;
    return g;
}

ADJACENCIA *criaAdj(int v, int peso)
{
    ADJACENCIA *temp = (ADJACENCIA *)malloc(sizeof(ADJACENCIA));
    temp->vertice = v;
    temp->peso = peso;
    temp->prox = NULL;
    return temp;
}

ADJACENCIA *inseriListAdj(ADJACENCIA *adj, int vi, int vf, TIPOPESO p)
{
    ADJACENCIA *ant = adj;
    ADJACENCIA *atual = adj;
    int control = 0;

    ADJACENCIA *novo = criaAdj(vf, p);

    while (atual != NULL && atual->vertice < vf)
    {
        ant = atual;
        atual = atual->prox;
        control = 1;
    }
    if (ant == NULL && control == 0)
    {
        novo->prox = atual;
        return novo;
    }
    else if (control == 0)
    {
        novo->prox = atual;
        return novo;
    }
    else
    {
        novo->prox = atual;
        ant->prox = novo;
    }

    return adj;
}

bool criaAresta(GRAFO *gr, int vi, int vf, TIPOPESO p)
{
    if (!gr)
        return (false);
    if ((vf < 0) || (vf >= gr->vertices))
        return (false);
    if ((vi < 0) || (vi >= gr->vertices))
        return (false);

    gr->adj[vi].cab = inseriListAdj(gr->adj[vi].cab, vi, vf, p);
    gr->arestas++;
    return (true);
}

void imprime(GRAFO *gr)
{
    printf("Vertices: %d. Arestas: %d, \n", gr->vertices, gr->arestas);

    for (int i = START; i < gr->vertices; i++)
    {
        printf("v%d: ", i);
        ADJACENCIA *ad = gr->adj[i].cab;
        while (ad)
        {
            printf("v%d(%d) ", ad->vertice, ad->peso);
            ad = ad->prox;
        }
        printf("\n");
    }
}

// ----------- DIJKSTRA ---------------------------

int *dijkstra(GRAFO *g, int s, int *p)
{
    int nv = g->vertices;
    int *dist = (int *)malloc(nv * sizeof(int));
    bool *aberto = (bool *)malloc(nv * sizeof(bool));

    for (int i = START; i < nv; i++)
    {
        dist[i] = INT_MAX;
        p[i] = -1;
        aberto[i] = true;
    }

    dist[s] = 0;

    while (true)
    {
        int u = -1, menor_dist = INT_MAX;

        for (int i = START; i < nv; i++)
        {
            if (aberto[i] && dist[i] < menor_dist)
            {
                menor_dist = dist[i];
                u = i;
            }
        }

        if (u == -1)
            break;

        aberto[u] = false;

        ADJACENCIA *adj = g->adj[u].cab;
        while (adj)
        {
            int v = adj->vertice;
            if (dist[v] > dist[u] + adj->peso)
            {
                dist[v] = dist[u] + adj->peso;
                p[v] = u;
            }
            adj = adj->prox;
        }
    }

    free(aberto);
    return dist;
}

// ----------- BELLMAN FORD ---------------------------

int *bellman_ford(GRAFO *g, int s, int *p)
{
    int nv = g->vertices;
    int *dist = (int *)malloc(nv * sizeof(int));

    for (int i = START; i < nv; i++)
    {
        dist[i] = INT_MAX;
        p[i] = -1;
    }

    dist[s] = 0;

    for (int i = 1; i < nv; i++)
    {
        bool alterado = false;
        for (int u = START; u < nv; u++)
        {
            ADJACENCIA *adj = g->adj[u].cab;
            while (adj)
            {
                int v = adj->vertice;
                if (dist[u] != INT_MAX && dist[v] > dist[u] + adj->peso)
                {
                    dist[v] = dist[u] + adj->peso;
                    p[v] = u;
                    alterado = true;
                }
                adj = adj->prox;
            }
        }
        if (!alterado)
            break;
    }

    return dist;
}

void caminho(GRAFO *g, int from, int to, int *p)
{
    if (from == to)
        printf("%d", from);
    else if (p[to] == -1)
        printf("Sem caminho de %d para %d", from, to);
    else
    {
        caminho(g, from, p[to], p);
        printf(" -> %d", to);
    }
}

int main()
{
    char nomearquivo[] = "teste.gr";
    GRAFO *gr;
    FILE *arq;
    char entrada[50], c;
    int qtdnos, arcs, n1, n2, peso, j = 0;
    int *p;

    arq = fopen(nomearquivo, "r");
    if (arq == NULL)
    {
        puts("Erro ao abrir o arquivo.");
        return 0;
    }

    while (fscanf(arq, "%c", &c) != EOF)
    {
        if (c == 'c')
        {
            fscanf(arq, "%[^\n]", entrada);
        }
        else if (c == 'p')
        {
            fscanf(arq, " sp %d %d", &qtdnos, &arcs);
            gr = criarGrafo(qtdnos + 1);
            puts("#vertices criados#...");
            p = (int *)malloc(gr->vertices * sizeof(int));
        }
        else if (c == 'a')
        {
            fscanf(arq, " %d %d %d", &n1, &n2, &peso);
            printf("a-%d (%d,%d)[%d]\n", j++, n1, n2, peso);
            criaAresta(gr, n1, n2, peso);
        }
    }

    puts("Arestas carregadas #...");
    imprime(gr);

    int find = 1;
    int no1 = 4, no2 = 2, no3 = 5;

    clock_t start, end;
    double cpu_time_used;

    start = clock();
    int *r = dijkstra(gr, find, p);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    if (r == NULL)
    {
        puts("Erro: Dijkstra retornou um ponteiro nulo.");
        return 1;
    }

    for (int i = START; i < gr->vertices; i++)
    {
        if (r[i] != INT_MAX)
            printf("D(v%d -> v%d) = %d\n", find, i, r[i]);
        else
            printf("D(v%d -> v%d) = INFINITO\n", find, i);
    }

    printf("Tempo total de execução: %f segundos\n", cpu_time_used);

    FILE *output = fopen("resultado.txt", "w");
    if (output == NULL)
    {
        puts("Erro ao criar arquivo de saída");
        return 1;
    }

    fprintf(output, "Distâncias e Caminhos a partir do vértice %d:\n", find);
    for (int i = START; i < gr->vertices; i++)
    {
        if (r[i] != INT_MAX)
            fprintf(output, "D(v%d -> v%d) = %d\n", find, i, r[i]);
        else
            fprintf(output, "D(v%d -> v%d) = INFINITO\n", find, i);
    }

    fprintf(output, "Tempo total de execução: %f segundos\n", cpu_time_used);
    fclose(output);

    caminho(gr, find, no1, p);
    printf("\n");
    caminho(gr, find, no2, p);
    printf("\n");
    caminho(gr, find, no3, p);
    printf("\n");

    return 0;
}
