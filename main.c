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

  for (int i = 1; i < argc; ++i) {
    if (i==1) {
      int numElements;
      char *result = extractVertices(argv[i], &numElements);

      for (int i = 0; i < numElements; ++i) {
        Vertice vertice = {result[i]};

        adicionar_vertice(grafo, vertice);
      }

      imprimir_vertices(grafo);

      free(result);
    } else if (i==2) {
      int numPairs;
      char **result = extractEdges(argv[2], &numPairs);

      for (int i = 0; i < numPairs; ++i) {
        Vertice origem = {result[i][0]};
        Vertice destino = {result[i][1]};
        adicionar_aresta(grafo, origem, destino);
      }

      for (int i = 0; i < numPairs; ++i)
        free(result[i]);

      free(result);
    }
  }

  imprimir_arestas(grafo);

  imprimir_adjacencia_matriz(grafo);
  
  printf("Caminho entre A e C: ");
  Lista *lista = acha_caminho(grafo, (Vertice) {'A'}, (Vertice) {'C'});

  while (lista != NULL) {
    printf("%s ", lista->vertice.label);
    lista = lista->proximo;
  }
  printf("\n");

  return 0;
}
