#include <stdbool.h>

#define MAX_VERTICES 100

typedef struct {
    int vertices;
    int arestas;
    int matriz[MAX_VERTICES][MAX_VERTICES];
} Grafo;

bool eh_isomorfo(Grafo *g1, Grafo *g2);

bool eh_isomorfo(Grafo *g1, Grafo *g2) {
  return true;
}
