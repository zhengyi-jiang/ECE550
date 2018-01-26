#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
  if(inputName == NULL){
    fprintf(stderr,"no name\n");
    exit(EXIT_FAILURE);
  }

  size_t c=0;
  while(inputName[c] != '\0'){
    c++;
  }

  char *outName = malloc((c+8)*sizeof(*outName));

  for(int i = 0; i < c; i ++){
    outName[i]=inputName[i];
  }
  outName[c] = '.';
  outName[c+1] = 'c';
  outName[c+2] = 'o';
  outName[c+3] = 'u';
  outName[c+4] = 'n';
  outName[c+5] = 't';
  outName[c+6] = 's';
  outName[c+7] = '\0';
  return outName;

}
