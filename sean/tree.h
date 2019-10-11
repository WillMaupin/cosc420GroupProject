#ifndef TREE_H
#define TREE_H

// boolean values
#define true 1
#define false 0

#define KRED  "\x1B[31m"    // red terminal text
#define KWHT  "\x1B[37m"    // white terminal text
#define KYEL  "\x1B[33m"    // yellow terminal text

// #define DBUG true
_Bool DBUG = false;

#include <math.h>
// #include "debug.h"

typedef struct Node{
  struct Node *parent, *lptr, *rptr;
  _Bool winningMove;
  int id, nodes_in_subtree;
}Node;

typedef struct BinaryTree{
    Node root;
    int nodes_in_tree;
    int levels_in_tree;
}BinaryTree;

// function header, function defined below
int genTree(BinaryTree *tree, Node* parent, int size_needed,
    int current_size);

void insertNode(Node *n, int id){
    if(DBUG) printf("iN\n");
    // n->parent = NULL;
    n->rptr = NULL;
    n->lptr = NULL;
    n->id = id;
    n->winningMove = 0;
    // n->nodes_in_subtree = 1; //counts self in subtree; do we want this?
}

void printNode(Node *node){
    if(node->winningMove){
        printf("%s%c%s", KRED, 'o', KWHT);
    }else{
        printf("%c",'o');
    }
}

// added for ease of use, used to call recursive genBTree()
void initBTree(BinaryTree* tree, int size){
    Node root;
    insertNode(&root, 0);
    tree->root = root;
    tree->nodes_in_tree = 1;
    // tree->levels_in_tree = 1;
    // printf("%d\n", size);
    genTree(tree, &tree->root, size, 0);
}

//recursively print subtrees of node passed
void printTree(Node *node, int level){
    if(DBUG) printf("pT %d\n", level);

    if(node != NULL){
        printf("lnode id: %d\n", node->lptr->id);
        printTree(node->lptr, level+1);
        printf("o%d", level);
        printf("rnode id: %d\n", node->rptr->id);
        printTree(node->rptr, level+1);
        puts("");
    }
}

// count nodes in tree and assign to tree's variable 'node_in_tree'
int countNodes(BinaryTree *node){
    // TODO: is this needed?
}

// recursively generate tree
// tree: does not change in recursive calls,
// parent: parent of added nodes
// n: number of child nodes
// level: level of tree of parent node
int genTree(BinaryTree *tree, Node* parent, int nchild, int id)
{
    if(DBUG) printf("gT nc:%d id:%d\n", nchild, id);

    if(nchild > 1){
        Node nlptr, nrptr;
        parent->lptr = &nlptr;
        genTree(tree, parent->lptr, nchild - 1, (id*2)+1);
        parent->rptr = &nrptr;
        genTree(tree, parent->rptr, nchild - 2, (id*2)+2);

    }
}

#endif
