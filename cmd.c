#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define LABEL_SIZE 25

typedef struct Vertice {
  char label[LABEL_SIZE];
} Vertice;

char*** pegar_arestas(const char *input, int *num_pares) {
  int len = strlen(input);
  int count = 0;

  for (int i = 0; i < len; ++i) {
    if (input[i] == '(') {
      count++;
      while (i < len && input[i] != ')') {
        i++;
      }
    }
  }

  *num_pares = count;

  char ***result = (char ***)malloc(count * sizeof(char **));
  for (int i = 0; i < count; ++i) {
    result[i] = (char **)malloc(2 * sizeof(char *));
    for (int j = 0; j < 2; ++j) {
      result[i][j] = (char *)malloc(LABEL_SIZE * sizeof(char));
    }
  }

  count = 0;
  int i = 0;

  while (i < len) {
    if (input[i] == '(') {
      i++;
      int j = 0;
      while (input[i] != ',') {
        result[count][0][j++] = input[i++];
      }
      result[count][0][j] = '\0';
      i++;
      j = 0;
      while (input[i] != ')') {
        result[count][1][j++] = input[i++];
      }
      result[count][1][j] = '\0';
      count++;
    }
    i++;
  }

  return result;
}

char** pegar_vertices(const char *input, int *num_elementos) {
  char *entrada_limpa = strdup(input + 1);
  entrada_limpa[strlen(entrada_limpa) - 1] = '\0';

  *num_elementos = 1;
  for (int i = 0; entrada_limpa[i] != '\0'; ++i) {
    if (entrada_limpa[i] == ',') {
      (*num_elementos)++;
    }
  }

  char **result = (char **)malloc(*num_elementos * sizeof(char *));
  for (int i = 0; i < *num_elementos; ++i) {
    result[i] = (char *)malloc(LABEL_SIZE * sizeof(char));
  }

  int count = 0;

  char *token = strtok(entrada_limpa, ",");
  while (token != NULL) {
    strcpy(result[count], token);
    count++;

    token = strtok(NULL, ",");
  }

  free(entrada_limpa);

  return result;
}
