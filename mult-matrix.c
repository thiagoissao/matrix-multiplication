#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[]) {
  int SIZE;

  if (argc < 2) {
    printf("Array size missed");
    return 0;
  }

  if (argc >= 2) {
    char* param = argv[1];
    SIZE = atoi(param);
  }

  // B * A = C
  int* B[SIZE];
  int* A[SIZE];
  int* C[SIZE];

  for (int i = 0; i < SIZE; i++) {
    B[i] = (int*)malloc(SIZE * sizeof(int));
    A[i] = (int*)malloc(SIZE * sizeof(int));
    C[i] = (int*)malloc(SIZE * sizeof(int));
  }

  int count = 0;
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      count += 1;
      A[i][j] = count;
      B[i][j] = count;
    }
  }


  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      int sum = 0;
      for (int k = 0; k < SIZE; k++) {
        sum = sum + (B[i][k] * A[k][j]);
      }
      C[i][j] = sum;
    }
  }

  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      printf("%i ", C[i][j]);
    }
    printf("\n");
  }

  return 0;
}