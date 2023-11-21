#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "lib.h"
#include "cmd.h"

int main(int argc, char *argv[]) {
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
        // TODO FIX: receiving wrong value -> ABCDE -> BCDE -> CDE -> DE -> E
        adicionar_vertice(grafo, &result[i]);
        // printf("%c\n", result[i]);
        // imprimir_vertices(grafo);
        // printf("---");
      }

      free(result);
    } else if (i==2) {
      int numPairs;
      char **result = extractEdges(argv[2], &numPairs);

      for (int i = 0; i < numPairs; ++i) {
        // TODO FIX: pointer needs to be cleaned? not receiving correct value like A,B C,D
        // printf("%s %s\n", &result[i][0], &result[i][1]);
        adicionar_aresta(grafo, &result[i][0], &result[i][1]);
      }

      for (int i = 0; i < numPairs; ++i)
        free(result[i]);

      free(result);
    }
  }

  imprimir_adjacencia_matriz(grafo);

  return 0;
}
