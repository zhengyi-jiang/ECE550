#ifndef __BSTMAP_H__
#define __BSTMAP_H__
#include "map.h"
#include <cstdlib>
#include <iostream>

template<typename T, typename W>
class BstMap: public Map<T, W> {
private:
  class Node{
  public:
    T key;
    W value;
    Node * left;
    Node * right;
    Node():left(NULL),right(NULL){}
    Node(T k, W v, Node *l, Node *r):key(k),value(v),left(l),right(r){}
  };
  Node *root;
  
public:
  BstMap():root(NULL){}
  BstMap(const BstMap &rhs):root(NULL){
    copy(rhs.root);
  }

  BstMap &operator= (const BstMap &rhs){
    if (this != &rhs){
      BstMap temp(rhs);
      std::swap(temp.root,root);
    }
    return *this;
  }
			  
			  
  void copy(const Node *curr){
    if(curr != NULL){
      copy(curr->left);
      copy(curr->right);
      add(curr->key, curr->value);
    }
  }
 
    
  virtual void add(const T & key, const W & value){
    Node ** curr = &root;
    while(*curr != NULL){
      if( key < (*curr)->key){
	curr = &(*curr)->left;
      }
      else if(key == (*curr)->key){
	(*curr)->value = value;
	return;
      }
      else{
	curr = &(*curr)->right;
      }
    }
    *curr = new Node(key,value,NULL,NULL);
  }
  
  virtual const W & lookup(const T& key) const throw (std::invalid_argument){
    Node *current = root;
    while(current != NULL){
      if(current->key == key){
	return current->value;
      }
      if(key < current->key){
	current = current->left;
      }
      else{
	current = current->right;
      }
    }
    throw std::invalid_argument("can't find it");
  }
      
    

  Node *removehelper(const T& key, Node *curr){
    if(curr != NULL){
      if(curr->key == key){
	//std::cout <<"to remove:"<< curr->key << "\n";//print to remove
	if(curr -> left == NULL){
	  Node *temp = curr->right;
	  delete curr;
	  return temp;
	}
	else if(curr -> right == NULL){
	  Node *temp = curr->left;
	  delete curr;
	  return temp;
	}
	else{
	  int i = 0;
	  Node *torp = curr->right;
	  Node *torpup = curr;
	  while(torp->left != NULL && torp->right != NULL){
	    torpup = torp;
	    torp = torp->left;
	    i++;
	  }
	  if(torp -> left == NULL){
	    Node *temp = torp->right;
	    if(i != 0){
	      torpup->left = temp;
	    }
	    else{
	      torpup->right = temp;
	    }
	  }
	  else if(torp -> right == NULL){
	    Node *temp = torp->left;
	    if(i != 0){
	      torpup->left = temp;
	    }
	    else{
	      torpup->right = temp;
	    }
	  }
	  Node *templeft = curr->left;
	  Node *tempright = curr->right;
	  torp->left = templeft;
	  torp->right = tempright;
	  delete curr;
	  //std::cout <<"to replace:"<< torp->key << "\n";//print to replace
	  return torp;
	} 
      }
      else{
	curr->left = removehelper(key ,curr->left);
	curr->right = removehelper(key, curr->right);
      }
    }
    return curr;
  }
  
  virtual void remove(const T& key){
    root = removehelper(key, root);
  }
  

  
  void destory(Node *curr){
    if(curr != NULL){
      destory(curr->left);
      destory(curr->right);
      //std::cout <<"to destroy:"<< curr->key <<":"<< curr->value<< "\n";//print to replace 
      delete curr;
    }
  }

virtual ~BstMap<T,W>() {destory(root);}
};
#endif
