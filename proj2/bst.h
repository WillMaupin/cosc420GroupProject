<<<<<<< HEAD
#ifndef BST
#define BST

#include<stdio.h>
#include<stdlib.h>

#include"BSTNode.h"

typedef struct BSTree {
    BSTNode* root;

    // char*

} BSTree;

void initBST(BSTree *tree) {
    tree->root = NULL;
}

/*insertBSTNode:
    recursively inserts into tree alphabetically: words that appear
    earlier alphabetically will be inserted to the left, words that appear
    later will be inserted to the right.

    RETURNS:
        BSTNode*: have to reassign tree when function is called...
            not sure why...

    ARGUMENTS:
        parent_node: compare keyword of this node with node being inserted,
            also used to point to node after being inserted
        node: node to be inserted   */
BSTNode* insertBSTNode(BSTNode *root_node, BSTNode* new_node){
    printf("Welcome to insertBSTNode!!!\n"); // dbugging

    if(new_node != NULL)    printf("inserting: %s\n", new_node->keyword); // dbugging
    if(root_node != NULL)   printf("comparing: %s\n", root_node->keyword); //dbugging

    if(root_node == NULL) {
        /*  tree is empty, just need to insert node at root */
        printf("Empty tree\n"); //dbugging

        // node = new_node;
        return new_node;
    }else{
        /* tree is not empty */
        printf("tree not empty\n"); //dbugging

        /* determines difference in ascii values between root keyword and keyword of
            node being inserted */
        int key = strcmp(root_node->keyword, new_node->keyword);
        printf("%d\n", key); //dbugging
        if(key <= -1){
            //str comes before ptr->keyword alphabetically
            printf("after\n");

            root_node->right = insertBSTNode(root_node->right, new_node);
            return root_node;

        } else if (key >= 1){
            //str comes after ptr->keyword alphabetically
            printf("before\n");

            root_node->left = insertBSTNode(root_node->left, new_node);
            return root_node;

        } else {
            // str and ptr->key word are the same word
            printf("equal\n");

            /* add article to nodes linked list here */
            return root_node;
        }
    }

    printf("end\n");    // dbugging
}

/*
    tried to rework insertion with this function, to make the function calls
    simpler and remove need to explicitly declare a new node for each
    keyword
        BSTNode a = {...};
            vs.
        insert(tree, <keyword string>);

    idea is to initialize new node in this function, actual insertion is
    done in insertBSTNode
    much of this function is debugging code, left pointer is not NULL
    in main function, shows to be null here though...
    not sure what is going on or why it is happening


*/
BSTNode* insert(BSTree tree, char* str){
    BSTNode new_node;      //new node to be inserted
    initBSTNode(&new_node, str);    //set keyword to str, else to NULL

    /*  debugging
    printf("new_node: %s\n", new_node.keyword);
    if(new_node.left != NULL)       printf("new_node.left\n");
    if(new_node.right != NULL)      printf("new_node.right\n");
    if(new_node.articles != NULL)   printf("new_node.articles \n");

    BSTNode* hold = insertBSTNode(tree.root, &new_node); //used in debugging
    if(hold->left != NULL)          printf("hold->left\n");
    if(hold->right != NULL)         printf("hold->right\n");
    if(hold->articles != NULL)      printf("hold->articles \n");
    return hold;     //debugging

    debug code ends here*/

    return insertBSTNode(tree.root, &new_node); //remove to test code above

}

/*displayBST:

    recursively prints keywords of nodes in preorder

    ARGUMENTS:
        BSTNode *node:
            node to recurse on (if it has any children)
                or print keyword of.

        int level:
            level of tree (increases as you move down the tree,
                s.t.:
                    root is on level 0,
                    roots children on level 1,
                    roots grandchildren on level 2,
                    etc.)
*/
void displayBST(BSTNode *node, int level){
    printf("a\n");
    if(node->left != NULL){
        printf("b\n");
        // displayBST(node->left, level++);
        printf("c\n");
    }
    printf("d\n");

    if(node != NULL){
        printf("e\n");
        printf("%d: %s\n", level, node->keyword);
        printf("f\n");
    }
    else{  printf("null\n"); }  //debugging
    printf("g\n");

    if(node->right != NULL){
        printf("h\n");
        displayBST(node->right, level++);
        printf("i\n");
    }
    printf("j\n");
}

=======
#ifndef BST_H
#define BST_H

/*
typedef struct ReferencesBST{
	char* id;
	struct ReferencesBST *left;
	struct ReferencesBST *right;
}ref;
*/

typedef struct ArticleBST{
	char* id;
	struct ArticleBST *left;
	struct ArticleBST *right;
	//ref *references;	//search tree of references
}article;

typedef struct BST
{
	char* keyword;
	struct BST *left;
	struct BST *right;
	article *articles; //search tree of articles
}node;
 
node *createNode();
article *createArticle();
node *insertNode(node *,node *, article *);
void insertArticle(article *root, article *new_node);
void printNodes(node *);
void printArticles(article *);
void mergeTrees(node *, node*);
void mergeArticles(article *, article*);

article *createArticle(char* id){
	article *temp;
	temp = (article*)malloc(sizeof(article));
	temp->id = malloc(sizeof(char)*20);
	
	for(int i = 0; i < 20; i++){
		temp->id[i] = id[i];
		if(id[i] == '\0')
			i = 20;
	}

	temp->left=temp->right=NULL;
	return temp;
}

node *createNode(char* str){
	node *temp;
	temp=(node*)malloc(sizeof(node));
	temp->keyword = malloc(sizeof(char)*20);
	temp->articles = malloc(sizeof(article));

	for(int i = 0; i < 20; i++){
		temp->keyword[i] = str[i];
		if(str[i] == '\0')
			i = 20;
	}
	temp->articles = NULL;
	temp->left=temp->right=NULL;
	return temp;
}
 
node* insertNode(node *root,node *temp, article *article_node){
	int key = strcmp(temp->keyword, root->keyword);
	if(key < 0){
		if(root->left!=NULL){
			insertNode(root->left,temp, article_node);
		} else {
			root->left=temp;	
			if(root->left->articles == NULL)
				root->left->articles = article_node;
			else
				insertArticle(root->left->articles, article_node);
			return root->left;
		}
	} else if(key > 0){
		if(root->right!=NULL){
			insertNode(root->right,temp, article_node);
		} else {
			root->right=temp;
			if(root->right->articles == NULL){
				root->right->articles = article_node;
			}else{
				insertArticle(root->right->articles, article_node);
			}
			return root->right;
		}
	} else if(key == 0) {
		//don't insert, only add the article
		if(root->articles == NULL){
			root->articles = article_node;
		}else{
			insertArticle(root->articles, article_node);
		}
		return root;
	}
}


void insertArticle(article *root, article *temp){
	int key = strcmp(temp->id, root->id);
	if(key < 0){
		if(root->left!=NULL)
			insertArticle(root->left,temp);
		else
			root->left=temp;	
	} else if(key > 0){
		if(root->right!=NULL){
			insertArticle(root->right,temp);
		}else{
			root->right=temp;
		}
	} else if(key == 0) {
		//do nothing, article already exists
	}

}
 
void printNodes(node *root){
	if(root!=NULL){
		printf("%s ",root->keyword);
		printNodes(root->left);
		printNodes(root->right);
	}
}

void printArticles(article *root){
	if(root != NULL){
		printf("%s ", root->id); 
		printArticles(root->left);
		printArticles(root->right);
	}
}

void mergeTrees(node *major, node *minor){
	node *temp;
	if(minor != NULL){
		temp = insertNode(major, minor, minor->articles);
		//mergeArticles(temp->articles, minor->articles);
		mergeTrees(major, minor->left);
		mergeTrees(major, minor->right);
	}
}

void mergeArticles(article *root, article* A){
	if(A != NULL){
		insertArticle(root, A);
		mergeArticles(root, A->left);
		mergeArticles(root, A->right);
	}
}
>>>>>>> 2b05534fcf99c4fbdab6acacf933885d4d0b45d9
#endif
