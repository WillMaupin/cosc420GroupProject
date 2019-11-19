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

void initHashMap(HashMap* map, int s){
    /*want to create hashmap with size s*/

    map->size = s;
    
    // Node* ptr = map->head;
    // for(int i=0; i<s; i++){
    //     Node* new_bucket;
    //     initBucket(new_bucket, i);
    //
    //     ptr->next = new_bucket;
    // }
}

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

void insert(HashMap* map, Node* node){
    hash(map, node);
}

#endif
