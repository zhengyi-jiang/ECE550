#include<cstdlib>
#include<iostream>
#include<math.h>
#include"function.h"


int binarySearchForZero(Function<int, int> * f, int low, int high){
  if(low >= high-1){
    return low;
  }
  int mid = (low+high)/2;
  if(f->invoke(mid) > 0){
    return binarySearchForZero(f,  low,  mid);
  }
  else{
    return binarySearchForZero(f, mid, high);
  }
}
