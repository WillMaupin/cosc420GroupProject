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
#endif
