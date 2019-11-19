#include<stdio.h>
#include<stdlib.h>

#include <string.h>
#include "hash.h"
#include "node.h"

int main(){
    HashMap map;        // = malloc(sizeof(HashMap));
    initHashMap(&map, 7);

    printf("map: %lu\n", sizeof(map));
    // printf("list: %lu\n", sizeof(map.list));
    printf("size: %d\n", map.size);
    printf("\n");

    Node test_node;
    char* str = malloc(sizeof(char) * 4);
    str = "test";
    initKeywordNode(&test_node, str);
    insert(&map, &test_node);
    printf("%d\n", test_node.key);

    Node test_node1;
    // (str);
    char* str1 = malloc(sizeof(char) * 5);
    str1 = "test8";
    initKeywordNode(&test_node, str1);
    insert(&map, &test_node1);
    printf("%d\n", test_node1.key);


    return 0;
}
