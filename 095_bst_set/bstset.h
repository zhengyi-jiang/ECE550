#ifndef __BSTSET_H__
#define __BSTMAP_H__
#include "set.h"
#include <cstdlib>
#include <iostream>

template<typename T>
  class BstSet: public Set<T> {
 private:
  class Node{
  public:
    T key;
    Node * left;
    Node * right;
  Node():left(NULL),right(NULL){}
  Node(T k, Node *l, Node *r):key(k),left(l),right(r){}
  };
  Node *root;

 public:
 BstSet():root(NULL){}
 BstSet(const BstSet &rhs):root(NULL){
    copy(rhs.root);
  }

  BstSet &operator= (const BstSet &rhs){
    if (this != &rhs){
      BstSet temp(rhs);
      std::swap(temp.root,root);
    }
    return *this;
  }


  void copy(const Node *curr){
    if(curr != NULL){
      copy(curr->left);
      copy(curr->right);
      add(curr->key);
    }
  }


  virtual void add(const T & key){
    Node ** curr = &root;
    while(*curr != NULL){
      if( key < (*curr)->key){
	curr = &(*curr)->left;
      }
      else if(key == (*curr)->key){
	return;
      }
      else{
	curr = &(*curr)->right;
      }
    }
    *curr = new Node(key,NULL,NULL);
  }

  virtual bool contains(const T& key)const{
    Node *current = root;
    while(current != NULL){
      if(current->key == key){
	return true;
      }
      if(key < current->key){
	current = current->left;
      }
      else{
	current = current->right;
      }
    }
    return false;
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

  virtual ~BstSet<T>() {destory(root);}
};
#endif
