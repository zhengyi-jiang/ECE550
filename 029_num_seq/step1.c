#include <stdio.h>
#include <stdlib.h>

int seq1 (int x){
  int b = x*4 - 3;
  return b;
}

void printSeq1Range(int low, int high){
  if(low >= high){
    printf("\n");
  }
  else{
    int N = high - low;
    int seq = 0;
    for(int i = 0; i<N; i++){
      seq = seq1(low+i);
      if(i==(N-1)){
	printf("%d\n",seq);
      }
      else{
	printf("%d,",seq);
      }
    }
  }
  return;
}


int main(void){
  int s1 = seq1(1);
  int s2 = seq1(100);
  int s3 = seq1(-100);
  printf("seq1(%d) = %d\n", 1, s1);
  printf("seq1(%d) = %d\n", 100, s2);
  printf("seq1(%d) = %d\n", -100, s3);

  printf("printSeq1Range(%d,%d)\n",1,1);
  printSeq1Range(1, 1);
  printf("printSeq1Range(%d,%d)\n",3,7);
  printSeq1Range(3, 7);
  printf("printSeq1Range(%d,%d)\n",-2,6);
  printSeq1Range(-2, 6);
  printf("printSeq1Range(%d,%d)\n",8,0);
  printSeq1Range(8, 0);
  printf("printSeq1Range(%d,%d)\n",0,1);
  printSeq1Range(0, 1);
  return 0;
}

//This file is for Step 1.
//You should do 
//  Step 1 (A): write seq1
//  Step 1 (B): write main to test seq1
//  Step 1 (C): write printSeq1Range
//  Step 1 (D): add test cases to main to test printSeq1Range
// 
// Be sure to #include any header files you need!

