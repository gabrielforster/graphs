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
  char *vertices = pergar_vertices(argv[1], &numElements);

  for (int i = 0; i < numElements; ++i) {
    Vertice vertice = {vertices[i]};

    adicionar_vertice(grafo, vertice);
  }

  imprimir_vertices(grafo);

  free(vertices);

  int numPares;
  char **arestas = pegar_arestas(argv[2], &numPares);

  for (int i = 0; i < numPares; ++i) {
    Vertice origem = {arestas[i][0]};
    Vertice destino = {arestas[i][1]};
    adicionar_aresta(grafo, origem, destino);
  }

  for (int i = 0; i < numPares; ++i)
    free(arestas[i]);

  free(arestas);

  imprimir_arestas(grafo);

  imprimir_adjacencia_matriz(grafo);

  Vertice origem, destino;

  printf("Deseja saber o caminho entre quais vértices? ");
  scanf("%s %s", origem.label, destino.label);

  printf("Caminho entre %s e %s usando dfs: ", origem.label, destino.label);
  Lista *lista = acha_caminho(grafo, origem, destino);

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

  lista = acha_caminho_bfs(grafo, origem, destino);

  printf("Caminho entre %s e %s usando bfs: ", origem.label, destino.label);
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

  lista = acha_caminho_bfs_short(grafo, origem, destino);

  printf("Caminho entre %s e %s usando bfs_short: ", origem.label, destino.label);
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

  bool isomorfico = isomorfo(grafo, grafo);

  printf("Grafo é isomórfico a si mesmo? %s\n", isomorfico ? "Sim" : "Não");
  return 0;
}
