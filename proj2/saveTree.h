//saveTree.h
#ifndef SAVETREE_H
#define SAVETREE_H


/*
    write

*/

void writeTree(node* tree, FILE* file){

    if(tree!=NULL){
        // write root
        printf("%s\n", tree->keyword);

        // move to left subtree
        writeTree(tree->left, file);

        // move to right subtree
        writeTree(tree->right, file);
    }

    printf("tree saved to ");
}

void saveTree(node* tree){
    FILE *file = fopen("tree.dat", "w+");
    if (file) {
        printf("file open\n");
    }

    writeTree(tree,file);
}

#endif
