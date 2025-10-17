#include <stdio.h>
#include <stdlib.h>

struct poly {
    int coff;
    int expo;
    struct poly *next;
};
typedef struct poly poly;

poly* create(poly* head) {
    int a = 1;
    while (a == 1) {
        int e, c;
        printf("Enter the values of Exponent and Coefficient: ");
        scanf("%d %d", &e, &c);

        poly* newnode = (poly*)malloc(sizeof(poly));
        newnode->expo = e;
        newnode->coff = c;
        newnode->next = NULL;

        if (head == NULL) {
            head = newnode;
        } else {
            poly* prev = NULL;
            poly* curr = head;

            while (curr != NULL && curr->expo > e) {
                prev = curr;
                curr = curr->next;
            }

            if (curr != NULL && curr->expo == e) {
                curr->coff += c;
                free(newnode);
            } else if (prev == NULL) {
                newnode->next = head;
                head = newnode;
            } else {
                newnode->next = curr;
                prev->next = newnode;
            }
        }

        printf("Do you want to continue? (1/0): ");
        scanf("%d", &a);
    }
    return head;
}

poly* add(poly* head1, poly* head2) {
    poly* result = NULL;
    poly* tail = NULL;

    while (head1 != NULL && head2 != NULL) {
        poly* temp = (poly*)malloc(sizeof(poly));
        temp->next = NULL;

        if (head1->expo == head2->expo) {
            temp->expo = head1->expo;
            temp->coff = head1->coff + head2->coff;
            head1 = head1->next;
            head2 = head2->next;
        } else if (head1->expo > head2->expo) {
            temp->expo = head1->expo;
            temp->coff = head1->coff;
            head1 = head1->next;
        } else {
            temp->expo = head2->expo;
            temp->coff = head2->coff;
            head2 = head2->next;
        }

        if (result == NULL) {
            result = tail = temp;
        } else {
            tail->next = temp;
            tail = temp;
        }
    }

    while (head1 != NULL) {
        poly* temp = (poly*)malloc(sizeof(poly));
        temp->expo = head1->expo;
        temp->coff = head1->coff;
        temp->next = NULL;
        tail->next = temp;
        tail = temp;
        head1 = head1->next;
    }

    while (head2 != NULL) {
        poly* temp = (poly*)malloc(sizeof(poly));
        temp->expo = head2->expo;
        temp->coff = head2->coff;
        temp->next = NULL;
        tail->next = temp;
        tail = temp;
        head2 = head2->next;
    }

    return result;
}

void display(poly* head) {
    if (head == NULL) {
        printf("Polynomial is empty\n");
        return;
    }

    while (head != NULL) {
        printf("%dx^%d", head->coff, head->expo);
        if (head->next != NULL)
            printf(" + ");
        head = head->next;
    }
    printf("\n");
}

int main() {
    poly* head1 = NULL;
    poly* head2 = NULL;

    printf("Enter first polynomial\n");
    head1 = create(head1);

    printf("Enter second polynomial\n");
    head2 = create(head2);

    poly* result = add(head1, head2);

    printf("Resultant Polynomial after Addition: ");
    display(result);

    return 0;
}
