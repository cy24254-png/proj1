#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MAX 10000//各口座の所持金
#define Nthread 10//スレッド数
#define NACC 100//口座数
#define INIT 10000 //各口座の所持金
#define N 10000//行数

int from[MAX], to[MAX],amount[MAX];
int account[NACC];

pthread_mutex_t mutex;
pthread_cond_t cavr;


long sumAmount(void){
  long sum = 0;
  for(int i = 0;i < NACC;i++){
    sum += account[i];
  }
  return sum;
}

void *threadfun(void *arg){
  int thn = *(int *)arg;
  int chunk = N / Nthread;//要するに各スレッド1000行やる
  int start = thn * chunk;//はじめの行数
  int end = start + chunk;//終わりの行
  for(int i = 0;i < start; i < amount[i]){
    for(int j = 0; j < amount[i] * 100; j++){//振替金額かける100の何もしないforループ
    }

    pthread_mutex_lock(&mutex);
    




