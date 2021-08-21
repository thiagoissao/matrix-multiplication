#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>

#define handle_error_en(en, msg)				\
  do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

// B * A = C
int** A;
int** B;
int** C;
struct multiply_array_params {
  pthread_t thread_id;
  int size;
  int start;
  int end;
};

void init_data(int size) {
  A = (int**)malloc(sizeof(int*) * size);
  B = (int**)malloc(sizeof(int*) * size);
  C = (int**)malloc(sizeof(int*) * size);
  for (int k = 0; k < size; k++) {
    A[k] = (int*)malloc(sizeof(int) * size);
    B[k] = (int*)malloc(sizeof(int) * size);
    C[k] = (int*)malloc(sizeof(int) * size);
  }

  int count = 1;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      A[i][j] = count;
      B[i][j] = count;
      C[i][j] = count;
      count++;
    }
  }
}

static void* multiply_array(void* arg) {
  struct multiply_array_params* tinfo = arg;
  for (int i = tinfo->start; i < tinfo->end; i++) {
    for (int j = 0; j < tinfo->size; j++) {
      int sum = 0;
      for (int k = 0; k < tinfo->size; k++) {
        sum = sum + (B[i][k] * A[k][j]);
      }
      C[i][j] = sum;
    }
  }
}

int main(int argc, char* argv[]) {
  pthread_t* threads;
  struct multiply_array_params* tinfo;

  int n_threads = -1;
  int size = -1;
  int opt;
  while ((opt = getopt(argc, argv, "t:m:")) != -1) {
    switch (opt) {
    case 't':
      n_threads = strtoul(optarg, NULL, 0);
      break;
    case 'm':
      size = strtoul(optarg, NULL, 0);
      break;
    default:
      printf("“unknown option : %c\n", opt);
    }
  }

  if (size == -1 || n_threads == -1) {
    printf("how to execute: program -t 3 -m 100 \n t => threads quantity \n m => matrix size");
    return 0;
  }

  init_data(size);

  threads = (pthread_t*)malloc(n_threads * sizeof(pthread_t));
  tinfo = malloc(n_threads * sizeof(struct multiply_array_params));

  int range = (int)size / n_threads;

  for (int i = 0; i < n_threads; i++) {
    tinfo[i].thread_id = i + 1;
    tinfo[i].size = size;

    tinfo[i].end = range * (i + 1);
    tinfo[i].start = range * i;

    pthread_create(&threads[i], NULL, &multiply_array, &tinfo[i]);
  }

  for (int i = 0; i < n_threads; i++) {
    pthread_join(threads[i], NULL);
  }

  // for (int i = 0; i < size; i++) {
  //   for (int j = 0; j < size; j++) {
  //     printf("%i ", C[i][j]);
  //   }
  //   printf("\n");
  // }

  free(tinfo);
  free(A);
  free(B);
  free(C);
  free(threads);
  return 0;
}