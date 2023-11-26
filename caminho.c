#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "lib.h"
#include "cmd.h"

int main(int argc, char *argv[]) {
  char temp_char1, temp_char2;
  Grafo *grafo = (Grafo *) malloc(sizeof(Grafo));

  if (argc < 3) {
    printf("Usage: %s <arg1> <arg2> ... <argN>\n", argv[0]);
    return 1;
  }

  int numElements;
  char **vertices = pegar_vertices(argv[1], &numElements);

  for (int i = 0; i < numElements; ++i) {
    adicionar_vertice(grafo, vertices[i]);
  }

  free(vertices);

  int numPares;
  char ***arestas = pegar_arestas(argv[2], &numPares);

  for (int i = 0; i < numPares; ++i) {
    adicionar_aresta(grafo, arestas[i][0], arestas[i][1]);
  }

  for (int i = 0; i < numPares; ++i)
    free(arestas[i]);

  free(arestas);

  imprimir_vertices(grafo);
  imprimir_arestas(grafo);

  imprimir_matriz_adjacente(grafo);

  Lista* lista = acha_caminho_bfs(grafo, argv[3], argv[4]);

  printf("Caminho entre %s e %s: ", argv[3], argv[4]);
  if (lista == NULL) {
    printf("Caminho não encontrado\n");
    return 0;
  } else {
    while (lista != NULL) {
      printf("%s ", lista->vertice.label);
      lista = lista->proximo;
    }
    printf("\n");
  }

  return 0;
}
