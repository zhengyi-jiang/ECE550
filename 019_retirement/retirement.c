#include <stdlib.h>
#include <stdio.h>

struct _retire_info{
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;

double compute(int age,double balance,retire_info info){
  for(int i=0;i<info.months;i++){
    int tmonth=age+i;
    int month=tmonth%12;
    printf("Age %3d month %2d you have $%.2lf\n",tmonth/12,month,balance);
    balance=balance+balance*info.rate_of_return+info.contribution;
  }
  return balance;
}

void retirement(int startAge,
		double initial,
		retire_info working,
		retire_info retired){

  double tbalance=compute(startAge,initial,working);

  startAge=startAge+working.months;
  initial=tbalance;

  double retire=compute(startAge,initial,retired);
  retire=0*retire;
  return;
}

int main(){
  int startAge=327;
  double initial=21345;
  retire_info working;
  retire_info retired;
  
  working.months=489;
  working.contribution=1000;
  working.rate_of_return=0.045/12;

  retired.months=384;
  retired.contribution=-4000;
  retired.rate_of_return=0.01/12;

  retirement(startAge,initial,working,retired);
  return 0;
}
