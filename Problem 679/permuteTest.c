#include <stdio.h>
#include <stdlib.h>

void addToArray(int *add, int length, int* arr){
	int index = 0;
	while(arr[index] != -1)
		index++;
	for(int i = 0; i <= length; i++)
		arr[i+index] = add[i];
}

void swap(int *x, int *y){
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

void permute(int *a, int l, int r, int *permutations){
	int i;
	if(l == r){
		addToArray(a, r, permutations);
	} else {
		for(i = l; i <= r; i++){
			swap((a+l), (a+i));
			permute(a, l+1, r, permutations);
			swap((a+l), (a+i));
		}
	}
}

void removeDuplicates(int* permutations, int r, int s){//, int* new, int* newSize){
	int counter = 0;
	for(int i = 0; i < r; i++){
		for(int j = 0; j < r; j++){
			if(j != i){
				int flag = 0;
				for(int k = 0; k < s; k++)
					if(permutations[(i*s)+k] != permutations[(j*s)+k]){
						flag = 1;
						break;
					}
				if(flag == 0){
					for(int k = 0; k < s; k++)
						permutations[(j*s)+k] = -1;
				}
			}
		}
	}
	
	for(int i = 0; i < 120; i++){
		if(permutations[i*5] != -1)
			counter++;
	}
	
	//*newSize = counter;
	//new = malloc(sizeof(int)*counter*5);
	
	//FILE *fp;
	//fp = fopen("

	counter = 0;
	for(int i = 0; i < r; i++){
		if(permutations[(i*s)] != -1){
			for(int j = 0; j < s; j++){
	//			new[(counter*s)+j] = permutations[(i*s)+j];
				printf("%d ", permutations[(i*s)+j]);
			}	
			printf("\n");
			counter++;
		}
	}
}

int main(){
	int* arr = malloc(sizeof(int) * 5);
	int* permutations = malloc(sizeof(int)*5*120);

	for(int i = 0; i < 5*120; i++)
		permutations[i] = -1;
	
/*	arr[0] = 5;
	arr[1] = 4;
	arr[2] = 1;
	arr[3] = 1;
	arr[4] = 1;
*/
	FILE *fp = fopen("enumeration", "r");
	char line[256];
	int* eLines = malloc(sizeof(int) * 4);
	while(fgets(line, 256, fp)){
//		int numRead = sscanf(line, "%d", eLines[0]);// %d %d %d", eLines[0], eLines[1], eLines[2], eLines[3]);
		printf("%c\n", line);
	//	for(int i = 0; i < numRead; i++)
	//		printf("%d", eLines[i]);
//		printf("\n");
//
	}

	permute(arr, 0, 4, permutations);

	int* permutationsFinal;
	int sizePermutationsFinal;
	removeDuplicates(permutations, 120, 5);//, permutationsFinal, &sizePermutationsFinal);

	for(int i = 0; i < sizePermutationsFinal; i++){
		for(int j = 0; j < 5; j++){
//			printf("%d ", permutationsFinal[(i*5)+j]);
		}
//		printf("\n");
	}
	free(arr);
}
