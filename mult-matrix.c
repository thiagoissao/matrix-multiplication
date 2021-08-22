#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char* argv[]) {
  int size = -1;
  int opt;
  while ((opt = getopt(argc, argv, "m:")) != -1) {
    switch (opt) {
    case 'm':
      size = strtoul(optarg, NULL, 0);
      break;
    default:
      printf("“unknown option : %c\n", opt);
    }
  }

  if (size == -1) {
    printf("how to execute: program -m 100 \n m => matrix size");
    return 0;
  }

  // B * A = C
  int* B[size];
  int* A[size];
  int* C[size];

  for (int i = 0; i < size; i++) {
    B[i] = (int*)malloc(size * sizeof(int));
    A[i] = (int*)malloc(size * sizeof(int));
    C[i] = (int*)malloc(size * sizeof(int));
  }

  int count = 0;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      count += 1;
      A[i][j] = count;
      B[i][j] = count;
    }
  }

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      int sum = 0;
      for (int k = 0; k < size; k++) {
        sum = sum + (B[i][k] * A[k][j]);
      }
      C[i][j] = sum;
    }
  }

  // printf("size: %i", size);
  // for (int i = 0; i < size; i++) {
  //   for (int j = 0; j < size; j++) {
  //     printf("%i ", C[i][j]);
  //   }
  //   printf("\n");
  // }

  return 0;
}