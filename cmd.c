#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

char** extractEdges(const char *input, int *numPairs) {
  int len = strlen(input);
  int count = 0;

  // Count the number of pairs to allocate memory for the matrix
  for (int i = 0; i < len; ++i) {
    if (input[i] == '(') {
      count++;
      while (i < len && input[i] != ')') {
        i++;
      }
    }
  }

  // Allocate memory for the matrix
  char **matrix = (char **)malloc(count * sizeof(char *));
  for (int i = 0; i < count; ++i) {
    matrix[i] = (char *)malloc(2 * sizeof(char));  // Assuming each element is a single character
  }

  // Extract elements and populate the matrix
  count = 0;
  for (int i = 0; i < len; ++i) {
    if (input[i] == '(') {
      int j = i + 1;
      // Find the corresponding ")"
      int k = 0;
      while (j < len && input[j] != ')') {
        // Store the characters in the matrix
        if ((input[j] >= '0' && input[j] <= '9') || (input[j] >= 'a' && input[j] <= 'z') || (input[j] >= 'A' && input[j] <= 'Z')) {
          matrix[count][k] = input[j];
          k++;
          // Move the index to the next non-alphanumeric character
          while (j < len && (input[j] == ',' || input[j] == ' ')) {
            j++;
          }
        }
        j++;
      }
      count++;
    }
  }

  // Set the number of pairs
  *numPairs = count;

  return matrix;
}

char* extractVertices(const char *input, int *numElements) {
  // Remove the first and last characters (curly braces)
  char *cleanedInput = strdup(input + 1);
  cleanedInput[strlen(cleanedInput) - 1] = '\0';

  // Count the number of elements
  *numElements = 1;
  for (int i = 0; cleanedInput[i] != '\0'; ++i) {
    if (cleanedInput[i] == ',') {
      (*numElements)++;
    }
  }

  // Allocate memory for the character array
  char *result = (char *)malloc(*numElements * sizeof(char));

  // Extract elements and populate the array
  int currentIndex = 0;
  char *token = strtok(cleanedInput, ",");
  while (token != NULL) {
    result[currentIndex++] = token[0];  // Assuming each element is a single character
    token = strtok(NULL, ",");
  }

  // Free memory for the cleaned input
  free(cleanedInput);

  return result;
}
