#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char * str) {
  if(str == NULL){
    return;
  }
  else{
    size_t N=0;
    while(str[N] != '\0'){
      N++;
    }
    N++;
    
    char strrecord[N];
    for(size_t i=0;i<N-1;i++){
      strrecord[i]=str[N-2-i];
    }
    strrecord[N-1]='\0';
    
    for(size_t j=0;j<N-1;j++){
      str[j]=strrecord[j];
    }
    str[N-1]='\0';
    return;
  }
}

int main(void) {
  char str0[] = "";
  char str1[] = "123";
  char str2[] = "abcd";
  char str3[] = "Captain's log, Stardate 42523.7";
  char str4[] = "Hello, my name is Inigo Montoya.";
  char str5[] = "You can be my wingman anyday!";
  char str6[] = "Executor Selendis! Unleash the full power of your forces! There may be no tomorrow!";
  char * array[] = {str0, str1, str2, str3, str4, str5, str6};
  for (int i = 0; i < 7; i++) {
    reverse(array[i]);
    printf("%s\n", array[i]);
  }
  return EXIT_SUCCESS;
}
