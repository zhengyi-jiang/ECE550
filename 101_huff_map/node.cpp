#include "node.h"
void  buildMaphelper(const Node * curr,BitString b, std::map<unsigned,BitString> & theMap){
  if(curr->sym == NO_SYM){
    assert(curr->left != NULL && curr->right != NULL);
    buildMaphelper(curr->left, b.plusZero(), theMap);
    buildMaphelper(curr->right, b.plusOne(), theMap);
  }
  else{
    assert(curr->left == NULL && curr->right == NULL);
    theMap.insert ( std::pair<unsigned,BitString>(curr->sym,b));
  }
}

void Node::buildMap(BitString b, std::map<unsigned,BitString> & theMap) {
  buildMaphelper(this,b,theMap);
}
