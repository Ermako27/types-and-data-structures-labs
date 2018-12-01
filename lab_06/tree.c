#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"


 
// #define CMP_EQ(a, b) ((a) == (b))
#define CMP_LT(a, b) ((a) <= (b))
#define CMP_GT(a, b) ((a) > (b))


Node* getFreeNode(int value, char *word, Node *parent) 
{
    Node* tmp = (Node*) malloc(sizeof(Node));
    tmp->left = tmp->right = NULL;
    tmp->data = value;
    tmp->word = word;
    tmp->parent = parent;
    return tmp;
}



void insert(Node **head, int value, char *word) // вставка в дерево
{
    Node *tmp = NULL;
    Node *ins = NULL;
    if (*head == NULL) 
    {
        *head = getFreeNode(value, word, NULL);
        return;
    }
     
    tmp = *head;
    while (tmp) 
    {
        if (CMP_GT(value, tmp->data)) 
        {
            if (tmp->right) 
            {
                tmp = tmp->right;
                continue;
            } 
            else 
            {
                tmp->right = getFreeNode(value, word, tmp);
                return;
            }
        } 
        else if (CMP_LT(value, tmp->data)) 
        {
            if (tmp->left) 
            {
                tmp = tmp->left;
                continue;
            } 
            else 
            {
                tmp->left = getFreeNode(value, word, tmp);
                return;
            }
        } 
    }
}



Node* getMinNode(Node *root) // минимальный элемент
{
    while (root->left) 
    {
        root = root->left;
    }
    return root;
}




Node* getMaxNode(Node *root) // максимальный элемент
{
    while (root->right) 
    {
        root = root->right;
    }
    return root;
}

Node *getNodeByValue(Node *root, int value, char *word, int *cmp_count) // поиск в дереве
{
    *cmp_count = 0;

    while (root) 
    {
        if (CMP_GT(value, root->data)) 
        {
            *cmp_count += 1;
            root = root->right;
            continue;
        } 
        else if (CMP_LT(value, root->data)) 
        {
        	if (strcmp(root->word, word) == 0)
        		return root;
        	else
        	{
                *cmp_count += 1;
        		root = root->left;
            	continue;
        	}
        } 
    }
    return NULL;
}



void removeNodeByPtr(Node *target) 
{
    if (target->left && target->right) 
    {
        Node *localMax = getMaxNode(target->left);
        target->data = localMax->data;
        removeNodeByPtr(localMax);
        return;
    } 
    else if (target->left) 
    {
        if (target == target->parent->left) 
        {
            target->parent->left = target->left;
        } 
        else 
        {
            target->parent->right = target->left;
        }
    } 
    else if (target->right) 
    {
        if (target == target->parent->right) 
        {
            target->parent->right = target->right;
        } 
        else 
        {
            target->parent->left = target->right;
        }
    } 
    else 
    {
        if (target == target->parent->left) 
        {
            target->parent->left = NULL;
        }
        else 
        {
            target->parent->right = NULL;
        }
    }
    free(target);
}



void deleteValue(Node *root, int value, char *word) 
{
    int c;
    Node *target = getNodeByValue(root, value, word, &c);
    removeNodeByPtr(target);
}





void printTree(Node *root, const char *dir, int level) 
{
    if (root) 
    {
        printf("lvl %d %s = %d %s\n", level, dir, root->data,root->word);
        printTree(root->left, "left", level+1);
        printTree(root->right, "right", level+1);
    }
}


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
    printf("%s, %d | ", current->word, current->data);
}





void bst_print_dot_null(char *word, int nullcount, FILE* stream)
{
    fprintf(stream, "    null%d [shape=point];\n", nullcount);
    fprintf(stream, "    %s -> null%d;\n", word, nullcount);
}

void bst_print_dot_aux(Node* node, FILE* stream)
{
    static int nullcount = 0;

    if (node->left)
    {
        fprintf(stream, "    %s -> %s;\n", node->word, node->left->word);
        bst_print_dot_aux(node->left, stream);
    }
    else
        bst_print_dot_null(node->word, nullcount++, stream);

    if (node->right)
    {
        fprintf(stream, "    %s -> %s;\n", node->word, node->right->word);
        bst_print_dot_aux(node->right, stream);
    }
    else
        bst_print_dot_null(node->word, nullcount++, stream);
}

void bst_print_dot(Node* tree, FILE* stream)
{
    fprintf(stream, "digraph BST {\n");
    fprintf(stream, "    node [fontname=\"Arial\"];\n");

    if (!tree)
        fprintf(stream, "\n");
    else if (!tree->right && !tree->left)
        fprintf(stream, "    %s;\n", tree->word);
    else
        bst_print_dot_aux(tree, stream);

    fprintf(stream, "}\n");
}


/*
void bst_print_dot_null(char *word, int data, int nullcount, FILE* stream)
{
    fprintf(stream, "    null%d [shape=point];\n", nullcount);
    fprintf(stream, "    '%s, %d' -> null%d;\n", word, data, nullcount);
}

void bst_print_dot_aux(Node* node, FILE* stream)
{
    static int nullcount = 0;

    if (node->left)
    {
        fprintf(stream, "    %s, %d -> %s, %d;\n", node->word, node->data, node->left->word, node->left->data);
        bst_print_dot_aux(node->left, stream);
    }
    else
        bst_print_dot_null(node->word, node->data, nullcount++, stream);

    if (node->right)
    {
        fprintf(stream, "    %s, %d -> %s %d;\n", node->word, node->data, node->right->word, node->right->data);
        bst_print_dot_aux(node->right, stream);
    }
    else
        bst_print_dot_null(node->word, node->data, nullcount++, stream);
}

void bst_print_dot(Node* tree, FILE* stream)
{
    fprintf(stream, "digraph BST {\n");
    fprintf(stream, "    node [fontname=\"Arial\"];\n");

    if (!tree)
        fprintf(stream, "\n");
    else if (!tree->right && !tree->left)
        fprintf(stream, "    %s;\n", tree->word);
    else
        bst_print_dot_aux(tree, stream);

    fprintf(stream, "}\n");
}
*/
