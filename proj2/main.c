#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bst.h"
#include "saveTree.h"

int main(){
	node *root=NULL, *temp, *root2=NULL;	//node declarations
	article *rootArticle=NULL, *tempArticle;	//article declarations
	char* str = malloc(sizeof(char)*20);	//used to store abtracts?
	char* id = malloc(sizeof(char)*20);		//used to store article ids
	sprintf(str, "sean");	//write "keyword" to str
	sprintf(id, "1830.3195");	//write "id" to is
	temp=createNode(str);	//create new node assigned to temp
	tempArticle = createArticle(id);	//create new article assigned to tempArticle

	/******************* root 1 ************************/
	root = temp; //have to initialize the BST before inserting nodes. Error
				 //checking for that in the function proved to be more trouble
				 //than it was worth

	root->articles = tempArticle;	//assign tempArticle to root articles bst

	sprintf(id, "penis-tiddies");	// write new temp id
	tempArticle = createArticle(id);	//create new article
	insertNode(root, temp, tempArticle);	//insert node to

	sprintf(id, "testacle-tiddies");
	tempArticle = createArticle(id);
	insertNode(root, temp, tempArticle);


	temp = createNode(str); //create a second tree to test merging
	sprintf(id, "1111.1111");
	tempArticle = createArticle(id);

	/******************* root 2 ************************/
	root2 = temp;
	root2->articles = tempArticle;

	sprintf(id, "2222.2222");
	tempArticle = createArticle(id);
	insertNode(root2, temp, tempArticle);


	/******************* merge *************************/
	mergeTrees(root, root2);

	printf("preorder traversal\n");
	printNodes(root);
	printArticles(root->articles);
	printf("\n");

	saveTree(root);

	return 0;
}
