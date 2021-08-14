
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// Let us create a global variable to change it in threads
int g = 0;

void* myThreadFun(void* vargp) {
  int* my_id = (int*)vargp;

  static int s = 0;
  ++s; ++g;
  printf("Thread ID: %d, Static: %d, Global: %d\n", *my_id, ++s, ++g);
}

int main() {
  int i;
  pthread_t tid;

  for (int i = 0; i < 3; i++) {
    pthread_create(&tid, NULL, myThreadFun, (void*)&tid);
  }

  pthread_exit(NULL);

  return 0;
}