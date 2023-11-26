#include <stdbool.h>
#include <string.h>

#define MAX_VERTICES 100

typedef struct {
  char label[25];
} Vertice;

// Estrutura do Grafo
typedef struct {
  Vertice vertices[MAX_VERTICES];
  int numero_vertices;
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
void adicionar_vertice(Grafo *grafo, const char *label);
void adicionar_aresta(Grafo *grafo, const char *origem, const char *destino);
void imprimir_matriz_adjacente(Grafo *grafo);
void imprimir_vertices(Grafo *grafo);
void imprimir_arestas(Grafo *grafo);

bool eh_conexo(Grafo *grafo);
bool isomorfo(Grafo *g1, Grafo *g2);

void imprimir_caminho(Lista *lista);
Lista* acha_caminho_bfs(Grafo *grafo, const char **origem, const char **destino);

bool bfs(int adj_matrix[MAX_VERTICES][MAX_VERTICES], int start, int end, int* path, int* path_length);

char*** pegar_arestas(const char *input, int *numPairs);
char** pegar_vertices(const char *input, int *numElements);
