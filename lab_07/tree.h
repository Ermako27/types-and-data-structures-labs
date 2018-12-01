#ifndef structures_h
#define structures_h

#include "structures.h"

#endif


#ifndef __TREE__H__

#define __TREE__H__

Node* getFreeNode(int value, char *word, Node *parent);

void insert(Node **head, int value, char *word);

Node* getMinNode(Node *root);

Node* getMaxNode(Node *root);

Node *getNodeByValue(Node *root, int value, char *word, int *cmp_count);

void removeNodeByPtr(Node *target);

void deleteValue(Node *root, int value, char *word);

void printTree(Node *root, const char *dir, int level);

void height_setting(Node* root, int (*visit)(Node*));

void preOrderTravers(Node* root, void (*visit)(Node*, void*), void *params) ;

void inOrderTravers(Node* root, void (*visit)(Node*, void*), void *params);

void postOrderTravers(Node* root, void (*visit)(Node*, void*), void *params);

void printNode(Node *current, void *args);

// void bst_print_dot_null(char *word, int nullcount, FILE* stream);

void bst_print_dot_null(int data, int nullcount, FILE* stream);

void bst_print_dot_aux(Node* node, FILE* stream);

void bst_print_dot(Node* tree, FILE* stream);

int HeightOfTree(Node* node);

unsigned char height(Node* p);

int bfactor(Node* p);

void fixheight(Node* p);

Node* rotateright(Node* p);

Node* rotateleft(Node* q);

void l2rRotation(Node **root);

void r2lRotation(Node **root);

Node* balance(Node* p);

Node* insert_balance(Node* p, int k, char* word);

Node* balance_setting(Node* root, Node* (*visit)(Node*));

#endif
