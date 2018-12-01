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




//////////////////////////////////////////////////////////////

void bst_print_dot_null(int data, int nullcount, FILE* stream)
{
    fprintf(stream, "    null%d [shape=point];\n", nullcount);
    fprintf(stream, "    %d -> null%d;\n", data, nullcount);
}

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


