#include "stdio.h"
#include "stdlib.h"

typedef enum { head, entry } tagField;

typedef struct entryNode {
    int row;
    int col;
    int value;
} entryNode;

typedef struct Matrix {
    struct Matrix* down;    
    struct Matrix* right;    
    tagField tag;
    union {
        entryNode entry;
        struct Matrix* next;
    } u;
} Matrix;

Matrix* createMatrix(int n, int m, int a[n][m]) {
    Matrix* mat = (Matrix*)malloc(sizeof(Matrix));
    mat->down = NULL;
    mat->right = NULL;
    mat->tag = entry;

    mat->u.entry.row = n;
    mat->u.entry.col = m;
    mat->u.entry.value = 0;

    int max = n > m ? n : m;
    Matrix* ptr = mat;

    ptr->right = (Matrix*)malloc(sizeof(Matrix));
    ptr = ptr->right;
    ptr->down = ptr;
    ptr->right = ptr;
    ptr->tag = head;
    ptr->u.next = NULL;

    while (max--) {
        ptr->u.next = (Matrix*)malloc(sizeof(Matrix)); 
        ptr = ptr->u.next;
        ptr->down = ptr;
        ptr->right = ptr;
        ptr->tag = head;
        ptr->u.next = NULL;
    }

    Matrix* temp;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j]) {
                ptr = mat->right;
                Matrix* node = (Matrix*)malloc(sizeof(Matrix));
                node->tag = entry;
                node->u.entry.row = i;
                node->u.entry.col = j;
                node->u.entry.value = a[i][j];
                node->right = node;
                node->down = node;

                for (int r = 0; r < i; r++) {
                    ptr = ptr->u.next;
                }
                temp = ptr;

                if (temp->right == ptr) {
                    ptr->right = node;
                    node->right = ptr;
                } else {
                    while (temp->right != ptr) {
                        if (temp->right->u.entry.col < j) {
                            temp = temp->right;
                        } else {
                            break;
                        }
                    }
                    node->right = temp->right;
                    temp->right = node;
                }

                ptr = mat->right;
                for (int c = 0; c < j; c++) {
                    ptr = ptr->u.next;
                }
                temp = ptr;

                if (temp->down == ptr) {
                    ptr->down = node;
                    node->down = ptr;
                } else {
                    while (temp->down != ptr) {
                        if (temp->down->u.entry.row < i) {
                            temp = temp->down;
                        } else {
                            break;
                        }
                    }
                    node->down = temp->down;
                    temp->down = node;
                }
            }
        }
    }

    return mat;
}

void printMatrix(Matrix* mat) {
    Matrix* ptr = mat->right;
    Matrix* temp;
    while (ptr->u.next) {
        temp = ptr;
        while (temp->right != ptr) {
            temp = temp->right;
            printf("Row: %d Col: %d Val: %d\n", 
                temp->u.entry.row, 
                temp->u.entry.col, 
                temp->u.entry.value);
        }
        ptr = ptr->u.next;
    }
}

int main() {
    int n = 4, m = 4;
    int a[4][4] = {
        {0, 0, 5, 0},
        {0, 8, 0, 0},
        {3, 0, 0, 7},
        {0, 0, 0, 0}
    };

    Matrix* mat = createMatrix(n, m, a);
    printMatrix(mat);
    return 0;
}