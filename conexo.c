#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "lib.h"
#include "cmd.h"

void montar_grafo(Grafo *grafo, const char *vertices, const char *arestas);

int main(int argc, char *argv[]) {
  Grafo *grafo1 = (Grafo *) malloc(sizeof(Grafo));

  montar_grafo(grafo1, argv[1], argv[2]);

  if (eh_conexo(grafo1))
    printf("O grafo é conexo\n");
  else
    printf("O grafo não é conexo\n");
}

void montar_grafo(Grafo *grafo, const char *vertices_arg, const char *arestas_arg) {
  int numElements;
  char **vertices = pegar_vertices(vertices_arg, &numElements);

  for (int i = 0; i < numElements; ++i)
    adicionar_vertice(grafo, vertices[i]);

  free(vertices);

  int numPares;
  char ***arestas = pegar_arestas(arestas_arg, &numPares);

  for (int i = 0; i < numPares; ++i)
    adicionar_aresta(grafo, arestas[i][0], arestas[i][1]);

  for (int i = 0; i < numPares; ++i)
    free(arestas[i]);

  free(arestas);
}
