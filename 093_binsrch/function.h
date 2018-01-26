#ifndef __FUNCTION_H__
#define __FUNCTION_H__
#include <stdio.h>
#include <stdlib.h>
template<typename R, typename A> 
class Function {
public:
  virtual R invoke(A arg) = 0;
  virtual ~Function() {}
};


class CountedIntFn : public Function<int,int>{
protected:
  unsigned remaining;
  Function<int,int> * f;
  const char * mesg;
public:
  CountedIntFn(unsigned n, Function<int,int> * fn, const char * m): remaining(0),
                                                                    f(fn),
								    mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 100) {
      fprintf(stderr,"Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining++;
    printf("%d\n",remaining);
    return f->invoke(arg);
  }

};

class PlusoneFn : public Function<int,int>{
public:
  virtual int invoke(int arg){
    return arg + 1;
  }
};

#endif
