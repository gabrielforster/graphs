#include <stdbool.h>

#define MAX_VERTICES 100

typedef struct {
    int vertices;
    int arestas;
    int matriz[MAX_VERTICES][MAX_VERTICES];
} Grafo;

void inicializarGrafo(Grafo *grafo, int vertices);
void adicionarAresta(Grafo *grafo, int origem, int destino);
void imprimirGrafo(Grafo *grafo);
bool possuiCicloUtil(Grafo *grafo, int v, bool visitado[], int pai);
bool possuiCiclo(Grafo *grafo);
bool estaConectado(Grafo *grafo);
int** extractEdges(const char *input, int *numPairs);
int* extractVertices(const char *input, int *numElements);
