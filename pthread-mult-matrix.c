#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int intType;
int n_threads = 2;

struct multiply_array_params {
  pthread_t thread_id;
  int** A;
  int** B;
  int** C;
  int size;
  int start;
  int end;
};

static void* multiply_array(void* arg) {
  struct multiply_array_params* tinfo = arg;
  for (int i = tinfo->start; i < tinfo->end; i++) {
    for (int j = 0; j < tinfo->size; j++) {
      int sum = 0;
      for (int k = 0; k < tinfo->size; k++) {
        sum = sum + (tinfo->B[i][k] * tinfo->A[k][j]);
      }
      printf("Sum: %i\n", sum);
      tinfo->C[i][j] = sum;
    }
  }
}

int main(int argc, char* argv[]) {
  int SIZE;
  pthread_t* threads;
  struct multiply_array_params* tinfo;

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

  threads = (pthread_t*)malloc(n_threads * sizeof(pthread_t));
  tinfo = calloc(n_threads, sizeof(struct multiply_array_params));

  for (int i = 0; i < n_threads; i++) {
    tinfo[i].A = A;
    tinfo[i].B = B;
    tinfo[i].C = C;
    tinfo[i].thread_id = i;
    tinfo[i].size = SIZE;

    //ajustar dps
    if (i == 0) {
      tinfo[i].end = 2;
      tinfo[i].start = 0;
    }
    else {
      tinfo[i].end = 4;
      tinfo[i].start = 2;
    }


    pthread_create(&threads[i], NULL, &multiply_array, &tinfo[i]);
  }

  for (int i = 0; i < n_threads; i++) {
    pthread_join(threads[i], NULL);
  }

  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      printf("%i ", C[i][j]);
    }
    printf("\n");
  }

  return 0;
}