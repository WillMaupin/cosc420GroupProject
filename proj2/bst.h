#ifndef BST_H
#define BST_H
#include "matrixmult.h"
//#include"matrix.h"
#define INDEX(n,m,i,j) m*i + j
#define ACCESS(A,i,j) A->arr[INDEX(A->rows, A->cols, i, j)]

/*
typedef struct ReferencesBST{
	char* id;
	struct ReferencesBST *left;
	struct ReferencesBST *right;
}ref;
*/

/*typedef struct matrix{
  int rows, cols;
  float* arr;
} matrix;*/

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
void writeWords();
void writeArticles();
void readMetaData();

void my(matrix* A, int r, int c){
  A->rows = r;
  A->cols = c;
  A->arr = malloc(r*c*sizeof(int));
  int i,j;
  ACCESS(A,0,0) = 0;
  ACCESS(A,0,1) = 0;
  ACCESS(A,0,2) = 1;
  ACCESS(A,1,0) = 0;
  ACCESS(A,1,1) = 0;
  ACCESS(A,1,2) = 1;
  ACCESS(A,2,0) = 0;
  ACCESS(A,2,1) = 0;
  ACCESS(A,2,2) = 0;
}

void initMatrix(matrix* A, int r, int c){
  A->rows = r;
  A->cols = c;
  A->arr = malloc(r*c*sizeof(int));
  int i,j;
  for(i=0; i<r; i++)
    for(j=0; j<c; j++)
      ACCESS(A,i,j) = rand() % 10 + 1;
}

//initializes matrix with all values 1
void initOneMatrix(matrix* A, int r, int c){
  A->rows = r;
  A->cols = c;
  A->arr = malloc(r*c*sizeof(int));
 
  int i,j;
  for(i=0; i<r; i++)
    for(j=0; j<c; j++)
      ACCESS(A,i,j) = 1;
}

void initEmptyMatrix(matrix* A, int r, int c){
  A->rows = r;
  A->cols = c;
  A->arr = malloc(r*c*sizeof(int));
 
  int i,j;
  for(i=0; i<r; i++)
    for(j=0; j<c; j++)
      ACCESS(A,i,j) = 0;
}

void printMatrix(matrix* A){
  int i,j;
  for(i=0; i<A->rows; i++){
    for(j=0; j<A->cols; j++){
      printf("%d ", ACCESS(A,i,j));
    }
    //printf("\n");
    puts("");
  }
}

//Pass in original matrix and one other. Transpose of matrix A will be written into matrix B
void transpose(matrix* A, matrix* B){
	int i,j;
	for(i=0; i<A->cols; i++){
		for(j=0; j<A->rows; j++){
			int index = INDEX(A->rows, A->cols, i, j);
			int index2 = INDEX(A->rows, A->cols, j, i);
			B->arr[index] = A->arr[index2];
   		}
	}
}

void multMatrix(matrix* A, matrix* ones){
	int i, j, add=0;
	for(i=0; i<A->rows; i++){
		for(j=0; j<A->cols; j++){
			int index = INDEX(A->rows, A->cols, i, j);
			int index2 = INDEX(ones->rows, ones->cols, i, 0);
			add = add + (A->arr[index]*ones->arr[index2]);
		}
	ones->arr[i] = add;
	add=0;
	}
}

void hits(matrix* A, matrix *B, matrix *C, matrix *T,int rank){
	if(rank==0){
		printf("Matrix is: \n");
		printMatrix(A);
		printf("transpose is \n");
		transpose(A,T);
		printMatrix(T);
	}
	matrixMult(T, B, C);
	if(rank==0){
		printf("Initial authority weights are:\n");
		printMatrix(C);
	}
	matrixMult(A, C, B);
	if(rank==0){
		printf("Initial hub weights are:\n");
		printMatrix(B);
	}	
	
}

//Searches based on keyword entered by user and prints all articles associated with that word
void searchBST(node *root, char *word){
	node *curr=root;
	int c;
	//printf("HERE %s\n", curr->keyword);
	while((c=strcmp(word, curr->keyword)) != 0)
	{
		if(c<0){
			if(curr->left != NULL){
				curr=curr->left;
			}
			else{
				printf("Couldn't find\n");
				return;
			}
		}
		else if(c>0){
			if(curr->right != NULL){
				curr=curr->right;
			}
			else{
				printf("Couldn't find\n");
				return;
			}
		}
	}
	if(c==0){
		printArticles(curr->articles);
		printf("\n");
		return;
	}
}

void buildBST(node *root, FILE *fp){
	char *a;
	char c;
	char d[20];
	for(int i=0; i<20; i++)
	{
		d[i] = '\0';
	}
	int i, count = 0;
	int newline = 1; //bool to determine if node is to be 				 //created
	article *tempArticle=NULL;
	node *temp=NULL;
	while((c = fgetc(fp)) != EOF)
	{
		//printf("d=%s\n", d);
		if(c == ' ')
		{
			if(newline == 1)
			{
				//a=d;
				temp=createNode(d);
				newline = 0;
				for(i = 0; i<count+1; i++)
				{
					d[i] = '\0';
				}
				count=0;
			}
			else
			{
				//a = d;
				tempArticle=createArticle(d);
				insertNode(root, temp, tempArticle);
				for(i = 0; i<count+1; i++)
				{
					d[i] = '\0';
				}
				count=0;
			
			}
		}
		else if(c == '\n')
		{
			//a=d;
			tempArticle=createArticle(d);
			insertNode(root, temp, tempArticle);
			for(i = 0; i<20; i++)
			{
				d[i] = '\0';
			}
			newline = 1;
			count=0;
		}
		else{
			d[count] = c;
			count++;
		}
	}
}

//Inorder traversal of articles
void writeArticles(article *root, FILE *fp){
	if(root != NULL)
	{
		writeArticles(root->left, fp);
		writeArticles(root->right, fp);
		fprintf(fp, "%s", root->id);
		fprintf(fp, " ");
	}
}

//Inorder traversal of words
void writeWords(node *root, FILE *fp){
	if(root != NULL)
	{
		writeWords(root->left, fp);
		writeWords(root->right, fp);
		fprintf(fp, "%s", root->keyword);
		fprintf(fp, " ");
		writeArticles(root->articles, fp);
		fprintf(fp, "\n");
	}
}

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
