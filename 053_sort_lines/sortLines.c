#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  
  qsort(data, count, sizeof(char *), stringOrder);
}

void readfile(FILE* f){
  char ** data = NULL;
  char * sline = NULL;
  size_t s = 0;
  size_t count = 0;
  while(getline(&sline, &s , f) >= 0){
    count++;
    data = realloc (data,count*sizeof(*data));
    data[count-1] = sline;
    sline = NULL;
    free(sline);
  }
  free(sline);
  sortData(data, count);
  for(int j = 0; j<count; j++){
    printf("%s",data[j]);
    free(data[j]);
  }
  free(data);
  return;
}

int main(int argc, char ** argv) {
  if( argc == 1){
    if(stdin == NULL){
      fprintf(stderr,"enter something!\n");
      return EXIT_FAILURE;
    }
    readfile(stdin);
    return EXIT_SUCCESS;
  }
  for(size_t i = 1; i<argc; i++){
    FILE* f =fopen(argv[i],"r");
    if(f == NULL){
      fprintf(stderr,"invalid filename\n");
      return EXIT_FAILURE;
    }
    readfile(f);
    if (fclose(f) != 0) {
      perror("Failed to close the input file!");
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}
