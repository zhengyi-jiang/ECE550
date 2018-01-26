#include "bstmap.h"
#include <iostream>
#include <cstdlib>

int main(){
  try{
    BstMap<int,int> a;
    for(int i = 0; i < 10; i++){
      a.add(i,i-1);
    }
    BstMap<int,int> b(a);
    BstMap<int,int> c;
    c.remove(1000000);
    c.remove(1);
    c = a;
    c.remove(9);
    c.add(30,1);
    c.add(20,1);
    c.add(20,1);
    BstMap<int,int> d(c);
    d.add(5,1);
    d.add(4,2);
    d.add(6,3);
    d.add(7,4);
    d.add(8,5);
    d.add(2,6);
    d.add(3,7);
    d.add(1,8);
    d.add(9,9);
    d.add(0,10);
    d.add(6,6);
    d.remove(10);
    d.remove(6);
    d.add(6,6);
    d.remove(6);
    for(int i = 0; i <10; i++){
      //std::cout<<"d key:"<<i<<":"<<d.lookup(i)<<"\n";
      /*std::cout<<"a key:"<<i<<":"<<a.lookup(i)<<"\n";
      std::cout<<"b key:"<<i<<":"<<b.lookup(i)<<"\n";
      std::cout<<"c key:"<<i<<":"<<c.lookup(i)<<"\n";*/
     
    }

    BstMap<int,std::string> e;
    e.add(60,"one");
    e.add(11,"two");
    e.add(93,"3one");
    e.add(4,"4one");
    e.add(25,"5one");
    e.add(84,"6one");
    e.add(1,"7one");
    e.add(21,"8one");
    e.add(35,"9one");
    e.add(70,"one");
    e.add(86,"one");
    e.remove(60);
    e.remove(60);
    
    
  }
  catch(const std::invalid_argument& no){
    std::cerr << "can't find: " << no.what() << '\n';
    exit(EXIT_FAILURE);
  }
  return 0;
}
