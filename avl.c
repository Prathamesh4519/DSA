#include <stdio.h>
#include <stdlib.h>
#include <math.h>
struct tree{
    int data;
    int height;
    struct tree* left;
    struct tree* right;
};
typedef struct tree tree;

int get_height(tree* root){
    if(!root){
        return -1;
    }
    return root->height;
}

tree* right(tree* root){
    tree* temp=root->left;
    root->left=temp->right;
    temp->right=root;

    root->height = fmax(get_height(root->left), get_height(root->right)) + 1;
    temp->height = fmax(get_height(temp->left), get_height(temp->right)) + 1;
    return temp;
}
tree* left(tree* root){
    tree* temp=root->right;
    root->right=temp->left;
    temp->left=root;

    root->height = fmax(get_height(root->left), get_height(root->right)) + 1;
    temp->height = fmax(get_height(temp->left), get_height(temp->right)) + 1;
    return temp;
}

tree* rl(tree* root){
    root->left=right(root->left);
    return left(root);
}

tree* lr(tree* root){
    root->right=left(root->right);
    return right(root);
}

tree* ip(tree* root){
    if(root->left){
        tree* temp=root->left;
        while(temp->right){
            temp=temp->right;
        }
        return temp;
    }else{
        return root;
    }
}

int bf(tree* root){
    return get_height(root->left)-get_height(root->right);
}

tree* delete(tree* root,int data){
    if(root->data<data){
        root->right=delete(root->right,data);
        
    }else if(root->data>data){
        root->left=delete(root->left,data);
        
    }else{   
        if(root->left&&root->right){
            tree* temp=ip(root);
            root->data=temp->data;
            root->left=delete(root->left,root->data);
        }else if(root->left||root->right){
            if(root->left){
                tree* child=root->left;
                free(root);
                return child;
            }
            if(root->right){
                tree* child=root->right;
                free(root);
                return child;
            }
        }else{
            free(root);
            return NULL;
        }

    }
    root->height=fmax(get_height(root->left),get_height(root->right))+1;
        if(bf(root)>1){
            if(bf(root->left)>=0){
                root=right(root);
            }else{
                root=lr(root);
            }
        }

        if(bf(root)<-1){
            if(bf(root->right)<=0){
                root=left(root);
            }else{
                root=rl(root);
            }
        }

    
    return root;
}




tree *insert(tree *root, int data)
{
    if (!root)
    {
        tree *new = (tree *)malloc(sizeof(tree));
        new->data = data;
        new->left = NULL;
        new->right = NULL;
        new->height = 0;
        root = new;
    }
    else if (root->data > data)
    {
        root->left = insert(root->left, data);
        if (get_height(root->left) - get_height(root->right) == 2)
        {
            if (root->left->data > data)
            {
                root = right(root);
            }
            else
            {
                root = lr(root);
            }
        }
    }
    else if (root->data < data)
    {
        root->right = insert(root->right, data);
        if (get_height(root->right) - get_height(root->left) == 2)
        {
            if (root->right->data < data)
            {
                root = left(root);
            }
            else
            {
                root = rl(root);
            }
        }
    }

    root->height = fmax(get_height(root->left), get_height(root->right)) + 1;
    return root;
}

void inorder(tree *root)
{
    if (!root)
    {
        return;
    }
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}
void preorder(tree *root)
{
    if (!root)
    {
        return;
    }
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

int main()
{
    tree *root = NULL;
    int n;
    printf("Enter the number of nodes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        int data;
        printf("Enter the value :");
        scanf("%d", &data);
        root = insert(root, data);
    }
    inorder(root);
    printf("\n");
    preorder(root);
    return 0;
}