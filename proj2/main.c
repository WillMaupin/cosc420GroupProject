#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bst.h"

int main(){
	node *root=NULL, *temp, *root2=NULL, *root3=NULL;
	article *rootArticle=NULL, *tempArticle;
	char* str = malloc(sizeof(char)*20);
	char* id = malloc(sizeof(char)*20);
	sprintf(str, "sean:");
	//sprintf(id, "1830.3195");
	temp=createNode(str);
	tempArticle = createArticle(id);

	root = temp; //have to initialize the BST before inserting nodes. Error
				 //checking for that in the function proved to be more trouble
				 //than it was worth
	root->articles = tempArticle;

	sprintf(id, "the weed");
	tempArticle = createArticle(id);
	insertNode(root, temp, tempArticle);

	sprintf(id, "im calling");
	tempArticle = createArticle(id);
	insertNode(root, temp, tempArticle);

	//-------------------------


	temp = createNode(str); //create a second tree to test merging
	sprintf(str, "matt:");
	sprintf(id, "police");
	temp = createNode(str);
	tempArticle = createArticle(id);
	
	root2 = temp;
	root2->articles = tempArticle;

	sprintf(id, "is that a");
	tempArticle = createArticle(id);
	insertNode(root2, temp, tempArticle);

	sprintf(str, "will:");
	sprintf(id, "420 what you smokin");
	temp = createNode(str);
	tempArticle = createArticle(id);
	root3 = temp;
	root3->articles = tempArticle;
	insertNode(root3, temp, tempArticle);

	mergeTrees(root, root2);
	mergeTrees(root, root3);
	FILE *fp;
	fp = fopen("treez.txt", "w");
	printf("preorder traversal\n");
	printNodes(root);
	printArticles(root->articles);
	writeWords(root, fp);
	printf("\n");
	return 0;
}
