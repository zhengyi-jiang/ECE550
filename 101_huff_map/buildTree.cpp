#include "node.h"
#include <assert.h>

Node *  buildTree(uint64_t * counts) {
  assert(counts != NULL);
  priority_queue_t pq;
  for (unsigned i = 0; i < 257; i++) {
    if (counts[i] == 0) {
      continue;
    }
    pq.push(new Node(i,counts[i]));
  }
  while(pq.size() != 1){
    Node * a = pq.top();
    pq.pop();
    Node * b = pq.top();
    pq.pop();
    Node * p = new Node(a,b);
    pq.push(p);
  }
  return pq.top();
}
