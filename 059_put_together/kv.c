#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"



kvarray_t * readKVs(const char * fname) {

  FILE *f = fopen(fname,"r");
  if(f == NULL){
    fprintf(stderr,"can't open the file");
    exit(EXIT_FAILURE);
  }

  kvarray_t *kvs = malloc(sizeof(*kvs));
  kvs->n = 0;
  kvs->kv = malloc((kvs->n+1)*sizeof(*(kvs->kv)));
  char *lines = NULL;
  size_t s;

  while(getline(&lines,&s,f) >= 0){
    size_t tt = 0;
    kvs->kv[kvs->n].key = NULL;
    kvs->kv[kvs->n].value = NULL;
    while(lines[tt] != '='){
      kvs->kv[kvs->n].key = realloc(kvs->kv[kvs->n].key,(tt+1)*sizeof(*(kvs->kv[kvs->n].key)));
      kvs->kv[kvs->n].key[tt] = lines[tt];
      tt++;
    }
    kvs->kv[kvs->n].key = realloc(kvs->kv[kvs->n].key,(tt+1)*sizeof(*(kvs->kv[kvs->n].key)));
    kvs->kv[kvs->n].key[tt] = '\0';
    tt++;
    size_t vt = 0;
    while(lines[tt] != '\n' && lines[tt] != '\0' ){
      kvs->kv[kvs->n].value = realloc(kvs->kv[kvs->n].value,(vt+1)*sizeof(*(kvs->kv[kvs->n].value)));
      kvs->kv[kvs->n].value[vt] = lines[tt];
      vt++;
      tt++;
    }
    kvs->kv[kvs->n].value = realloc(kvs->kv[kvs->n].value,(vt+1)*sizeof(*(kvs->kv[kvs->n].value)));
    kvs->kv[kvs->n].value[vt] = '\0';  
    kvs->n++;
    kvs->kv = realloc(kvs->kv,(kvs->n+1)*sizeof(*(kvs->kv)));
    free(lines);
    lines = NULL;
  }
  free(lines);
  if(fclose(f) != 0){
    fprintf(stderr,"can't close the file");
    exit(EXIT_FAILURE);
  }
  return kvs;

}

void freeKVs(kvarray_t * pairs) {
  for(int i = 0; i < pairs->n ;i++){
    free(pairs->kv[i].key);
    free(pairs->kv[i].value);
  }
  free(pairs->kv);
  free(pairs);
  return;
}

void printKVs(kvarray_t * pairs) {
  for(int i = 0 ; i <pairs->n ; i++){
    printf("key = '%s' value = '%s'\n",pairs->kv[i].key,pairs->kv[i].value);
  }
  return;
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  for(size_t i= 0; i < pairs->n ; i++){
    if(strcmp(pairs->kv[i].key, key)==0){
      return pairs->kv[i].value;
    }
  }
  return NULL;
}
