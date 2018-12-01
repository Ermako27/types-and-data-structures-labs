#include "structures.h"

#ifndef __WALKAROUNDTREE__H__

#define __WALKAROUNDTREE__H__

void preOrderTravers(Node* root, void (*visit)(Node*, void*), void *params) ;

void inOrderTravers(Node* root, void (*visit)(Node*, void*), void *params);

void postOrderTravers(Node* root, void (*visit)(Node*, void*), void *params);

void printNode(Node *current, void *args);

#endif
