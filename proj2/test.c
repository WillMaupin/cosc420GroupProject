#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#include "hash.h"
#include "node.h"

int main(){
    HashMap map;        // = malloc(sizeof(HashMap));
    initHashMap(&map, 23);

    // printf("%s\n", map.head->data);

    return 0;
}
