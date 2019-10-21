#include <stdio.h>

int main(int argc, char** argv){
	FILE *fp;
	fp = fopen("./enumeration", "r");
	if(fp == NULL){
		printf("Error opening file");
		return 1;
	}
	char line[20];
	char str1[9], str2[9], str3[9], str4[9];

	while(fgets(line, sizeof(line), fp)){
		printf("%s", line);
	}

	fclose(fp);
	return 0;
}
