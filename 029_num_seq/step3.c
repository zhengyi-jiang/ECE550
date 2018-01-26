#include <stdio.h>
#include <stdlib.h>

int seq3 (int x, int y){
  int z = 2*y+(x*(y-3));
  return z;
}

int countEvenInSeq3Range (int xLow, int xHi, int yLow, int yHi){
  if(xLow >= xHi || yLow >= yHi){
    return 0;
  }
  else{
    size_t Nx = xHi - xLow;
    size_t Ny = yHi - yLow;
    int e = 0;
    for(int i=0 ; i < Nx ; i++){
      for(int j=0 ; j < Ny ; j++){
	if (seq3(i,j)%2 == 0){
	  e++;
	}
	else{}
      }
    }
    return e;
  }
}

int main(void){
  printf("seq3(%d, %d) = %d\n",1,1,seq3(1,1));
  printf("seq3(%d, %d) = %d\n",2,8,seq3(2,8));
  printf("seq3(%d, %d) = %d\n",4,0,seq3(4,0));
  printf("seq3(%d, %d) = %d\n",-2,1,seq3(-2,1));
  printf("seq3(%d, %d) = %d\n",-8,100,seq3(-8,100));

  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",1,0,0,1,countEvenInSeq3Range(1,0,0,1));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",1,0,1,0,countEvenInSeq3Range(1,0,1,1));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",0,1,0,0,countEvenInSeq3Range(0,1,0,0));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",0,1,1,0,countEvenInSeq3Range(0,1,1,0));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",0,0,0,0,countEvenInSeq3Range(0,0,0,0));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",1,0,0,1,countEvenInSeq3Range(1,0,0,1));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",0,2,0,3,countEvenInSeq3Range(0,2,0,3));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",-5,5,-5,5,countEvenInSeq3Range(-5,5,-5,5));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",4,5,-3,1,countEvenInSeq3Range(4,5,-3,1));
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",-5,6,-5,6,countEvenInSeq3Range(-5,6,-5,6));  
 
  return 0;
}
  
  
			    






//This file is for Step 3.
//You should do 
//  Step 3 (A): write seq3
//  Step 3 (B): write main to test seq3
//  Step 3 (C): write countEvenInSeq3Range
//  Step 3 (D): add test cases to main to test countEvenInSeq3Range
// 
// Be sure to #include any header files you need!

