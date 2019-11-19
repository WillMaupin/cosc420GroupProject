#ifndef NODE_H
#define NODE_H

// can be used for both hashmap buckets and keyword nodes
// do we want seperate structs for each?
typedef struct Node {
    char* data;     // hashmap: unused?
                    // article node: article ids???

    int key;        // hashap: key of bucket,
                    // keyword: which bucket it belongs to

    struct Node* next; //next keyword node in bucket
} Node;

void initKeywordNode(Node* node, char* s){
    node->data = s;
}

void initBucket(Node* node, int k){
    node->key = k;
}

#endif
