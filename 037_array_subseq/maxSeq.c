#include <stdlib.h>
#include <stdio.h>

size_t maxSeq(int *array, size_t n){
  if((array == NULL)||(n == 0)){
    return 0;
  }
  else{
    size_t max= 1;
    size_t now = 1;
    for(size_t i=0; i<n; i++){
      if((array[i]<array[i+1])&&(i<(n-1))){
	now++;
      }
      else{
	if(max<now){
	  max=now;
	  now=1;
	}
	else{
	  now=1;
	}
      }
    }
    return max;
  }
}
