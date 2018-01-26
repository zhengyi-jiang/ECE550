#include <cstdlib>
#include <stdio.h>
#include <math.h>
#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high);

void check(Function<int,int> * f, int low, int high, int expected_ans, const char * mesg){
  int max = 1;
  if(high > low){
    max = log2(high - low) + 1;
  }
  printf("%d\n\n",max);
  CountedIntFn* CF = new CountedIntFn(max ,f,mesg);
  int ans = binarySearchForZero(CF, low, high);
  if(expected_ans != ans){
    fprintf(stderr,"ans not right!: %s :%d what's right:%d\n",mesg, ans, expected_ans);
    exit(EXIT_FAILURE);
  }
}



int main(){
  PlusoneFn *f1 = new PlusoneFn();

  check(f1, -2, 2, -1, "1");
  check(f1, -4, -2, -3, "1");
  check(f1, -2, -2, -2, "2");
  check(f1, -2, -1, -2, "3");
  check(f1, -4, -2, -3, "4");
  check(f1, -2, 0, -1, "5");
  check(f1, -8, 100, -1, "6");
  check(f1, -1, -1, -1, "7");
  check(f1, -1, 100, -1, "8");
  check(f1, -100, 120, -1, "9");
  check(f1, 1, 60, 1, "10");
  
  


  
  return 0;
  
  
}
