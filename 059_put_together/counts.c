#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
counts_t * createCounts(void) {
  counts_t *allC = malloc(sizeof(*allC));
  allC->object = NULL;
  allC->num = 0;
  allC->unknown = 0;
  return allC;
}

void addCount(counts_t * c, const char * name) {
   if(c == NULL){
    fprintf(stderr,"error: no count\n");
    exit(EXIT_FAILURE);
  }
      
  if(name == NULL){
    c->unknown++;
    return;
  }
  
  size_t j= 0;
  for(size_t i = 0; i < c->num ; i++){
    if(strcmp(name,c->object[i].value) == 0){
	c->object[i].oc++;
	j++;
      }
  }

  if(j == 0){
    c->num++;
    c->object= realloc(c->object,c->num*sizeof(*(c->object)));
    c->object[c->num-1].value = NULL;
    c->object[c->num-1].oc = 1;
    size_t li = 0;
    while(name[li] != '\0'){
      c->object[c->num-1].value = realloc(c->object[c->num-1].value,(li+1)*sizeof(*(c->object[c->num-1].value)));
      c->object[c->num-1].value[li] = name[li];
      li++;
    }
    c->object[c->num-1].value = realloc(c->object[c->num-1].value,(li+1)*sizeof(*(c->object[c->num-1].value)));
    c->object[c->num-1].value[li] = '\0';
  }					 
  return;
  
}
void printCounts(counts_t * c, FILE * outFile) {
  for(size_t i= 0; i < c->num ; i++){
    fprintf(outFile,"%s: %lu\n",c->object[i].value,c->object[i].oc);
  }
  if(c->unknown != 0){
    fprintf(outFile,"<unknown> : %lu\n",c->unknown);
  }
  return;
}

void freeCounts(counts_t * c) {
  for(size_t i = 0; i < c->num ; i++){
    free(c->object[i].value);
  }
  free(c->object);
  free(c);
  return;
}
