#ifndef BST_H
#define BST_H

#include<string.h>

/*
		TRIED TO DOCUMENT AS MUCH AS I COULD, WAS UNCLEAR ABOUT SOME FUNTIONS,
		TRIED TO USE ??? TO INDICATE WHERE I WAS UNCLEAR.

		FEEL FREE TO ADD/CHANGE/REMOVE AS YOU FEEL
		-SB
*/

/*
typedef struct ReferencesBST{
	char* id;
	struct ReferencesBST *left;
	struct ReferencesBST *right;
}ref;
*/


typedef struct ArticleBST {
	char* id;					//id of article
	struct ArticleBST *left;	//pointer to left article subtree
	struct ArticleBST *right;	//pointer to right article subtree
}article;

typedef struct BST {
	char* keyword;		//keyword used
	struct BST *left; 	//left subtree
	struct BST *right; 	//right subtree
	article *articles;	//search tree of articles
}node;

//function prototypes
node *createNode();
article *createArticle();
node *insertNode(node*, node*, article*);
void insertArticle(article*, article*);
void printNodes(node*);
void printArticles(article*);
void mergeTrees(node*, node*);
void mergeArticles(article*, article*);

//function declarations

/* createArticles
	create article pointer and assign id variable, along with

	ARGUMENTS:
		id: char*;

	RETURNS:
		article*: returns newly created article pointer
*/
article* createArticle(char* id){
	article *temp; //node used to store article id
	temp = (article*)malloc(sizeof(article)); //allocate memory for temp
	temp->id = malloc(sizeof(char)*20);	//allocate memory for article id

	strcpy(temp->id, id);
	// printf("copied: %s\n", temp->id);	// debugging

	// for(int i = 0; i < 20; i++){
	// 	temp->id[i] = id[i];
	// 	if(id[i] == '\0')
	// 		i = 20;
	// }

	temp->left=temp->right=NULL; //left and right subtrees are empty
	return temp;
}

/* createNode
	creates node storing article BSTs and keyword BSTs
	ARGUMENTS:
		str: char*; the keyword to be assigned to node->keyword

	RETURN:
		node*: points to newly created node */
node *createNode(char* str){
	node *temp;	//node used to store str
	temp=(node*)malloc(sizeof(node));	//dynamically allocate space in
										//memory for temp

	temp->keyword = malloc(sizeof(char)*20); //allocate space in memory to store keyword
	temp->articles = malloc(sizeof(article)); //allocate memory for article pointers
												// and article BSTs

	strcpy(temp->keyword, str);
	// printf("copied: %s\n", temp->id);	// debugging

	//copy str to temp->keyword char by char
	// for(int i = 0; i < 20; i++){
	// 	temp->keyword[i] = str[i];
	// 	if(str[i] == '\0')	//breaks from loop if string has been read
	// 		i = 20;
	// }

	temp->articles = NULL;	//articles BST is empty
	temp->left=temp->right=NULL;	//left and right subtrees are empty
	return temp;
}

/*	insertNode
	insert node into bst
	ARGUMENTS:
		root: node pointer, root of tree which node will be inserted
		article: node pointer, node contatining data to be inserted by (id?)
		article_node: article to be added to articleBST via insertArticle()

	RETURNS:
		node*: (root of tree?)*/
node* insertNode(node *root, node *temp, article *article_node){
	//keyword of node to be inserted
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

/* insertArticle
	recurse through article BST and insert where appropriate

	ARGUMENTS:
		root: article bst pointer; used in recursion, will point to location
			where article node will be inserted

		temp: article node pointer: stores data to be inserted

	RETURNS:
		n/a */
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

/* printNodes
	recursively prints nodes of bst in PREORDER
	ACCEPTS:
		root: node pointer; node containing keyword to be printed
	RETURNS:
		n/a	*/
void printNodes(node *root){
	if(root!=NULL){	//make sure root is not NULL
		printf("%s ",root->keyword);	//print roots keyword
		printNodes(root->left);		//recurse down left subtree
		printNodes(root->right);	//recurse down right subtree
	}
}

/* printArticles
	recursively prints articles and their id's in PREORDER

	ACCEPTS:
		root: article pointer; node containing article ids to be printed
	RETURNS:
		n/a  */
void printArticles(article *root){
	if(root != NULL){	//make sure root article is not NULL
		printf("%s ", root->id);	//print root articles id
		printArticles(root->left);	//recurse down left subtree
		printArticles(root->right);	//recurse down right subtree
	}
}

/* mergeTrees
	NOTE: NOT SURE I UNDERSTAND WHAT IS HAPPENING IN THIS FUNCTION,
			??? WHERE I AM UNCLEAR -SB
	merge two BSTs, used when combining two proc.s respective BSTs

	ACCEPTS:
		major: node pointer; "master" nodes, ???

		minor: node pointer; node being merged into major???
			NOTE: will we want to delete minor after merging to prevent
				data leaks?

	RETURNS:
		n/a */
void mergeTrees(node *major, node *minor){
	node *temp;
	if(minor != NULL){	//make sure minor is not an empty tree
		temp = insertNode(major, minor, minor->articles);	//???
		//mergeArticles(temp->articles, minor->articles);
		mergeTrees(major, minor->left);	//recurse down left subtree
		mergeTrees(major, minor->right);	//recurse down right subtree
	}
}

/* mergeArticles
	copies articles from ??? to root->articles
	ARGUMENTS:
		root: node pointer; node containing "master" article list,
			articles will be copied into root->articles
		A: article BST pointer; article to be added to root->articles
	RETURNS:
		n/a */
void mergeArticles(article *root, article* A){
	if(A != NULL){	//make sure there are articles let to be copied
		insertArticle(root, A);	//add article to root->articles
		mergeArticles(root, A->left);	//recurse down left subtree of A
		mergeArticles(root, A->right);	//recures down right subtree of A
	}
}
#endif
