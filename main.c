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
        temp_char1 = result[i];

        adicionar_vertice(grafo, &temp_char1);
      }

      imprimir_vertices(grafo);

      free(result);
    } else if (i==2) {
      int numPairs;
      char **result = extractEdges(argv[2], &numPairs);

      for (int i = 0; i < numPairs; ++i) {
        // TODO FIX: pointer needs to be cleaned? not receiving correct value like A,B C,D
        // printf("%s %s\n", &result[i][0], &result[i][1]);
        temp_char1 = result[i][0];
        temp_char2 = result[i][1];
        adicionar_aresta(grafo, &temp_char1, &temp_char2);
      }

      for (int i = 0; i < numPairs; ++i)
        free(result[i]);

      free(result);
    }
  }

  imprimir_arestas(grafo);

  imprimir_adjacencia_matriz(grafo);

  // char** caminho = caminho_simples(grafo, "A", "D");
  //
  // printf("Caminho: ");
  //
  // for (int i = 0; i < grafo->arestas; ++i) {
  //   printf("%s ", caminho[i]);
  // }
  // printf("\n");

  return 0;
}
