#include <stdio.h>
#include <pthread.h>
#include <time.h>

#define COUNT 1000
#define LOOP 10000

struct timespec ts[4][COUNT];
pthread_mutex_t mutexes[3];

void busy(){
  for(int i = 0;i < LOOP;i++){
  }
}

//スレッドの動き
void *fun(void *arg){
  int thn = (int)arg;
  int time_index = 0;

  for(int loop = 0;loop < 100;loop++){
    int acquired_count = 0;
    int acq[2];


    

    

    for(int i = 0;i < 10;i++){
      busy();
      clock_gettime(CLOCK_REALTIME, &ts[thn][time_index]);
      time_index++;
    }

    pthread_mutex_unlock(&mutexes[

  }
  return NULL;
}
