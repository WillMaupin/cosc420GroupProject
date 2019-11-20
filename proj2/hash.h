#ifndef HASH_H
#define HASH_H

#include <crypt.h>
#include <string.h>
// #include "list.h"
#include "node.h"

typedef struct HashTable {
    // Node *head,         //points to first bucket node
        //  *b_contents;  //points to contents of bucket (article, node struct)

    Node** table;

    int size;   //size of HashTable
} HashTable;

/*
    assigns key value to bucket based on keyword string
    ex:
*/
void hash(HashTable* map, Node* node){
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
void insert(HashTable* map, Node* node){
    hash(map, node);
}

/*
*/
void initHashTable(HashTable* table, int size){
    /*want to create HashTable with size s*/
    /*  TEST CODE
    char* a = NULL;
    Node temp = {a,2,NULL};
    printf("data: %s\n", temp.data);
    printf("key: %d\n", temp.key);
    printf("next: %s\n", temp.next);
    */

    // table->size = size;   //set hash table size

    // printf("%u\n", sizeof(table->table));
    // table->table = malloc(sizeof(Node*) * size);
    // for(int i=0; i<size; i++){
    //     Node* temp = {};
    //     table->table[i] =
    // }
    // printf("%u\n", sizeof(table->table));



/*
    Node head;
    initBucket(&head, 0);

    map->head = &head;
    // printf("%d\n", map->head->key);

    for(int i=1; i<size; i++){
        printf("\n========================\n");

        printf("%d\n", i);
        Node temp;
        initBucket(&temp, i);
        printf("t key: %d\n", temp.key);

        Node* ptr = map->head;
        printf("p key: %d\n", ptr->key);

        while(ptr->next){
            printf("while: p key: %d\n", ptr->key);
            ptr = ptr->next;
        }
        printf("ptr->key final: %d\n", ptr->key);
        ptr->next = &temp;
        if(ptr->next){printf("next: %d\n", ptr->next->key);}
        printf("here\n");

    }


    // if(map->head)   printf("%d\n", map->head->next->key);
    // printf("out\n\n");
    */
}

#endif
