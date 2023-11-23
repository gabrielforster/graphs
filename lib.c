#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_VERTICES 100

typedef char Vertice[25];

// Estrutura do Grafo
typedef struct {
  Vertice vertices[MAX_VERTICES];
  int arestas;
  int adjacencia_matriz[MAX_VERTICES][MAX_VERTICES];
} Grafo;

typedef struct pilha {
  Vertice vertice;
  int indice;
  struct pilha *proximo;
} Pilha;

// Protótipos de Funções
void inicializar_grafo(Grafo *grafo);
void adicionar_vertice(Grafo *grafo, Vertice vertice);
void adicionar_aresta(Grafo *grafo, Vertice origem, Vertice destino);
void imprimir_grafo(Grafo *grafo);
void imprimir_adjacencia_matriz(Grafo *grafo);
void imprimir_vertices(Grafo *grafo);
void imprimir_arestas(Grafo *grafo);
void imprimir_adjacencias(Grafo *grafo);
void imprimir_adjacencias_vertice(Grafo *grafo, Vertice vertice);
void imprimir_adjacencias_vertice_indice(Grafo *grafo, int indice);
char** caminho_simples(Grafo *grafo, Vertice origem, Vertice destino);
int* trajeto(Grafo *grafo, Vertice origem, Vertice destino);
bool eh_conexo(Grafo *grafo);

void inicializar_grafo(Grafo *grafo) {
  grafo->arestas = 0;

  for (int i = 0; i < MAX_VERTICES; ++i) {
    for (int j = 0; j < MAX_VERTICES; ++j) {
      grafo->adjacencia_matriz[i][j] = 0;
    }
  }
}

void adicionar_vertice(Grafo *grafo, Vertice vertice) {
  strcpy(grafo->vertices[grafo->arestas], vertice);
  grafo->arestas++;
}

void adicionar_aresta(Grafo *grafo, Vertice origem, Vertice destino) {
  int indice_origem = -1;
  int indice_destino = -1;

  for (int i = 0; i < grafo->arestas; ++i) {
    if (*grafo->vertices[i] == *origem) {
      indice_origem = i;
    }

    if (*grafo->vertices[i] == *destino) {
      indice_destino = i;
    }
  }

  if (indice_origem != -1 && indice_destino != -1) {
    grafo->adjacencia_matriz[indice_origem][indice_destino] = 1;
    grafo->adjacencia_matriz[indice_destino][indice_origem] = 1;
  }
}

void imprimir_grafo(Grafo *grafo) {
  printf("Grafo:\n");
  imprimir_vertices(grafo);
  imprimir_arestas(grafo);
  imprimir_adjacencias(grafo);
}

void imprimir_adjacencia_matriz(Grafo *grafo) {
  printf("Matriz de Adjacência:\n");

  for (int i = 0; i < grafo->arestas; ++i) {
    for (int j = 0; j < grafo->arestas; ++j) {
      printf("%d ", grafo->adjacencia_matriz[i][j]);
    }
    printf("\n");
  }
}

void imprimir_vertices(Grafo *grafo) {
  printf("Vértices: ");

  for (int i = 0; i < grafo->arestas; ++i) {
    printf("%c ", *grafo->vertices[i]);
  }

  printf("\n");
}

void imprimir_arestas(Grafo *grafo) {
  printf("Arestas: ");

  for (int i = 0; i < grafo->arestas; ++i) {
    for (int j = i + 1; j < grafo->arestas; ++j) {
      if (grafo->adjacencia_matriz[i][j] == 1) {
        printf("(%s - %s) ", grafo->vertices[i], grafo->vertices[j]);
      }
    }
  }

  printf("\n");
}

void imprimir_adjacencias(Grafo *grafo) {
  printf("Adjacências:\n");

  for (int i = 0; i < grafo->arestas; ++i) {
    printf("%s: ", grafo->vertices[i]);
    for (int j = 0; j < grafo->arestas; ++j) {
      if (grafo->adjacencia_matriz[i][j] == 1) {
        printf("%s ", grafo->vertices[j]);
      }
    }
    printf("\n");
  }
}

void imprimir_adjacencias_vertice(Grafo *grafo, Vertice vertice) {
  int indice_vertice = -1;

  for (int i = 0; i < grafo->arestas; ++i) {
    if (strcmp(grafo->vertices[i], vertice) == 0) {
      indice_vertice = i;
    }
  }

  if (indice_vertice != -1) {
    printf("Adjacências de %s:\n", vertice);
    for (int i = 0; i < grafo->arestas; ++i) {
      if (grafo->adjacencia_matriz[indice_vertice][i] == 1) {
        printf("%s ", grafo->vertices[i]);
      }
    }
    printf("\n");
  }
}

void imprimir_adjacencias_vertice_indice(Grafo *grafo, int indice) {
  if (indice >= 0 && indice < grafo->arestas) {
    printf("Adjacências de %s:\n", grafo->vertices[indice]);
    for (int i = 0; i < grafo->arestas; ++i) {
      if (grafo->adjacencia_matriz[indice][i] == 1) {
        printf("%s ", grafo->vertices[i]);
      }
    }
    printf("\n");
  }
}

char** caminho_simples(Grafo *grafo, Vertice origem, Vertice destino) {
  int indice_origem = -1;
  int indice_destino = -1;

  for (int i = 0; i < grafo->arestas; ++i) {
    if (strcmp(grafo->vertices[i], origem) == 0) {
      indice_origem = i;
    }

    if (strcmp(grafo->vertices[i], destino) == 0) {
      indice_destino = i;
    }
  }

  printf("Origem: %d\n", indice_origem);
  printf("Destino: %d\n", indice_destino);

  printf("aa");
  if (indice_origem != -1 && indice_destino != -1) {
    printf("alocando");
    int* trajeto = (int*) malloc(grafo->arestas * sizeof(int));
    int* visitados = (int*) malloc(grafo->arestas * sizeof(int));
    int* pilha = (int*) malloc(grafo->arestas * sizeof(int));
    int topo = -1;

    for (int i = 0; i < grafo->arestas; ++i) {
      visitados[i] = 0;
    }

    topo++;
    pilha[topo] = indice_origem;
    visitados[indice_origem] = 1;

    while (topo != -1) {
      int vertice_atual = pilha[topo];
      topo--;

      for (int i = 0; i < grafo->arestas; ++i) {
        if (grafo->adjacencia_matriz[vertice_atual][i] == 1 && visitados[i] == 0) {
          topo++;
          pilha[topo] = i;
          visitados[i] = 1;
          trajeto[i] = vertice_atual;
        }
      }
    }

    if (visitados[indice_destino] == 1) {
      int* caminho = (int*) malloc(grafo->arestas * sizeof(int));
      int indice_caminho = 0;
      int vertice_atual = indice_destino;

      while (vertice_atual != indice_origem) {
        caminho[indice_caminho] = vertice_atual;
        indice_caminho++;
        vertice_atual = trajeto[vertice_atual];
      }

      printf("cheguei aq 1: ");

      caminho[indice_caminho] = indice_origem;
      indice_caminho++;

      char** caminho_simples = (char**) malloc(indice_caminho * sizeof(char*));

      printf("cheguei aq 2: ");

      for (int i = 0; i < indice_caminho; ++i) {
        caminho_simples[i] = (char*) malloc(25 * sizeof(char));
        strcpy(caminho_simples[i], grafo->vertices[caminho[indice_caminho - i - 1]]);
      }

      return caminho_simples;
    } else {
      return NULL;
    }
  }

  return NULL;
}

int* trajeto(Grafo *grafo, Vertice origem, Vertice destino) {
  int indice_origem = -1;
  int indice_destino = -1;

  for (int i = 0; i < grafo->arestas; ++i) {
    if (strcmp(grafo->vertices[i], origem) == 0) {
      indice_origem = i;
    }

    if (strcmp(grafo->vertices[i], destino) == 0) {
      indice_destino = i;
    }
  }

  if (indice_origem != -1 && indice_destino != -1) {
    int* trajeto = (int*) malloc(grafo->arestas * sizeof(int));
    int* visitados = (int*) malloc(grafo->arestas * sizeof(int));
    int* pilha = (int*) malloc(grafo->arestas * sizeof(int));
    int topo = -1;

    for (int i = 0; i < grafo->arestas; ++i) {
      visitados[i] = 0;
    }

    pilha[++topo] = indice_origem;
    visitados[indice_origem] = 1;

    while (topo != -1) {
      int vertice = pilha[topo--];
      trajeto[vertice] = 1;

      if (vertice == indice_destino) {
        break;
      }

      for (int i = 0; i < grafo->arestas; ++i) {
        if (grafo->adjacencia_matriz[vertice][i] == 1 && visitados[i] == 0) {
          pilha[++topo] = i;
          visitados[i] = 1;
        }
      }
    }

    free(visitados);
    free(pilha);

    return trajeto;
  }

  return NULL;
}

bool eh_conexo(Grafo *grafo) {
  int* visitados = (int*) malloc(grafo->arestas * sizeof(int));
  int* pilha = (int*) malloc(grafo->arestas * sizeof(int));
  int topo = -1;

  for (int i = 0; i < grafo->arestas; ++i) {
    visitados[i] = 0;
  }

  pilha[++topo] = 0;
  visitados[0] = 1;

  while (topo != -1) {
    int vertice = pilha[topo--];

    for (int i = 0; i < grafo->arestas; ++i) {
      if (grafo->adjacencia_matriz[vertice][i] == 1 && visitados[i] == 0) {
        pilha[++topo] = i;
        visitados[i] = 1;
      }
    }
  }

  for (int i = 0; i < grafo->arestas; ++i) {
    if (visitados[i] == 0) {
      free(visitados);
      free(pilha);
      return false;
    }
  }

  free(visitados);
  free(pilha);
  return true;
}
