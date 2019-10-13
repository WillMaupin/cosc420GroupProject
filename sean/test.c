#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct Node{
  struct Node *l, *r;
  _Bool winningMove;
  int id;
};

struct Node* newNode(int id){
  struct Node* node = (struct Node*) malloc(sizeof(struct Node));
  node->id = id;
  node->l = NULL;
  node->r = NULL;
  return(node);
}

// recursively generate tree
// parent: parent of added nodes
// k: level of tree
struct Node* genTree(struct Node* parent, int k){
  if(k == 0){
    // printf("null\n");
    return NULL;
  }else if(k == 1){
    // printf("gT k:%d id:%d\n", k, parent->id);

    parent->l = newNode(parent->id * 2 + 1);
    genTree(parent->l, k-1);
  }else { // k > 1
    // printf("gT k:%d id:%d\n", k, parent->id);

    parent->l = newNode(parent->id * 2 + 1);
    genTree(parent->l, k-1);

    if(k-2 > 0){
    parent->r = newNode(parent->id * 2 + 2);
      genTree(parent->r, k-2);
    }
  }
}

void pre(struct Node* n){
  if(n != NULL){
    printf("%d\n", n->id);
    pre(n->l);
    pre(n->r);
  }
}

int main(int argc, char** argv){
  int k = atoi(argv[1]);

  struct Node *root = newNode(0);
  // printf("main n %d\n", root->id);
  genTree(root, k-1);
  pre(root);



  return 0;
}
