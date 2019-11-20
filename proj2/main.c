#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bst.h"

int main(){
	node *root=NULL, *temp, *root2=NULL;
	article *rootArticle=NULL, *tempArticle;
	char* str = malloc(sizeof(char)*20);
	char* id = malloc(sizeof(char)*20);
	sprintf(str, "sean");
	sprintf(id, "1830.3195");
	temp=createNode(str);
	tempArticle = createArticle(id);

	root = temp; //have to initialize the BST before inserting nodes. Error
				 //checking for that in the function proved to be more trouble
				 //than it was worth
	root->articles = tempArticle;

	sprintf(id, "penis-tiddies");
	tempArticle = createArticle(id);
	insertNode(root, temp, tempArticle);

	sprintf(id, "testacle-tiddies");
	tempArticle = createArticle(id);
	insertNode(root, temp, tempArticle);

	//-------------------------


	temp = createNode(str); //create a second tree to test merging
	//sprintf(str, "will");
	sprintf(id, "1111.1111");
	//temp = createNode(str);
	tempArticle = createArticle(id);
	
	root2 = temp;
	root2->articles = tempArticle;

	sprintf(id, "2222.2222");
	tempArticle = createArticle(id);
	insertNode(root2, temp, tempArticle);

	
	mergeTrees(root, root2);

	printf("preorder traversal\n");
	printNodes(root);
	printArticles(root->articles);
	printf("\n");
	return 0;
}
