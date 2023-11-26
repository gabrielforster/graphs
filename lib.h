#include <stdbool.h>
#include <string.h>

#define MAX_VERTICES 100

typedef char Vertice[25];

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

void inicializar_grafo(Grafo *grafo);
void adicionar_vertice(Grafo *grafo, Vertice vertice);
void adicionar_aresta(Grafo *grafo, Vertice origem, Vertice destino);
void imprimir_grafo(Grafo *grafo);
void imprimir_adjacencia_matriz(Grafo *grafo);
void imprimir_vertices(Grafo *grafo);
void imprimir_arestas(Grafo *grafo);
void imprimir_adjacencias(Grafo *grafo);
void imprimir_adjacencias_vertice(Grafo *grafo, Vertice vertice);
void imprimir_adjacencias_vertice_indice(Grafo *grafo, int indice);
char** caminho_simples(Grafo *grafo, Vertice origem, Vertice destino);
int* trajeto(Grafo *grafo, Vertice origem, Vertice destino);
bool eh_conexo(Grafo *grafo);

char** extractEdges(const char *input, int *numPairs);
char* extractVertices(const char *input, int *numElements);
