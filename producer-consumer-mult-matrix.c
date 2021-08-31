#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <semaphore.h>

#define LIMITE 2

struct buffer_data {
  int** A;
  int** B;
};

struct buffer_data* buffer;
sem_t empty;
sem_t full;
pthread_mutex_t mutex;
pthread_t* producers, * consumers;
int in = 0;
int out = 0;
int buffer_size = -1;
int matrix_size = -1;
int consumer_size = -1;
int producer_size = -1;

void* create_matrix_producer() {
  struct buffer_data aux;

  for (int i = 0; i < LIMITE; i++) {

    // inicializa a matriz
    int count = 1;
    aux.A = (int**)malloc(sizeof(int*) * matrix_size);
    aux.B = (int**)malloc(sizeof(int*) * matrix_size);
    for (int k = 0; k < matrix_size; k++) {
      aux.A[k] = (int*)malloc(sizeof(int) * matrix_size);
      aux.B[k] = (int*)malloc(sizeof(int) * matrix_size);
    }
    for (int i = 0; i < matrix_size; i++) {
      for (int j = 0; j < matrix_size; j++) {
        aux.A[i][j] = count;
        aux.B[i][j] = count;
        count++;
      }
    }

    sem_wait(&empty); // Se o semáforo tem um valor > 0, decremente 1, se não, bloqueia
    pthread_mutex_lock(&mutex);
    buffer[in] = aux;
    printf("Produtor insere em %d\n", in);
    in = (in + 1) % buffer_size;
    pthread_mutex_unlock(&mutex);
    sem_post(&full); // incremente o semáforo em 1

  }
}

void* multiply_matrix_consumer() {
  for (int i = 0; i < LIMITE; i++) {
    sem_wait(&full);
    pthread_mutex_lock(&mutex);

    struct buffer_data item = buffer[out];
    int C[matrix_size][matrix_size];

    for (int i = 0; i < matrix_size; i++) {
      for (int j = 0; j < matrix_size; j++) {
        int sum = 0;
        for (int k = 0; k < matrix_size; k++) {
          sum = sum + (item.B[i][k] * item.A[k][j]);
        }
        C[i][j] = sum;
      }
    }

    // printf("Matriz resultante\n");
    // for (int i = 0; i < matrix_size; i++) {
    //   for (int j = 0; j < matrix_size; j++) {
    //     printf("%i ", C[i][j]);
    //   }
    //   printf("\n");
    // }

    printf("Consumidor remove item de %d\n", out);
    out = (out + 1) % buffer_size;
    pthread_mutex_unlock(&mutex);
    sem_post(&empty);
  }

}

int main(int argc, char* argv[]) {

  int opt;
  while ((opt = getopt(argc, argv, "c:p:m:b:")) != -1) {
    switch (opt) {
    case 'm':
      matrix_size = strtoul(optarg, NULL, 0);
      break;
    case 'b':
      buffer_size = strtoul(optarg, NULL, 0);
      break;
    case 'c':
      consumer_size = strtoul(optarg, NULL, 0);
      break;
    case 'p':
      producer_size = strtoul(optarg, NULL, 0);
      break;
    default:
      printf("“unknown option : %c\n", opt);
    }
  }

  if (matrix_size == -1 || buffer_size == -1 || consumer_size == -1 || producer_size == -1) {
    printf("how to execute: program -p 5 -c 5 -b 3 -m 100 -t 4\n b => buffer size \n m => matrix size \n c => consumer size \n p => producer size \n");
    return 0;
  }

  producers = malloc(producer_size * sizeof(pthread_t));
  consumers = malloc(consumer_size * sizeof(pthread_t));
  pthread_mutex_init(&mutex, NULL);
  sem_init(&empty, 0, buffer_size);
  sem_init(&full, 0, 0);

  buffer = (struct buffer_data*)malloc(buffer_size * sizeof(struct buffer_data));

  for (int i = 0; i < producer_size; i++) {
    pthread_create(&producers[i], NULL, (void*)create_matrix_producer, NULL);
  }
  for (int i = 0; i < consumer_size; i++) {
    pthread_create(&consumers[i], NULL, (void*)multiply_matrix_consumer, NULL);
  }

  for (int i = 0; i < producer_size; i++) {
    pthread_join(producers[i], NULL);
  }
  for (int i = 0; i < consumer_size; i++) {
    pthread_join(consumers[i], NULL);
  }

  pthread_mutex_destroy(&mutex);
  sem_destroy(&empty);
  sem_destroy(&full);

  free(producers);
  free(consumers);

  return 0;
}