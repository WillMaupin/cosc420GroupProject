#ifndef HASH_TABLE
#define HASH_TABLE

struct RefsLL{
	char id[20];
	struct RefsLL* next; //ptr to next node
};

//contains an article and a linked list of references
struct Article{
	char id[20];
	char name[100];
	char authors[100];
	char abstract[2000];
	struct RefsLL* head;
};

//list of articles, to be the "buckets" for the hash table
struct ArticleLL{
	struct Article* article;
	struct ArticleLL* next;
};

// table is a hash table of article linked lists (list since more than one
// entry can be hashed to the same bucket)
struct Table{
	int entries;
	struct ArticleLL* articles; //array of article structs
};

//initialize a references linked list inside an article struct
void initRefsLL(struct Article* A){
	struct RefsLL r;
	r.id[0] = '\0';
	r.next = NULL;
	A->head = &r;
}

void initArticle(struct Article *A){
	A->id[0] = '\0';
	A->name[0] = '\0';
	A->authors[0] = '\0';
	A->abstract[0] = '\0';
	initRefsLL(A);
}

//adds an article to the hash table, make sure id is null terminated
void addArticle(struct Table *T, struct Article* A){
	//do hash function
	int hash = 1;
	for(int i = 0; i < 20; i++){
		hash *= (int)A->id[i];
		if(A->id[i] == '\0')
			i = 20;
	}
	hash %= T->entries;

	printf("You\n");

	struct ArticleLL* ptr = T->articles[hash].next;

	printf("fuck\n");
	while(ptr->next != NULL){
		ptr = ptr->next;
		printf("benis\n");
	}
	ptr->next->article = A;
	printf("PEnis\n");
}

//add node to a linked list, make sure id is null terminated
void addRefNode(struct RefsLL* refs, char* id){
	struct RefsLL* newNode;
	int i = 0;
	while(1){
		newNode->id[i] = id[i];
		if(id[i] == '\0')
			break;
		if(i > 20)
			printf("Error entering reference, is ID null-terminated?\n");
	}
	newNode->next = NULL;
	refs->next = newNode;
}

//initialize article linked list
void initArticleLL(struct Table *T, int index){
	struct ArticleLL newArticleLL;
	struct Article firstArticle;
	initArticle(&firstArticle);
	newArticleLL.article = &firstArticle;
	newArticleLL.next = NULL;
	T->articles = &newArticleLL;
}

//initilize the hash table
void initTable(struct Table *T, int n){
	T->entries = n;
	T->articles = malloc(sizeof(struct articleLL*));
	for(int i = 0; i < n; i++){
		initArticleLL(T, i);
	}
}

void printArticle(struct Table *T, char* id){
	
}

#endif
