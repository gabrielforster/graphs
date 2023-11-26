#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

char** pegar_arestas(const char *input, int *num_pares) {
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

  char **matrix = (char **)malloc(count * sizeof(char *));
  for (int i = 0; i < count; ++i) {
    matrix[i] = (char *)malloc(2 * sizeof(char));
  }

  count = 0;
  for (int i = 0; i < len; ++i) {
    if (input[i] == '(') {
      int j = i + 1;
      int k = 0;
      while (j < len && input[j] != ')') {
        if ((input[j] >= '0' && input[j] <= '9') || (input[j] >= 'a' && input[j] <= 'z') || (input[j] >= 'A' && input[j] <= 'Z')) {
          matrix[count][k] = input[j];
          k++;
          while (j < len && (input[j] == ',' || input[j] == ' ')) {
            j++;
          }
        }
        j++;
      }
      count++;
    }
  }

  *num_pares = count;

  return matrix;
}

char* pergar_vertices(const char *input, int *num_elementos) {
  char *entrada_limpa = strdup(input + 1);
  entrada_limpa[strlen(entrada_limpa) - 1] = '\0';

  *num_elementos = 1;
  for (int i = 0; entrada_limpa[i] != '\0'; ++i) {
    if (entrada_limpa[i] == ',') {
      (*num_elementos)++;
    }
  }

  char *result = (char *)malloc(*num_elementos * sizeof(char));

  int currentIndex = 0;
  char *token = strtok(entrada_limpa, ",");
  while (token != NULL) {
    result[currentIndex++] = token[0];
    token = strtok(NULL, ",");
  }

  free(entrada_limpa);

  return result;
}
