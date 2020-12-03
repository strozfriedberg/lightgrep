#include "treehasher.h"

HasherHolder::HasherHolder(TreeHasher& th):
  th(th) 
{
  th.push();
}

HasherHolder::~HasherHolder() {
  th.pop();
}
