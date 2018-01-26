#include <stdio.h>
#include <stdlib.h>

int seq2 (int x){
  int y = x*x+3*x+1;
  return y;
}

int sumSeq2(int low, int high){
  if(low >= high){
    return 0;
  }
  else{
    int N = high - low;
    int seq = 0;
    for(int i = 0; i<N; i++){
      seq = seq + seq2(low+i);
    }
    return seq;
  }
}

int main(void){
  int s1 = seq2(1);
  int s2 = seq2(100);
  int s3 = seq2(-100);
  printf("seq2(%d) = %d\n", 1, s1);
  printf("seq2(%d) = %d\n", 100, s2);
  printf("seq2(%d) = %d\n", -100, s3);

  printf("sumSeq2(%d, %d) = %d\n",1,1,sumSeq2(1,1));
  printf("sumSeq2(%d, %d) = %d\n",3,7,sumSeq2(3,7));
  printf("sumSeq2(%d, %d) = %d\n",-2,6,sumSeq2(-2,6));
  printf("sumSeq2(%d, %d) = %d\n",8,0,sumSeq2(8,0));
  printf("sumSeq2(%d, %d) = %d\n",1,0,sumSeq2(1,0));
  printf("sumSeq2(%d, %d) = %d\n",0,1,sumSeq2(0,1));
  printf("sumSeq2(%d, %d) = %d\n",0,0,sumSeq2(0,0));
  return 0;
}
