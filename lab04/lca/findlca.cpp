#include "tree.h"

// Function which returns lca node of given nodes 'a' and 'b'
// We've given the parent pointer: Made it very easy to solve
TreeNode* solve(TreeNode* a, TreeNode* b){
  if(a==nullptr || b == nullptr) return nullptr;

  TreeNode* t1 = a;
  TreeNode* t2 = b;

  while(t1 != nullptr){
    if(t2->key == t1-> key){
      return t1;
    }
    t1 = t1->parent;
  }
  t1 = a;
  while(t2 != nullptr){
    if(t1->key == t2-> key){
      return t2;
    }
    t2 = t2->parent;
  }

  return solve(a->parent, b->parent);

}
TreeNode* TREE::findlca(TreeNode* a, TreeNode* b) {
    
  return solve(a, b);

}