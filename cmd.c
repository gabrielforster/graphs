#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int** extractEdges(const char *input, int *numPairs) {
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

  int **matrix = (int **)malloc(count * sizeof(int *));
  for (int i = 0; i < count; ++i) {
    matrix[i] = (int *)malloc(2 * sizeof(int));
  }

  count = 0;
  for (int i = 0; i < len; ++i) {
    if (input[i] == '(') {
      int j = i + 1;
      int k = 0;
      while (j < len && input[j] != ')') {
        if (input[j] >= '0' && input[j] <= '9') {
          matrix[count][k] = strtol(&input[j], NULL, 10);
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

  *numPairs = count;

  return matrix;
}

int* extractVertices(const char *input, int *numElements) {
  char *cleanedInput = strdup(input + 1);
  cleanedInput[strlen(cleanedInput) - 1] = '\0';

  *numElements = 1;
  for (int i = 0; input[i] != '\0'; ++i) {
    if (input[i] == ',') {
      (*numElements)++;
    }
  }

  int *result = (int *)malloc(*numElements * sizeof(int));

  int currentIndex = 0;
  char *token = strtok((char *)cleanedInput, ",");
  while (token != NULL) {
    printf("token -> %s\n", token);
    result[currentIndex] = atoi(token);
    currentIndex++;
    token = strtok(NULL, ",");
  }

  return result;
}
