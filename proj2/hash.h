#ifndef HASH_H
#define HASH_H

#include <crypt.h>
#include <string.h>
// #include "list.h"
#include "node.h"

typedef struct HashMap {
    Node *head,         //points to first bucket node
         *b_contents;  //points to contents of bucket (article, node struct)

    int size;   //size of hashmap
} HashMap;

/*
*/
void hash(HashMap* map, Node* node){
    int len = strlen(node->data);
    int key = 1;

    for(int i=0; i<len; i++){
        // printf("%c: %d\n", data[i], data[i]);
        key *= node->data[i];
        printf("%d\n", key);
    }

    key %= map->size;
    node->key = key;
    printf("key: %d\n", key);
    printf("key: %d\n", node->key);
    // return key;
}

/*
*/
void insert(HashMap* map, Node* node){
    hash(map, node);
}

/*
*/
void initHashMap(HashMap* map, int size){
    /*want to create hashmap with size s*/
    map->size = size;   //set hash table size

    Node temp;
    initBucket(&temp, 0);

    map->head = &temp;
    // printf("%d\n", map->head->key);

    for(int i=1; i<size; i++){
        Node temp;
        initBucket(&temp, i);
        Node* ptr = map->head;
        // if(ptr){printf("next\n");}

        while(ptr->next){
            printf("one\n");
            ptr = ptr->next;
        }
        printf("here\n");
    }
}

#endif
