#include <stdio.h>
#include <stdlib.h>
#include "arbre.h"

BinTree *empty_bintree(){
    return NULL;
}

Node *create_node(int data){
    Node *node = malloc(sizeof(Node));
    if(!node) return NULL;
    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return node;
}

BinTree *insert(BinTree *bt, int data){
    BinTree *prec;
    BinTree *head = bt;

    if(!bt) return create_node(data);

    while(bt){
        prec = bt;
        if(data < bt->data){
            bt = bt->left;
        } else {
            bt = bt->right;
        }
    }

    if(data < prec->data){
        prec->left = create_node(data);
    } else {
        prec->right = create_node(data);
    }

    return head;
}

BinTree *search(BinTree *bt, int data){
    while(bt){
        if(data < bt->data){
            bt = bt->left;
        } else {
            if(data > bt->data){
                bt = bt->right;
            } else {
                return bt;
            }
        }
    }

    return NULL;
}

void printBT(BinTree *bt){
    if(bt){
        printBT(bt->left);
        if(bt->data < 10){
            printf("Ligne : 0 | Colonne : %d\n", bt->data);
        } else {
            int l = bt->data / 10;
            int c = bt->data % 10;
            printf("Ligne : %d | Colonne : %d\n", l, c);
        }
        printBT(bt->right);
    }
}

BinTree *freeBT(BinTree *bt){
    if(bt){
        bt->left = freeBT(bt->left);
        bt->right = freeBT(bt->right);
        free(bt);
    }
    return NULL;
}

int lenBT(BinTree *bt){
    if(!bt) return 0;
    return 1 + lenBT(bt->left) + lenBT(bt->right);
}
