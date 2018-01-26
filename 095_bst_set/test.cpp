#include "bstset.h"
#include <iostream>
#include <cstdlib>

int main(){
  BstSet<int> a;
  for(int i = 0; i < 10; i++){
    a.add(i);
  }
  BstSet<int> b(a);
  BstSet<int> c;
  c.remove(1000000);
  c.remove(1);
  c = a;
  c.remove(9);
  c.add(30);
  c.add(20);
  c.add(20);
  BstSet<int> d(c);
  d.add(5);
  d.add(4);
  d.add(6);
  d.add(7);
  d.add(8);
  d.add(2);
  d.add(3);
  d.add(1);
  d.add(9);
  d.add(0);
  d.add(6);
  d.remove(10);
  d.remove(6);
  d.add(6);
  d.remove(6);
  for(int i = 0; i <10; i++){
    std::cout<<"d key:"<<i<<";"<<d.contains(i)<<"\n";
    std::cout<<"a key:"<<i<<":"<<a.contains(i)<<"\n";
    std::cout<<"b key:"<<i<<":"<<b.contains(i)<<"\n";
    std::cout<<"c key:"<<i<<":"<<c.contains(i)<<"\n";
    
  }
  BstSet<int> e;
  e.add(60);
  e.add(11);
  e.add(93);
  e.add(4);
  e.add(25);
  e.add(84);
  e.add(1);
  e.add(21);
  e.add(35);
  e.add(70);
  e.add(86);
  e.remove(60);
  e.remove(60);
  
  
  
  return 0;
}
