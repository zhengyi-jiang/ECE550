#ifndef _LL_H_
#define _LL_H_
#include <cstdlib>
#include <exception>
#include <assert.h>
#include <iostream>

template<typename T>
class LinkedList{
private:
  class Node{
  public:
    T data;
    Node *next;
    Node *previous;
    Node():previous(NULL),next(NULL){}
    Node(const T& d):data(data),previous(NULL),next(NULL){}
    Node(const T& d, Node *n, Node *p):data(d),next(n),previous(p){}
  };
  Node *head;
  Node *tail;
  int size;
public:
  LinkedList():head(NULL),tail(NULL),size(0){}
  LinkedList(const LinkedList &L):head(NULL),tail(NULL),size(0){
    Node *const *temp = &(L.head);
    while(*temp != NULL){
      addBack((*temp)->data);
      temp = &((*temp)->next);
    }
  }
  LinkedList& operator=(const LinkedList &L){
    if(this != &L){
      /*LinkedList temp(L);
      std::swap(temp.head,head);
      std::swap(temp.tail,tail);
      std::swap(temp.size,size);*/
      
      LinkedList temp(L);
      while(head != NULL){
	Node *t = head->next;
	delete head;
	head = t;
      }
      
      head = NULL;
      tail = NULL;
      size = 0;
      head = temp.head;
      temp.head = NULL;
      tail = temp.tail;
      temp.tail =NULL;
      size = temp.size;      
    }
    
    return *this;
  }
  
  void addFront(const T &item){
    head = new Node(item, head, NULL);
    size++;
    if(tail != NULL){
      head->next->previous = head;
    }
    else{
      tail = head;
    }
  }
  
  void addBack(const T &item){
    tail = new Node(item, NULL, tail);
    size++;
    if(head != NULL){
      tail->previous->next = tail;
    }
    else{
      head = tail;
    }
  }

  Node* removehelper(const T &d, Node *n, bool *ass){
    if(n == NULL){
      return NULL;
    }
    if(d == n->data){
      Node* ans = n->next;
      if(ans == NULL){
	tail = n->previous;
      }
      else{
	ans->previous = n->previous;
      }
      delete n;
      size--;
      *ass = true;
      return ans;
    }
    n->next = removehelper(d,n->next,ass);
    return n;
  }
  bool remove(const T &item){
    bool a = false;
    bool *ass = &a;
    if(head == NULL){
      return a;
    }
    head = removehelper(item, head, ass);
    return a; 
  }
  
  T &operator[](int index){
    try{
      if(index < 0 || index > size-1){
	throw std::out_of_range("out of range");
      }
      Node **temp = &head;
      for(int i = 0; i < index;i++){
	temp = &((*temp)->next);
      }
      if((*temp) == NULL){
	throw std::out_of_range("no size");
      }
      return (*temp)->data;
    }
    catch (const std::out_of_range& oor) {
      std::cerr << "Out of Range error: " << oor.what() << '\n';
      exit(EXIT_FAILURE);
    }
  }
  
  const T& operator[] (int index)const{
    try{
      if(index < 0 || index > size-1)
	{
	  throw std::out_of_range("out of range");
	}
      Node *const *temp = &head;
      for(int i = 0; i < index;i++){
	temp = &((*temp)->next);
      }
      if((*temp) == NULL){
	throw std::out_of_range("no size");
      }
      return (*temp)->data;
    }
    catch (const std::out_of_range& oor) {
      std::cerr << "Out of Range error: " << oor.what() << '\n';
      exit(EXIT_FAILURE);
      }
  }

  
  int find(const T &item) const{
    if(head == NULL){
      return -1;
    }
    Node *const *temp = &head;
    int i = 0;
    while((*temp) != NULL && (*temp)->data != item){
      temp = &((*temp)->next);
      if(*temp == NULL){
	return -1;
      }
      i ++;
    }
    return i;
  }
  
  int getSize() const{
    return size;
  }
  
  ~LinkedList(){
    while(head != NULL){
      Node *temp = head->next;
      delete head;
      head = temp;
    }
    tail = NULL;
    size = 0;
  }
};
  
  

#endif
