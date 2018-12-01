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
    tmp->height = 1;
    tmp->data = value;
    tmp->word = word;
    tmp->parent = parent;
    return tmp;
}

// Node* getFreeNode_2(int value, char *word) 
// {
//     Node* tmp = (Node*) malloc(sizeof(Node));
//     tmp->left = tmp->right = NULL;
//     tmp->data = value;
//     tmp->word = word;
//     return tmp;
// }



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


void height_setting(Node* root, int (*visit)(Node*)) 
{
    if (root) 
    {
        root->height = visit(root);
        // printf("inside: %d\n", root->height);
        height_setting(root->left, visit);
        height_setting(root->right, visit);
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





// void bst_print_dot_null(char *word, int nullcount, FILE* stream)
// {
//     fprintf(stream, "    null%d [shape=point];\n", nullcount);
//     fprintf(stream, "    %s -> null%d;\n", word, nullcount);
// }

void bst_print_dot_null(int data, int nullcount, FILE* stream)
{
    fprintf(stream, "    null%d [shape=point];\n", nullcount);
    fprintf(stream, "    %d -> null%d;\n", data, nullcount);
}

// void bst_print_dot_aux(Node* node, FILE* stream)
// {
//     static int nullcount = 0;

//     if (node->left)
//     {
//         fprintf(stream, "    %s -> %s;\n", node->word, node->left->word);
//         bst_print_dot_aux(node->left, stream);
//     }
//     else
//         bst_print_dot_null(node->word, nullcount++, stream);

//     if (node->right)
//     {
//         fprintf(stream, "    %s -> %s;\n", node->word, node->right->word);
//         bst_print_dot_aux(node->right, stream);
//     }
//     else
//         bst_print_dot_null(node->word, nullcount++, stream);
// }
void bst_print_dot_aux(Node* node, FILE* stream)
{
    static int nullcount = 0;

    if (node->left)
    {
        fprintf(stream, "    %d -> %d;\n", node->data, node->left->data);
        bst_print_dot_aux(node->left, stream);
    }
    else
        bst_print_dot_null(node->data, nullcount++, stream);

    if (node->right)
    {
        fprintf(stream, "    %d -> %d;\n", node->data, node->right->data);
        bst_print_dot_aux(node->right, stream);
    }
    else
        bst_print_dot_null(node->data, nullcount++, stream);
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



/////////////////////////БАЛАНСИРОВКА//////////////////////////

int HeightOfTree(Node* node)
{
    if(node == NULL)
        return 0;
    int l, r;
    if (node->left != NULL)
    {
        l = HeightOfTree(node->left);
    }
    else 
        l = -1;
    if (node->right != NULL) 
    {
        r = HeightOfTree(node->right);
    }
    else 
        r = -1;
    
    int max = l > r ? l : r;
    return max+1;

}



unsigned char height(Node* p)
{
    return p?p->height:0;
}

int bfactor(Node* p)
{
    // printf("height: %d\n", height(p->right)-height(p->left) );
    return height(p->right)-height(p->left);
}

void fixheight(Node* p)
{
    unsigned char hl = height(p->left);
    unsigned char hr = height(p->right);
    p->height = (hl>hr?hl:hr)+1;
}

Node* rotateright(Node* p) // правый поворот вокруг p
{
    Node* q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}


Node* rotateleft(Node* q) // левый поворот вокруг q
{
    Node* p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}


void l2rRotation(Node **root) {
    Node *parent = NULL,
         *C = NULL,
         *a = NULL, 
         *b = NULL;
 
    a = (*root);
    parent = a->parent;
    b = a->right;
    if (b == NULL) {
        return;
    }
    C = b->left;
 
    b->left = a;
    a->right = C;
    if (C) {
        C->parent = a;
    }
    b->parent = parent;
    if (parent) {
        if (parent->left == a) {
            parent->left = b;
        } else {
            parent->right = b;
        }
    }
    a->parent = b;
    if (!parent) {
        *root = (*root)->parent;
    }
}
 
void r2lRotation(Node **root) {
    Node *parent = NULL,
         *C = NULL,
         *a = NULL, 
         *b = NULL;
 
    b = (*root);
    parent = b->parent;
    a = b->left;
    if (a == NULL) {
        return;
    }
    C = a->right;
 
    a->right = b;
    b->left = C;
    if (C) {
        C->parent = b;
    }
    a->parent = parent;
    if (parent) {
        if (parent->left == b) {
            parent->left = a;
        } else {
            parent->right = a;
        }
    }
    b->parent = a;
 
    *root = (*root)->parent;
}



Node* balance(Node* p) // балансировка узла p
{
    fixheight(p);
    if( bfactor(p)==2 )
    {
        if( bfactor(p->right) < 0 )
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if( bfactor(p)==-2 )
    {
        if( bfactor(p->left) > 0  )
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p; // балансировка не нужна
}


Node* insert_balance(Node* p, int k, char* word) // вставка ключа k в дерево с корнем p
{
    if( !p ) return getFreeNode(k, word, NULL);
    if( k<p->data)
        p->left = insert_balance(p->left,k,word);
    else
        p->right = insert_balance(p->right,k,word);
    return balance(p);
}


// Node* balance(Node* p) // балансировка узла p
// {
//     fixheight(p);
//     if( bfactor(p)==2 )
//     {
//         if( bfactor(p->right) < 0 )
//             r2lRotation(&(p->right));
//         l2rRotation(&p);
//         return p;
//     }
//     if( bfactor(p)==-2 )
//     {
//         if( bfactor(p->left) > 0  )
//             l2rRotation(&(p->left));
//         r2lRotation(&p);
//         return p;
//     }
//     return p; // балансировка не нужна
// }

Node* balance_setting(Node* root, Node* (*visit)(Node*)) 
{
    if (root) 
    {
        root = visit(root);
        // printf("inside: %d\n", root->height);
        balance_setting(root->left, visit);
        balance_setting(root->right, visit);
    }

    return root;
}