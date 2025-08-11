#include <stdio.h>
#include <stdlib.h>
struct polynomial
{
    int coff;
    int expo;
    char c;
    struct polynomial* next;
};

typedef struct polynomial poly;

poly* create(poly* head, int n) {
    head->coff = 0;
    head->expo = 0;
    head->c="";
    head->next = NULL;
    for (int i = 0; i < n; i++) {
        int e, c;
        char ch;
        printf("Enter the values of Exponent,coefficient and variable:\n");
        scanf("%d %d %c", &e, &c,&ch);
        poly* newnode = (poly*)malloc(sizeof(poly));
        newnode->expo = e;
        newnode->coff = c;
        newnode->c=ch;
        newnode->next = NULL;

        if (head->expo == 0 && head->coff == 0 && head->next == NULL) {
            head->expo = e;
            head->coff = c;
            head->c=ch;
        } else {
            poly* prev = NULL;
            poly* curr = head;
            while (curr != NULL && curr->expo > e) {
                prev = curr;
                curr = curr->next;
            }
            if (curr != NULL && curr->expo == e&&curr->c==ch) {
                curr->coff += c;
                free(newnode);
            } else {
                if (prev == NULL) {
                    poly* temp = (poly*)malloc(sizeof(poly));
                    temp->expo = head->expo;
                    temp->coff = head->coff;
                    temp->c=head->c;
                    temp->next = head->next;
                    head->expo = e;
                    head->coff = c;
                    head->c=ch;
                    head->next = temp;
                    free(newnode);
                } else {
                    prev->next = newnode;
                    newnode->next = curr;
                }
            }
        }
    }
 return head;   
}
void show(poly* head) {
    while (head != NULL) {
        printf("%d%c^%d", head->coff,head->c,head->expo);
        if (head->next != NULL) {
            printf("+");
        }
        head = head->next;
    }
}
poly* addingpoly(poly* head1, poly* head2) {
    poly* result = NULL;
    poly* tail = NULL;

    while (head1 != NULL && head2 != NULL) {
        poly* temp = (poly*)malloc(sizeof(poly));
        temp->next = NULL;

        if (head1->expo == head2->expo && head1->c==head2->c) {
            temp->expo = head1->expo;
            temp->coff = head1->coff + head2->coff;
            temp->c=head1->c;
            head1 = head1->next;
            head2 = head2->next;
        }

        if (result == NULL) {
            result = temp;
            tail = temp;
        } else {
            tail->next = temp;
            tail = temp;
        }
    }

    while (head1 != NULL) {
        poly* temp = (poly*)malloc(sizeof(poly));
        temp->expo = head1->expo;
        temp->coff = head1->coff;
        temp->c=head1->c;
        temp->next = NULL;
        tail->next = temp;
        tail = temp;
        head1 = head1->next;
    }

    while (head2 != NULL) {
        poly* temp = (poly*)malloc(sizeof(poly));
        temp->expo = head2->expo;
        temp->coff = head2->coff;
        temp->c=head2->c;
        temp->next = NULL;
        tail->next = temp;
        tail = temp;
        head2 = head2->next;
    }

    return result;
}
int main(){
    int n;
    poly* head1 = NULL;
    poly* head2 = NULL;

    for (int i = 0; i < 2; i++) {
        printf("Enter number of terms in polynomial %d: ", i + 1);
        scanf("%d", &n);
        if (i == 0) {
            head1 = create(head1, n);
        } else {
            head2 = create(head2, n);
        }
    }

    poly* result = addingpoly(head1, head2);
    printf("Resultant Polynomial: ");
    show(result);

}