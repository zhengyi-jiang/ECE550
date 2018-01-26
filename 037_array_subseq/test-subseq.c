#include <stdlib.h>
#include <stdio.h>

size_t maxSeq(int *array, size_t n);

void test(int tarray[], size_t n, size_t correct){
  if(maxSeq(tarray,n) == correct){
    printf("Y");
    return;
  }
  else{
    printf("\nN\n");
    exit(EXIT_FAILURE);
  }
}

int main(void){
  int array[]={1,2,3,4};
  test(array,4,4);
  int array1[]={1,2,3};
  test(array1,3,3);
  int array2[]={-1,-2,-3,1,2,3,4};
  test(array2,7,5);
  int array3[]={-1,-2,-3,-9,-7,-5,-3,-1,1,3,1,2,3,4,5,6};
  test(array3,16,7);
  test(NULL,0,0);
  int array4[]={-1,-2,-3,-11,-9,-7,-5,-3,-1,1,2,3,4,5,6};
  test(array4,15,12);
  int array5[]={-1,-2,-3,-9,-7,-5,-3,-1,1,2,3,4,5,6,7};
  test(array5,15,12);
  int array6[]={1,1,2,2,3,3,3,4,4,4,4,5,6,7,8};
  test(array6,15,5);
  int array7[]={0,0,0,0,1,3,4,0,1,-1,2};
  test(array7,11,4);
  int array8[]={1,1000,2,200,300,423,588,123,0,-234,-3,0,64,7};
  test(array8,14,5);
  int array9[]={1,1000,2,200,300,423,588,123,0,-234,-3,0,64,7};
  test(array9,0,0);
  int array10[]={1,2,-1294967293,1294967294,1294967295};
  test(array10,5,3); 
 
 
  return 0;
}
