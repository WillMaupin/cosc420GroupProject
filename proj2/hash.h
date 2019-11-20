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
    assigns key value to bucket based on keyword string
    ex:
*/
void hash(HashMap* map, Node* node){
    int len = strlen(node->data);
    int key = 1;

    /* multiply ascii values of all chars in word*/
    for(int i=0; i<len; i++){
        key *= node->data[i];
        printf("%d\n", key);
    }

    /* mod by table size so that each bucket is numbered 0-N, where N is the
    size of the table*/
    key %= map->size;
    node->key = key;    //assign key to bucket

    /* debugging statements*/
    printf("key: %d\n", key);
    printf("key: %d\n", node->key);
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
        // Node temp;
        // initBucket(&temp, i);
        // Node* ptr = map->head;
        // if(ptr){printf("next\n");}

        // while(ptr->next){
            // printf("one\n");
            // ptr = ptr->next        }
        // printf("here\n");
    }
}

#endif
