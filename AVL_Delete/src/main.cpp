#include<iostream>

using namespace std;
struct node
{
    int element;
    struct node *left,*right;
    int ht;

};

node *insert(node *,int);
node *Delete(node *,int);
void preorder(node *);
void inorder(node *);
int height( node *);
node *rotateright(node *);
node *rotateleft(node *);
node *RR(node *);
node *LL(node *);
node *LR(node *);
node *RL(node *);
int balanceFactor(node *);
int main()
{
    node *root=NULL;
    int valor,n,i,option;
    do {
        cout << "1. Create AVL Tree\n";
        cout << "2. Delete Element\n";
        cout << "3. End Program\n";
        cout << "Enter your choice ";
        cin >> option;
        switch(option)
        {
            case 1: cout << "\nEnter no. of elements : ";
                    cin >> n;
                    root = NULL;
                    for( i = 0; i < n;i++) {

                        cout << "Enter element of tree ";
                        cin >> valor;
                        root = insert(root, valor);
                    }
                    cout << "\nPreorder sequence:\n";
                    preorder(root);
                    cout << "\n\nInorder sequence:\n";
                    inorder(root);
                    break;
             
            case 2: cout << "Enter a element to be deleted : ";
                    cin >> valor;
                    root = Delete(root,valor);
                    cout << "Preorder sequence:\n";
                    preorder(root);
                    cout << "\nInorder sequence:\n";
                    inorder(root);
                    break;
        }
    }while(option!=3);
    
    return 0;
}

node * insert(node *Tree,int valor)
    {
    if(Tree == NULL){
        Tree = (node*)malloc(sizeof(node));
        Tree -> element = valor;
        Tree -> left = NULL;
        Tree -> right = NULL;
    }
    else

    if(valor > Tree->element)        {

        Tree -> right = insert(Tree -> right, valor);
        if(balanceFactor(Tree) == -2)
            if( valor > Tree -> right -> element)
                Tree = RR(Tree);
            else
                Tree = RL(Tree);
    }

    else
    if(valor<Tree->element)
    {
        Tree -> left = insert(Tree -> left, valor);
        if(balanceFactor(Tree)==2)
            if(valor < Tree-> left -> element)
                Tree=LL(Tree);
            else
                Tree=LR(Tree);

    }

    Tree -> ht = height(Tree);

    return(Tree);
}

node * Delete(node *Tree, int valor)
{
    node *p;

    if(Tree == NULL)
    {
        return NULL;
    }
    else
    if(valor > Tree->element)    
    {
        Tree -> right = Delete(Tree -> right, valor);
        if(balanceFactor(Tree) == 2)
            if(balanceFactor(Tree -> left) >= 0)
                Tree = LL(Tree);
            else
                Tree = LR(Tree);
    }
    else
    if(valor < Tree -> element)
    {
        Tree -> left = Delete(Tree->left, valor);
            if(balanceFactor(Tree)==-2)    
                if(balanceFactor(Tree->right)<=0)
                    Tree=RR(Tree);
                else
                    Tree=RL(Tree);
                }
            else
            {
                if(Tree -> right != NULL)
                {
                    p = Tree -> right;

                    while(p -> left != NULL)
                        p = p -> left;

                        Tree -> element = p -> element;
                        Tree -> right = Delete(Tree -> right, p->element);

                        if(balanceFactor(Tree) == 2)
                            if(balanceFactor (Tree -> left) >= 0)
                                Tree=LL(Tree);
                            else
                                Tree=LR(Tree);
                }
                else
                return(Tree->left);
            }
    Tree ->ht = height(Tree);
    return(Tree);
}

int height(node *Tree)
{

    int lh,rh;
    if(Tree == NULL)
        return(0);
    if( Tree -> left == NULL)
        lh = 0;
    else
        lh = 1 + Tree -> left -> ht;

    if(Tree -> right == NULL)
        rh = 0;
    else
        rh=1+Tree->right->ht;

    if(lh > rh)
        return(lh);

    return(rh);
}

node * rotateright(node *valor)
{

    node *y;
    y = valor -> left;
    valor -> left = y -> right;
    y -> right = valor;
    valor -> ht = height(valor);
    y -> ht = height(y);
    return(y);
}

node * rotateleft(node *valor)
{
    node *y;
    y = valor -> right;
    valor -> right = y -> left;
    y -> left = valor;
    valor -> ht = height(valor);
    y -> ht = height(y);
    return(y);
}

// rotaciones dobles
node * RR(node *Tree) //right right
{

    Tree = rotateleft(Tree);
    return(Tree);
}

node * LL(node *Tree) //left left
{
    Tree = rotateright(Tree);
    return(Tree);
}

node * LR(node *Tree) //left right
{

    Tree -> left = rotateleft(Tree->left);
    Tree = rotateright(Tree);
    return(Tree);
}

node * RL(node *Tree) //right left
{
    Tree -> right = rotateright(Tree->right);
    Tree = rotateleft(Tree);
    return(Tree);
}

int balanceFactor(node *Tree)
{
    int lh,rh;
    if( Tree == NULL)
        return(0);
    if(Tree -> left == NULL)
        lh = 0;
    else
        lh = 1 + Tree->left->ht;
    if(Tree -> right == NULL)
        rh = 0;
    else
        rh = 1 + Tree -> right -> ht;
    return(lh-rh);
}

void preorder(node *Tree)
{
    if( Tree != NULL)
    {
        cout << "Balance factor " << Tree -> element << " " << balanceFactor(Tree) << endl;
        preorder(Tree->left);
        preorder(Tree->right);
    }
}

void inorder(node *Tree)
{

    if( Tree != NULL)
    {
        inorder(Tree->left);
        cout << "Balance Factor "<<Tree -> element<<" " << balanceFactor(Tree) << endl;
        inorder(Tree->right);
    }
}

    


