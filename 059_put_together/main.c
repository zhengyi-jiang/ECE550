#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  FILE* f=fopen(filename,"r");
  if(f == NULL){
    fprintf(stderr,"failed to open input\n");
    exit(EXIT_FAILURE);
  }
  char **Data = NULL;
  char *line = NULL;
  size_t sz;
  size_t li = 0;
  while(getline(&line,&sz,f) >= 0){
    Data = realloc(Data,(li+1)*sizeof(*Data));
    Data[li] = line;
    line = NULL;
    li++;
  }
  free(line);

  
  char **counts = NULL;
  
  for(size_t i = 0; i <li; i++){
    size_t _n = 0;
    while(Data[i][_n] != '\n'){
      _n++;
    }
    Data[i][_n] = '\0';
    counts = realloc(counts,(i+1)*sizeof(*counts));
    counts[i] = lookupValue(kvPairs, Data[i]);
    free(Data[i]);
  }
  free(Data);
  counts_t * C= createCounts();
  for(size_t j =0; j < li; j++) {
    addCount(C,counts[j]);
  }
  if(fclose(f) != 0){
    fprintf(stderr,"can't close the file\n");
    exit(EXIT_FAILURE);
  }
  free(counts);
  return C;
}

int main(int argc, char ** argv) {
  if(argc < 2){
    fprintf(stderr,"error:input\n");
    exit(EXIT_FAILURE);
  }
  
  //WRITE ME (plus add appropriate error checking!)
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t *kv =readKVs(argv[1]);
  //count from 2 to argc (call the number you count i)
  for(size_t i = 2; i < argc; i++){
    counts_t *c = countFile(argv[i],kv);
    
  //count the values that appear in the file named by argv[i], using kv as the key/value pair
  //   (call this result c)
  
  //compute the output file name from argv[i] (call this outName)
  char *outName = computeOutputFileName(argv[i]);
  //open the file named by outName (call that f)
  FILE* f =fopen(outName,"w");
  //print the counts from c into the FILE f
  printCounts(c,f);
  //close f
  if(fclose(f) != 0){
    fprintf(stderr,"can't close the file\n");
    exit(EXIT_FAILURE);
  }
  //free the memory for outName and c
  free(outName);
  freeCounts(c);
  }
  //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
