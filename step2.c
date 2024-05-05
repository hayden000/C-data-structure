#include <stdlib.h>
#include <stdio.h>

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

void allocateBlock(struct list *pList, int *counter) {
    for (int i = 0; i < BLOCKSIZE; i++) {
        struct node *object = (struct node *) allocator(sizeof(struct node), counter);
        object->prev = pList->left;
        object->next = pList->left->next;
        pList->left->next->prev = object;
        pList->left->next = object;
        object->i = -1;
        pList->length = pList->length + 1;
    }
}

void deAllocateBlock(struct list *pList, int *counter) {
    int i = 0;
    while (i < BLOCKSIZE) {
        struct node *temp = pList->left->next;
        pList->left->next->next->prev = pList->left;
        pList->left->next = pList->left->next->next;
        deAllocator(temp, counter);
        pList->length = pList->length - 1;
        i++;
    }
}

void printList(struct list *pList, int *counter) {
    if (pList->head) {
        struct node *cur = pList->head;
        while (cur) {
            printf(" | %d | ", cur->i);
            cur = cur->next;
        }
        printf("\n");
    }
    printf("counter = %d\n", *counter);
}

void removeList(struct list *pList, int *counter) {
    deAllocator(pList->head, counter);
    deAllocator(pList->tail, counter);
    pList->head = NULL;
    pList->tail = NULL;
    pList->length = 0;
    pList->left = NULL;
    pList->right = NULL;
}

int main() {
    int counter = 0;
    struct list myList;
    printf("initialising the list ... \n");
    initialiseList(&myList, &counter);
    printList(&myList, &counter);
    printf("allocating %d free nodes ... \n", BLOCKSIZE);
    allocateBlock(&myList, &counter);
    printList(&myList, &counter);
    printf("freeing %d free nodes ... \n", BLOCKSIZE);
    deAllocateBlock(&myList, &counter);
    printList(&myList, &counter);
    printf("freeing head and tail ... \n");
    removeList(&myList, &counter);
    printList(&myList, &counter);
}

