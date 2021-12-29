#ifndef ARBRE_H
#define ARBRE_H

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
}BinTree, Node;

BinTree *empty_bintree();
Node *create_node(int data);
BinTree *insert(BinTree *bt, int data);
BinTree *search(BinTree *bt, int data);
void printBT(BinTree *bt);
BinTree *freeBT(BinTree *bt);
int lenBT(BinTree *bt);

#endif
