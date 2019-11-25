#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#include "hash.h"
#include "node.h"

int main(){
    HashTable t;        // = malloc(sizeof(HashTable));
    // initHashTable(&map, 23);
    // printf("%u\n", t.table);
    initHashTable(&t, 4);
    // printf("%u\n", t.table);


    // printf("hello\n");
    // if(map.head)    printf("%d\n", map.head->key); 
    // if(map.head)    printf("HEAD\n"); 
    // printf("final\n");

    return 0;
}