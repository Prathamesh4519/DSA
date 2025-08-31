#include <stdio.h>
#include <stdlib.h>

struct list{
    int data;
    struct list* next;
};
typedef struct list list;

struct queue{
    list* front;
    list* rear;
    int size;
};
typedef  struct queue queue;

int hashing(int num){
    return num%10;
}

void enqueue(queue* ptr,int data){
    list* new=(list*)malloc(sizeof(list));
    new->next=NULL;
    new->data=data;
    if(ptr->front==NULL){
        ptr->front=new;
        ptr->rear=new;
        ptr->size++;
        return;
    }
    ptr->rear->next=new;
    ptr->rear=new;
    ptr->size++;
    return;
}


int dequeue(queue* ptr){
    if(ptr->front==NULL){
        printf("Empty que\n");
        return -1;
    }
    ptr->size--;
    int data=ptr->front->data;
    if(ptr->front->next==NULL){
        free(ptr->front);
        ptr->front=NULL;
        ptr->rear=NULL;
        
        return data;
    }
    
    list* t=ptr->front;
    ptr->front=ptr->front->next;
    free(t);
    return data;
}


void hash_in(queue* ptr[],int data){
    int index=hashing(data);
    enqueue(ptr[index],data);
}

void search(queue* ptr[],int data){
    int index=hashing(data);
    
    list* temp=ptr[index]->front;
    while(temp){
        int ret=temp->data;
        if(ret==data){
            printf("Found:\n");
            return;
        }
        temp=temp->next;
    }
    printf("Not Found\n");
 
}



int main(){
    queue* ptr[10];
    for(int i=0;i<10;i++){
        ptr[i]=(queue*)malloc(sizeof(queue));
        ptr[i]->front=NULL;
        ptr[i]->rear=NULL;
        ptr[i]->size=0;
    }
    hash_in(ptr,10);
    hash_in(ptr,11);
    hash_in(ptr,1111);
    hash_in(ptr,7);
    hash_in(ptr,1111111);

    search(ptr,11);
    search(ptr,77);
    search(ptr,43);
    search(ptr,1111111);
}