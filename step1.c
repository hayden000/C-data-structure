#include <stdio.h>
#include <stdlib.h>

#define BLOCKSIZE 5

struct list {
    struct node *head;
    struct node *tail;
    struct node *right;
    struct node *left;
    int length;
};

struct node {
    int i;
    struct node *next;
    struct node *prev;
};

void *allocator(int size, int *counter) {
    int *pointer;
    pointer = (int *) malloc(size);
    if (NULL != pointer) {
        *counter = *counter + 1;
    }
    return pointer;
}

void deAllocator(void *p, int *counter) {
    if (NULL != p) {
        free(p);
        *counter = *counter - 1;
    }
}

void initialiseList(struct list *pList, int *counter) {
    (*pList).head = allocator(sizeof(struct node), counter);
    (*pList).tail = allocator(sizeof(struct node), counter);
    pList->head->i = 0;
    pList->tail->i = 0;
    pList->head->next = pList->tail;
    pList->head->prev = NULL;
    pList->tail->prev = pList->head;
    pList->tail->next = NULL;
    pList->left = pList->head;
    pList->right = pList->tail;
}

int main() {
    int counter = 0;
    struct list myList;
    printf("allocating two nodes ... \n");
    printf("initialising the list ... \n");
    initialiseList(&myList, &counter);
    printf(" | %d || %d |\n", myList.head->i, myList.tail->i);
    printf("counter = %d\n", counter);
    printf("freeing the list ...\n");
    deAllocator(myList.head, &counter);
    deAllocator(myList.tail, &counter);
    printf("counter = %d\n", counter);
}

