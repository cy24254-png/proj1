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
    
    //3つのうち2つのmutexを獲得するまでループ
    while(acquired_count < 2){
      acquired_count = 0; // ループの最初で0リセットが必要
      for(int i = 0;i < 3;i++){
        if(pthread_mutex_trylock(&mutexes[i]) == 0){
          acq[acquired_count] = i;
          acquired_count++;
          if(acquired_count == 2) break;
        }
      }
      
      //1つ目が取れて2つ目が取れなかった場合、1つ目を解放してやり直す
      if(acquired_count == 1){
          pthread_mutex_unlock(&mutexes[acq[0]]);
      }
    }

    //クリティカルセクション
    for(int i = 0; i< 10; i++){
        busy();
        clock_gettime(CLOCK_REALTIME, &ts[thn][time_index]);
        time_index++;
    }

    //リソースの解放
    pthread_mutex_unlock(&mutexes[acq[0]]);
    pthread_mutex_unlock(&mutexes[acq[1]]);

    //処理B
    busy();

  }

  return NULL;
}

int main(){
  pthread_t th[4];
  struct timespec x;
  int thn, i;

  //mutexの初期化
  for(int m = 0; m < 3; m++){
    pthread_mutex_init(&mutexes[m], NULL);
  }

  clock_gettime(CLOCK_REALTIME, &x);
  long startt = x.tv_sec * 1000000000 + x.tv_nsec;

  for(thn = 0; thn < 4; thn++){
    pthread_create(&th[thn], NULL, fun, (void *)thn);
  }

  for(thn = 0; thn < 4; thn++){
    pthread_join(th[thn], NULL);
  }

  for(thn = 0; thn < 4; thn++){
    for(i = 0; i < COUNT; i++){
      long t = ts[thn][i].tv_sec * 1000000000 + ts[thn][i].tv_nsec;
      printf("%ld\t%d\n", t - startt, thn);
    }
  }
  return 0;
}