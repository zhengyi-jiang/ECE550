#include "election.h"
#include <string.h>
#include <ctype.h>
#include <stdio.h>
//include any other headers you need here...

state_t parseLine(const char * line) {
  if( line == NULL){
    fprintf(stderr,"error: NULL line.\n");
    exit(EXIT_FAILURE);
  }
  
  state_t s;
  s.population=0;
  s.electoralVotes=0;
  for(size_t j = 0; j<64; j++){
    s.name[j]=0;
  }
  size_t mao =0;
  size_t count=0;
  while(line[count] != '\0'){
    if(line[count] == ':'){
      mao++;
    }
    count++;
  }
  if(mao != 2){
    fprintf(stderr,"error: format.\n");
    exit(EXIT_FAILURE);
  }
  
  size_t n = 0;
  while(line[n] != ':'){
    s.name[n] = line[n];
    n++;
  }
  if(n == 0){
    fprintf(stderr,"error: no name.\n");
    exit(EXIT_FAILURE);
  }
  //name above.
  size_t p = n+1;
  size_t pp =0;
  while(line[p] != ':'){
    if (line[p] < '0' || line[p] > '9'){
      fprintf(stderr,"error: population should be a natrual number.\n");
      exit(EXIT_FAILURE);
      }
    pp++;
    p++;
  }
  if( pp == 0){
    fprintf(stderr,"error: no population.\n");
    exit(EXIT_FAILURE);
  }
  char population[pp+1];
  for (size_t i= 0; i < pp; i++){
    population[i] = line[n+1+i];
  }
  population[pp] = '\0';
  s.population = atoi(population);
  //population above
  size_t ee= 0;
  size_t e = p+1;
  while(line[e] != '\0'){
    if (line[e] < 48 || line[e] >57){
      fprintf(stderr,"error: electroalVotes should be a natrual number.\n");
      exit(EXIT_FAILURE);
    }
    ee++;
    e++;
  }
  if( ee == 0){
    fprintf(stderr,"error: no electroalVotes.\n");
    exit(EXIT_FAILURE);
  }
  char elec[ee+1];
  for (size_t i= 0; i < ee; i++){
    elec[i] = line[p+1+i];
  }
  elec[ee]='\0';
  s.electoralVotes = atoi(elec);
  return s;
}

unsigned int countElectoralVotes(state_t * stateData, 
				 uint64_t * voteCounts, 
				 size_t nStates) {
  if(stateData == NULL || voteCounts == NULL || nStates == 0){
    fprintf(stderr,"error: format.\n");
    exit(EXIT_FAILURE);
  }
  
  unsigned int tt = 0;
  for(size_t i = 0; i < nStates ; i++ ){
    if(voteCounts[i] > stateData[i].population){
      fprintf(stderr,"Voter Fraud!\n");
      exit(EXIT_FAILURE);
    }
    if(stateData[i].population == 0){
    }
    else if((double)voteCounts[i]/((double)stateData[i].population) > 0.5){
      tt += stateData[i].electoralVotes;
    }
  }
  return tt;
}

void printRecounts(state_t * stateData, 
		   uint64_t * voteCounts, 
		   size_t nStates) {
  if(stateData == NULL || voteCounts == NULL || nStates == 0){
    fprintf(stderr,"error: format.\n");
    exit(EXIT_FAILURE);
  }

  for(size_t i = 0; i < nStates ; i++ ){
    if(voteCounts[i] > stateData[i].population){
      fprintf(stderr,"Voter Fraud!\n");
      exit(EXIT_FAILURE);
    }
    if(stateData[i].population == 0){
    }
    else if((double)voteCounts[i]/((double)stateData[i].population) <= 0.505 &&
       (double)voteCounts[i]/((double)stateData[i].population) >= 0.495){
      double r =100*(double)voteCounts[i]/((double)stateData[i].population);
      printf("%s requires a recount (Candidate A has %.2f%% of the vote)\n",stateData[i].name,r);
    }
  }
  return;
}

void printLargestWin(state_t * stateData, 
		     uint64_t * voteCounts, 
		     size_t nStates) {
  if(stateData == NULL || voteCounts == NULL || nStates == 0){
    fprintf(stderr,"error: format.\n");
    exit(EXIT_FAILURE);
  }
  size_t temp = 0;
  double r = 0;
  double tempr = 0;
  for(size_t i = 0; i < nStates ; i++ ){
    if(voteCounts[i] > stateData[i].population){
      fprintf(stderr,"Voter Fraud!\n");
      exit(EXIT_FAILURE);
    }
    if(stateData[i].population == 0){
      tempr = 0;
      if(tempr > r){
    	r = tempr;
	temp = i;
      }
    }
    
    else{
      tempr =100*(double)voteCounts[i]/((double)stateData[i].population);
      if(tempr > r){
	r = tempr;
	temp = i;
      }
    }
  }
  printf("Candidate A won %s with %.2f%% of the vote\n",stateData[temp].name,r);
  return;
  
  //STEP 4: write me
}
