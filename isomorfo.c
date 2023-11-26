#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "lib.h"
#include "cmd.h"

void montar_grafo(Grafo *grafo, const char *vertices, const char *arestas);

int main(int argc, char *argv[]) {
  Grafo *grafo1 = (Grafo *) malloc(sizeof(Grafo));
  Grafo *grafo2 = (Grafo *) malloc(sizeof(Grafo));

  montar_grafo(grafo1, argv[1], argv[2]);
  montar_grafo(grafo2, argv[3], argv[4]);

  imprimir_adjacencia_matriz(grafo1);
  imprimir_adjacencia_matriz(grafo2);

  if (isomorfo(grafo1, grafo2))
    printf("Os grafos são isomorfos\n");
  else
    printf("Os grafos não são isomorfos\n");

  free(grafo1);
  free(grafo2);

  return 0;
}

void montar_grafo(Grafo *grafo, const char *vertices_arg, const char *arestas_arg) {
  int numElements;
  char *vertices = pergar_vertices(vertices_arg, &numElements);

  for (int i = 0; i < numElements; ++i) {
    Vertice vertice = {vertices[i]};

    adicionar_vertice(grafo, vertice);
  }

  free(vertices);

  int numPares;
  char **arestas = pegar_arestas(arestas_arg, &numPares);

  for (int i = 0; i < numPares; ++i) {
    Vertice origem = {arestas[i][0]};
    Vertice destino = {arestas[i][1]};
    adicionar_aresta(grafo, origem, destino);
  }

  for (int i = 0; i < numPares; ++i)
    free(arestas[i]);

  free(arestas);

}
