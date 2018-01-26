#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int count (int* n){
    int big = 0;
    int bl = 0;
    for (int z = 0 ; z <26 ;z++){
      if(n[z]>big){
	big = n[z];
	bl = z;
      }
    }//choose the highest rate
    return bl;
}//count the letter that shows up most frequently

    
int highF (FILE * f){
  int n =0;
  int c = 0;
  int l[26] = {0};
  while ((c = fgetc(f)) != EOF){
    if (isalpha(c)){
      c -= 'a';
      c %= 26;
      for (int j = 0; j <26; j++){
	if(c==j){
	  l[j]++;
	  n++;
	}
      }
    }//transfer letters to number
  }
  if(n==0){
    fprintf(stderr,"no letter\n");
    exit(EXIT_FAILURE);
  }
  int x = count(l);
  x %= 26;
  x -= 4;
  if (x<0){
    x += 26;
  }
  return x;
}//transfer letter into number and pass it to the func.count

int main (int argc, char **argv){
  if (argc != 2) {
    fprintf(stderr,"error\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  int key = highF(f);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  printf("%d\n",key);
  return EXIT_SUCCESS;
}
