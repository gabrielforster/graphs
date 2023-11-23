#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_VERTICES 100

typedef struct {
  char label[25];
} Vertice;

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

typedef struct lista {
  Vertice vertice;
  int indice;
  struct lista *proximo;
} Lista;

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
bool eh_conexo(Grafo *grafo);

void imprimir_caminho(Lista *lista);
Lista* acha_caminho(Grafo *grafo, Vertice origem, Vertice destino);
bool dfs(int adj_matrix[MAX_VERTICES][MAX_VERTICES], int start, int end, bool visited[MAX_VERTICES], int path[MAX_VERTICES], int *path_length);

void inicializar_grafo(Grafo *grafo) {
  grafo->arestas = 0;

  for (int i = 0; i < MAX_VERTICES; ++i) {
    for (int j = 0; j < MAX_VERTICES; ++j) {
      grafo->adjacencia_matriz[i][j] = 0;
    }
  }
}

void adicionar_vertice(Grafo *grafo, Vertice vertice) {
  strcpy(grafo->vertices[grafo->arestas].label, vertice.label);
  grafo->arestas++;
}

void adicionar_aresta(Grafo *grafo, Vertice origem, Vertice destino) {
  int indice_origem = -1;
  int indice_destino = -1;

  for (int i = 0; i < grafo->arestas; ++i) {
    if (strcmp(grafo->vertices[i].label, origem.label) == 0) {
      indice_origem = i;
    }

    if (strcmp(grafo->vertices[i].label, destino.label) == 0) {
      indice_destino = i;
    }
  }

  if (indice_origem == -1 || indice_destino == -1) {
    printf("Vértice não encontrado\n");
    return;
  }

  grafo->adjacencia_matriz[indice_origem][indice_destino] = 1;
  grafo->adjacencia_matriz[indice_destino][indice_origem] = 1;
}

void imprimir_grafo(Grafo *grafo) {
  printf("Grafo:\n");
  imprimir_vertices(grafo);
  imprimir_arestas(grafo);
  imprimir_adjacencias(grafo);
}

void imprimir_adjacencia_matriz(Grafo *grafo) {
  printf("  ");
  for (int i = 0; i < grafo->arestas; ++i) {
    printf("%s ", grafo->vertices[i].label);
  }

  printf("\n");

  for (int i = 0; i < grafo->arestas; ++i) {
    printf("%s ", grafo->vertices[i].label);
    for (int j = 0; j < grafo->arestas; ++j) {
      printf("%d ", grafo->adjacencia_matriz[i][j]);
    }
    printf("\n");
  }

  printf("\n");
}

void imprimir_vertices(Grafo *grafo) {
  printf("Vértices: ");

  for (int i = 0; i < grafo->arestas; ++i) {
    printf("%s ", grafo->vertices[i].label);
  }

  printf("\n");
}

void imprimir_arestas(Grafo *grafo) {
  printf("Arestas: ");

  for (int i = 0; i < grafo->arestas; ++i) {
    for (int j = i + 1; j < grafo->arestas; ++j) {
      if (grafo->adjacencia_matriz[i][j] == 1) {
        printf("(%s - %s) ", grafo->vertices[i].label, grafo->vertices[j].label);
      }
    }
  }

  printf("\n");
}

void imprimir_adjacencias(Grafo *grafo) {
  printf("Adjacências:\n");

  for (int i = 0; i < grafo->arestas; ++i) {
    printf("%s: ", grafo->vertices[i].label);
    for (int j = 0; j < grafo->arestas; ++j) {
      if (grafo->adjacencia_matriz[i][j] == 1) {
        printf("%s ", grafo->vertices[j].label);
      }
    }
    printf("\n");
  }
}

void imprimir_adjacencias_vertice(Grafo *grafo, Vertice vertice) {
  int indice_vertice = -1;

  for (int i = 0; i < grafo->arestas; ++i) {
    if (strcmp(grafo->vertices[i].label, vertice.label) == 0) {
      indice_vertice = i;
    }
  }

  if (indice_vertice != -1) {
    printf("Adjacências de %s:\n", vertice.label);
    for (int i = 0; i < grafo->arestas; ++i) {
      if (grafo->adjacencia_matriz[indice_vertice][i] == 1) {
        printf("%s ", grafo->vertices[i].label);
      }
    }
    printf("\n");
  }
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

void imprimir_caminho(Lista *caminho) {
  if (caminho == NULL) {
    printf("Caminho não encontrado\n");
    return;
  }

  while (caminho != NULL) {
    printf("%s ", caminho->vertice.label);
    caminho = caminho->proximo;
  }
  printf("\n");
}

Lista* acha_caminho(Grafo *grafo, Vertice origem, Vertice destino) {
  int indice_origem = -1;
  int indice_destino = -1;

  for (int i = 0; i < grafo->arestas; ++i) {
    if (strcmp(grafo->vertices[i].label, origem.label) == 0) {
      indice_origem = i;
    }

    if (strcmp(grafo->vertices[i].label, destino.label) == 0) {
      indice_destino = i;
    }
  }

  if (indice_origem == -1 || indice_destino == -1) {
    return NULL;
  }

  bool visited[MAX_VERTICES] = {false};
  int path_length = 0;
  int path[MAX_VERTICES];

  dfs(grafo->adjacencia_matriz, indice_origem, indice_destino, visited, path, &path_length);

  Lista *head, *tail, *aux;
  
  for (int i = 0; i < path_length; ++i) {
    aux = (Lista*) malloc(sizeof(Lista));
    aux->vertice = grafo->vertices[path[i]];
    aux->proximo = NULL;

    if (i == 0) {
      head = aux;
      tail = aux;
    } else {
      tail->proximo = aux;
      tail = aux;
    }
  }

  return head;
}

bool dfs(int adj_matrix[MAX_VERTICES][MAX_VERTICES], int start, int end, bool visited[MAX_VERTICES], int path[MAX_VERTICES], int *path_length) {
  visited[start] = true;
  path[(*path_length)++] = start;

  if (start == end) {
    return true;
  }

  for (int i = 0; i < MAX_VERTICES; ++i) {
    if (adj_matrix[start][i] && !visited[i]) {
      if (dfs(adj_matrix, i, end, visited, path, path_length)) {
        return true;
      }
    }
  }

  visited[start] = false;
  (*path_length)--;

  return false;
}
