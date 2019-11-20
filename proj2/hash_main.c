
#include <stdlib.h>
#include <stdio.h>
#include "hash_table.c"

int main(){
	char arr[5];
	arr[0] = 'c';

	struct Article A;
	initArticle(&A);
	sprintf(A.id, "test");

	struct Table T;
	initTable(&T, 100);

	printf("Hi\n");
	addArticle(&T, &A);
	printf("lo\n");
	return 0;
}
