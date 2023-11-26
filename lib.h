#include <stdbool.h>
#include <string.h>

#define MAX_VERTICES 100

typedef struct {
  char label[25];
} Vertice;

// Estrutura do Grafo
typedef struct {
  Vertice vertices[MAX_VERTICES];
  int arestas;
  int adjacencia_matriz[MAX_VERTICES][MAX_VERTICES];
} Grafo;

typedef struct lista {
  Vertice vertice;
  int indice;
  struct lista *proximo;
} Lista;

typedef struct node {
  int vertex;
  struct node* next;
} Node;

typedef struct fila {
  Node *primeiro;
  Node *ultimo;
} Fila;

// Protótipos de Funções
void inicializar_grafo(Grafo *grafo);
void adicionar_vertice(Grafo *grafo, Vertice vertice);
void adicionar_aresta(Grafo *grafo, Vertice origem, Vertice destino);
void imprimir_grafo(Grafo *grafo);
void imprimir_adjacencia_matriz(Grafo *grafo);
void imprimir_vertices(Grafo *grafo);
void imprimir_arestas(Grafo *grafo);
void imprimir_adjacencias(Grafo *grafo);
void imprimir_adjacencias_vertice(Grafo *grafo, Vertice vertice);

bool eh_conexo(Grafo *grafo);
bool isomorfo(Grafo *g1, Grafo *g2);

void imprimir_caminho(Lista *lista);
Lista* acha_caminho(Grafo *grafo, Vertice origem, Vertice destino);
Lista* acha_caminho_bfs(Grafo *grafo, Vertice origem, Vertice destino);
Lista* acha_caminho_bfs_short(Grafo *grafo, Vertice origem, Vertice destino);

bool dfs(int adj_matrix[MAX_VERTICES][MAX_VERTICES], int start, int end, bool visited[MAX_VERTICES], int path[MAX_VERTICES], int *path_length);
bool bfs(int adj_matrix[MAX_VERTICES][MAX_VERTICES], int start, int end, int* path, int* path_length);
bool bfs_shortest_path(int adj_matrix[MAX_VERTICES][MAX_VERTICES], int start, int end, int* path, int* path_length);

char** pegar_arestas(const char *input, int *numPairs);
char* pergar_vertices(const char *input, int *numElements);
