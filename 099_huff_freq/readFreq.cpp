#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include "readFreq.h"

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256 ) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  int c;
  FILE * myfile;
  myfile=fopen (fname,"r");
  if (myfile==NULL) {
    perror ("Error opening file");
    exit(EXIT_FAILURE);
  }
  else{
    uint64_t *ans = new uint64_t[257];
    for(int i =0; i < 257; i++){
      ans[i] = 0;
    }
    while ((c = fgetc (myfile)) != EOF) {
      ans[(int)c]++;
    }
    ans[256] = 1;
    fclose (myfile);
    return ans;
  }
}
