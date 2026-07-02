#include <stdio.h>

int main(void){
  long long sum = 0;
  for (int i = 0;i <= 1000000000;i++){
    sum = sum + i;
    
  }
  printf("sum = %lld\n",sum);
  return 0;


}
