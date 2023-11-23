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

typedef struct pilha {
  Vertice vertice;
  int indice;
  struct pilha *proximo;
} Pilha;

typedef struct lista {
  Vertice vertice;
  int indice;
  struct lista *proximo;
} Lista;

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

void imprimir_caminho(Lista *lista);
Lista* acha_caminho(Grafo *grafo, Vertice origem, Vertice destino);
bool dfs(int adj_matrix[MAX_VERTICES][MAX_VERTICES], int start, int end, bool visited[MAX_VERTICES], int path[MAX_VERTICES], int *path_length);

char** extractEdges(const char *input, int *numPairs);
char* extractVertices(const char *input, int *numElements);
