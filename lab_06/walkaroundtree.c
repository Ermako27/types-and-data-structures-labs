#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "walkaroundtree.h"

/*
Прямой (pre-order)
    Посетить корень
    Обойти левое поддерево
    Обойти правое поддерево
*/


void preOrderTravers(Node* root, void (*visit)(Node*, void*), void *params) 
{
    if (root) 
    {
        visit(root, params);
        preOrderTravers(root->left, visit, params);
        preOrderTravers(root->right, visit, params);
    }
}



/*
Симметричный или поперечный (in-order)
    Обойти левое поддерево
    Посетить корень
    Обойти правое поддерево
*/
 
void inOrderTravers(Node* root, void (*visit)(Node*, void*), void *params) 
{
    if (root) 
    {
        inOrderTravers(root->left, visit, params);
        visit(root, params);
        inOrderTravers(root->right, visit, params);
    }
}

/*
В обратном порядке (post-order)
    Обойти левое поддерево
    Обойти правое поддерево
    Посетить корень
*/
 
void postOrderTravers(Node* root, void (*visit)(Node*, void*), void *params) 
{
    if (root) 
    {
        postOrderTravers(root->left, visit, params);
        postOrderTravers(root->right, visit, params);
        visit(root, params);
    }
}

// функция visit

void printNode(Node *current, void *args) 
{
    printf("%d ", current->data);
}
