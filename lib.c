#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_VERTICES 100

typedef struct {
  char label[25];
} Vertice;

typedef struct {
  Vertice vertices[MAX_VERTICES];
  int numero_vertices;
  int matriz_adjacente[MAX_VERTICES][MAX_VERTICES];
} Grafo;

typedef struct lista {
  Vertice vertice;
  int indice;
  struct lista *proximo;
} Lista;

typedef struct node {
  int vertice;
  struct node* proximo;
} Node;

typedef struct {
  Node* topo;
} Pilha;

typedef struct fila {
  Node *primeiro;
  Node *ultimo;
} Fila;

void push(Pilha *pilha, int vertice);
int pop(Pilha *pilha);

void push(Pilha *pilha, int vertice) {
  Node* novo = (Node*)malloc(sizeof(Node));
  novo->vertice = vertice;
  novo->proximo = pilha->topo;
  pilha->topo = novo;
}

int pop(Pilha *pilha) {
  if (pilha->topo == NULL) {
    return -1; // Pilha vazia
  }

  int vertice = pilha->topo->vertice;
  Node* temp = pilha->topo;

  pilha->topo = pilha->topo->proximo;

  free(temp);
  return vertice;
}

void inicia_fila(Fila *fila) {
  fila->primeiro = fila->ultimo = NULL;
}

void enqueue(Fila* fila, int vertice) {
  Node* newNode = (Node*)malloc(sizeof(Node));
  newNode->vertice = vertice;
  newNode->proximo = NULL;

  if (fila->ultimo == NULL) {
    fila->primeiro = fila->ultimo = newNode;
  } else {
    fila->ultimo->proximo = newNode;
    fila->ultimo = newNode;
  }
}

int dequeue(Fila* fila) {
  if (fila->primeiro == NULL) {
    return -1; // Empty queue
  }

  int vertice = fila->primeiro->vertice;
  Node* temp = fila->primeiro;

  fila->primeiro = fila->primeiro->proximo;

  if (fila->primeiro == NULL) {
    fila->ultimo = NULL;
  }

  free(temp);
  return vertice;
}

bool bfs(int adj_matrix[MAX_VERTICES][MAX_VERTICES], int start, int end, int* path, int* path_length) {
  bool visited[MAX_VERTICES] = {false};
  Fila fila;
  inicia_fila(&fila);

  visited[start] = true;
  enqueue(&fila, start);

  while (fila.primeiro != NULL) {
    int current = dequeue(&fila);
    path[(*path_length)++] = current;

    if (current == end) {
      return true;
    }

    for (int i = 0; i < MAX_VERTICES; ++i) {
      if (adj_matrix[current][i] && !visited[i]) {
        visited[i] = true;
        enqueue(&fila, i);
      }
    }
  }

  return false; // No path found
}

// Protótipos de Funções
void inicializar_grafo(Grafo *grafo);
void adicionar_vertice(Grafo *grafo, const char *label);
void adicionar_aresta(Grafo *grafo, const char *origem, const char *destino);
void imprimir_matriz_adjacente(Grafo *grafo);
void imprimir_vertices(Grafo *grafo);
void imprimir_arestas(Grafo *grafo);
bool eh_conexo(Grafo *grafo);
bool isomorfo(Grafo *g1, Grafo *g2);

void imprimir_caminho(Lista *lista);
Lista* acha_caminho_bfs(Grafo *grafo, const char **origem, const char **destino);


void inicializar_grafo(Grafo *grafo) {
  grafo->numero_vertices = 0;

  for (int i = 0; i < MAX_VERTICES; ++i) {
    for (int j = 0; j < MAX_VERTICES; ++j) {
      grafo->matriz_adjacente[i][j] = 0;
    }
  }
}

void adicionar_vertice(Grafo *grafo, const char *label) {
  strcpy(grafo->vertices[grafo->numero_vertices].label, label);

  grafo->numero_vertices++;
}

void adicionar_aresta(Grafo *grafo, const char *origem, const char *destino) {
  int indice_origem = -1;
  int indice_destino = -1;

  for (int i = 0; i < grafo->numero_vertices; ++i) {
    if (strcmp(grafo->vertices[i].label, origem) == 0)
      indice_origem = i;

    if (strcmp(grafo->vertices[i].label, destino) == 0)
      indice_destino = i;
  }

  if (indice_origem == -1 || indice_destino == -1) {
    printf("Vértice não encontrado\n");
    return;
  }

  grafo->matriz_adjacente[indice_origem][indice_destino] = 1;
  grafo->matriz_adjacente[indice_destino][indice_origem] = 1;
}

void imprimir_matriz_adjacente(Grafo *grafo) {
  printf("\t");
  for (int i = 0; i < grafo->numero_vertices; ++i) {
    printf("%s\t", grafo->vertices[i].label);
  }

  printf("\n");

  for (int i = 0; i < grafo->numero_vertices; ++i) {
    printf("%s\t", grafo->vertices[i].label);

    for (int j = 0; j < grafo->numero_vertices; ++j) {
      printf("%d\t", grafo->matriz_adjacente[i][j]);
    }
    printf("\n");
  }

  printf("\n");
}

void imprimir_vertices(Grafo *grafo) {
  printf("Vértices: ");

  for (int i = 0; i < grafo->numero_vertices; ++i) {
    printf("%s ", grafo->vertices[i].label);
  }

  printf("\n");
}

void imprimir_arestas(Grafo *grafo) {
  printf("Arestas: ");

  for (int i = 0; i < grafo->numero_vertices; ++i) {
    for (int j = i + 1; j < grafo->numero_vertices; ++j) {
      if (grafo->matriz_adjacente[i][j] == 1) {
        printf("(%s - %s) ", grafo->vertices[i].label, grafo->vertices[j].label);
      }
    }
  }

  printf("\n");
}

bool eh_conexo(Grafo *grafo) {
  int* visitados = (int*) malloc(grafo->numero_vertices * sizeof(int));
  Pilha* pilha = (Pilha*) malloc(grafo->numero_vertices * sizeof(Pilha));

  for (int i = 0; i < grafo->numero_vertices; ++i) {
    visitados[i] = 0;
  }

  int topo = 0;
  push(pilha, topo);
  visitados[0] = 1;

  while (topo != -1) {
    int vertice = pop(pilha);
    topo = vertice;

    for (int i = 0; i < grafo->numero_vertices; ++i) {
      if (grafo->matriz_adjacente[vertice][i] == 1 && visitados[i] == 0) {
        push(pilha, i);
        visitados[i] = 1;
      }
    }
  }

  for (int i = 0; i < grafo->numero_vertices; ++i) {
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

bool isomorfo(Grafo *g1, Grafo *g2) {
  if (g1->numero_vertices != g2->numero_vertices) {
    return false;
  }

  for (int i = 0; i < g1->numero_vertices; i++) {
    for (int j = 0; j < g1->numero_vertices; j++) {
      if (g1->matriz_adjacente[i][j] != g2->matriz_adjacente[i][j]) {
        return false;
      }
    }
  }

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

Lista* acha_caminho_bfs(Grafo *grafo, const char **origem, const char **destino) {
  int indice_origem = -1;
  int indice_destino = -1;

  for (int i = 0; i < grafo->numero_vertices; ++i) {
    if (strcmp(grafo->vertices[i].label, origem) == 0) {
      indice_origem = i;
    }

    if (strcmp(grafo->vertices[i].label, destino) == 0) {

      indice_destino = i;
    }
  }

  if (indice_origem == -1 || indice_destino == -1) {
    return NULL;
  }

  bool visited[MAX_VERTICES] = {false};
  int path_length = 0;
  int path[MAX_VERTICES];

  bfs(grafo->matriz_adjacente, indice_origem, indice_destino, path, &path_length);

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
