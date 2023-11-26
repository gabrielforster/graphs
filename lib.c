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
  int arestas;
  int adjacencia_matriz[MAX_VERTICES][MAX_VERTICES];
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

typedef struct {
  int data[MAX_VERTICES];
  int front, rear;
} Queue;

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

void init_queue(Queue* q) {
  q->front = q->rear = -1;
}

void enqueue2(Queue *q, int value) {
  if (q->rear == MAX_VERTICES - 1) {
    printf("Queue is full.\n");
    return;
  }

  if (q->front == -1) {
    q->front = 0;
  }

  q->rear++;
  q->data[q->rear] = value;
}

int dequeue2(Queue *q) {
  if (q->front == -1) {
    printf("Queue is empty.\n");
    return -1;
  }

  int value = q->data[q->front];

  if (q->front == q->rear) {
    q->front = -1;
    q->rear = -1;
  } else {
    q->front++;
  }

  return value;
}

bool bfs_shortest_path(int adj_matrix[MAX_VERTICES][MAX_VERTICES], int start, int end, int* path, int* path_length) {
  bool visited[MAX_VERTICES] = {false};
  int distance[MAX_VERTICES] = {0};
  Queue q;
  init_queue(&q);

  visited[start] = true;
  enqueue2(&q, start);

  while (q.front != -1) {
    int current = dequeue2(&q);
    path[(*path_length)++] = current;

    if (current == end) {
      return true;
    }

    for (int i = 0; i < MAX_VERTICES; ++i) {
      if (adj_matrix[current][i] && !visited[i]) {
        visited[i] = true;
        distance[i] = distance[current] + 1;  // Update the distance
        enqueue2(&q, i);
      }
    }
  }

  return false; // No path found
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
void adicionar_vertice(Grafo *grafo, Vertice vertice);
void adicionar_aresta(Grafo *grafo, Vertice origem, Vertice destino);
void imprimir_grafo(Grafo *grafo);
void imprimir_adjacencia_matriz(Grafo *grafo);
void imprimir_vertices(Grafo *grafo);
void imprimir_arestas(Grafo *grafo);
void imprimir_adjacencias(Grafo *grafo);
void imprimir_adjacencias_vertice(Grafo *grafo, Vertice vertice);
bool eh_conexo(Grafo *grafo);
bool isomorfo(Grafo *g1, Grafo *g2);

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
  Pilha* pilha = (Pilha*) malloc(grafo->arestas * sizeof(Pilha));

  for (int i = 0; i < grafo->arestas; ++i) {
    visitados[i] = 0;
  }

  int topo = 0;
  push(pilha, topo);
  visitados[0] = 1;

  while (topo != -1) {
    int vertice = pop(pilha);
    topo = vertice;

    for (int i = 0; i < grafo->arestas; ++i) {
      if (grafo->adjacencia_matriz[vertice][i] == 1 && visitados[i] == 0) {
        push(pilha, i);
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

bool isomorfo(Grafo *g1, Grafo *g2) {
  if (g1->arestas != g2->arestas) {
    return false;
  }

  for (int i = 0; i < g1->arestas; i++) {
    for (int j = 0; j < g1->arestas; j++) {
      if (g1->adjacencia_matriz[i][j] != g2->adjacencia_matriz[i][j]) {
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

Lista* acha_caminho_bfs(Grafo *grafo, Vertice origem, Vertice destino) {
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

  bfs(grafo->adjacencia_matriz, indice_origem, indice_destino, path, &path_length);

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
Lista* acha_caminho_bfs_short(Grafo *grafo, Vertice origem, Vertice destino) {
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

  bfs_shortest_path(grafo->adjacencia_matriz, indice_origem, indice_destino, path, &path_length);

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
