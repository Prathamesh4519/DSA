#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct avl
{
int data;
int height;
struct avl*left;
struct avl*right;
};
typedef struct avl tree;
int getheight(tree*root){
    if(root==NULL){
return -1;
    }
    return root->height;
}
tree* rotate_right(tree*root){
tree*temp=root->left;
root->left=temp->right;
temp->right=root;

root->height=fmax(getheight(root->left),getheight(root->right))+1;
temp->height=fmax(getheight(temp->left),getheight(temp->right))+1;
return temp;
}
tree* rotate_left(tree*root){
tree*temp=root->right;
root->right=temp->left;
temp->left=root;

root->height=fmax(getheight(root->left),getheight(root->right))+1;
temp->height=fmax(getheight(temp->left),getheight(temp->right))+1;
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
tree*inorderpred(tree*root){
    if(root->left){
        tree*temp=root->left;
        while(temp->right){
            temp=temp->right;
        }
        return temp;
    }
    return root;
}
int balancefact(tree*root){
    return getheight(root->left)-getheight(root->right);
}
tree*insert(tree*root,int val){
    if(root==NULL){
tree*newnode=(tree*)malloc(sizeof(tree));
    newnode->data=val;
    newnode->left=NULL;
    newnode->right=NULL;
    newnode->height=0;
    root=newnode;
    }
    
    

}