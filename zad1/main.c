#include <stdio.h>
#include <stdlib.h>
#include "list.h"









int main() {

  BSTNode**root=malloc(sizeof(BSTNode*));
  *root = NULL;

  for(int i=0;i<10000;i++){
    insert(root,"a","b","c","g","h","k");
  }
  printTree(*root);



}
