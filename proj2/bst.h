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
void writeWords();
void writeArticles();
void readMetaData();

/*void readMetaData(MPI_Comm world, int rank, int nprocs){
    int i, send=0, j;
    unsigned long long indexArr[2] = {0,0};
    MPI_File input; 
    MPI_File_open(world, "arxiv-metadata.txt", MPI_MODE_RDONLY, MPI_INFO_NULL, &input);
    if(rank == 0){
     int distr = maxNumLines/nprocs;
     int procDistr = distr;
     char c;
     unsigned long long index = 0;
     for(i=0; i<maxNumLines; i++){
       while(1){
	 MPI_File_read(input, &c, 1, MPI_CHAR, MPI_STATUS_IGNORE);
	// printf("%c", c);
	 indexArr[1]++;
	 if(c == '\n')
	   break;
	 if(c == '+' && i > procDistr){
	   printf("hello");
	    for(j=0; j<5; j++){
	       MPI_File_read(input, &c, 1, MPI_CHAR, MPI_STATUS_IGNORE);
			  printf("hello\n");
			  indexArr[1]++;
			  if(c != '+')
			    j = 6;
			    
	    }
	    if(j == 5){
	       indexArr[1]-1;
	       MPI_Send(&indexArr[0], 2, MPI_UNSIGNED_LONG_LONG, send,0, world);
	       printf("hello\n");
	       indexArr[0] = indexArr[1]+1;
	       send++;
	       procDistr += distr; 
	    }
       }	
     }
   }
}*/

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
				exit(1);
			}
		}
		else if(c>0){
			if(curr->right != NULL){
				curr=curr->right;
			}
			else{
				printf("Couldn't find\n");
				exit(1);
			}
		}
	}
	if(c==0){
		printArticles(curr->articles);
		printf("\n");
		exit(0);
	}
}

void buildBST(node *root, FILE *fp){
	char *a;
	char c, d[20];
	int i, count = 0;
	int newline = 1; //bool to determine if node is to be 				 //created
	article *tempArticle=NULL;
	node *temp=NULL;
	while((c = fgetc(fp)) != EOF)
	{
		printf("d=%s\n", d);
		if(c == ' ')
		{
			if(newline == 1)
			{
				//a=d;
				temp=createNode(d);
				newline = 0;
				for(i = 0; i<20; i++)
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
				for(i = 0; i<20; i++)
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
