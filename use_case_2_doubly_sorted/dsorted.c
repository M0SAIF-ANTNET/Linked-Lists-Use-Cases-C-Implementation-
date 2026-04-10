#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dsorted.h"

void initializeList(DList *list) {
    *list = NULL;
}

int insertNode(DList *list, int key, const char info[]) {
    DNode *newNode = (DNode *)malloc(sizeof(DNode));
    if (newNode == NULL) {
        return 0;
    }

    newNode->key = key;
    strcpy(newNode->info, info);
    newNode->prev = NULL;
    newNode->next = NULL;

    if (*list == NULL) {
        *list = newNode;
        return 1;
    }

    DNode *current = *list;

    if (key < current->key) {
        newNode->next = *list;
        (*list)->prev = newNode;
        *list = newNode;
        return 1;
    }

    while (current->next != NULL && current->next->key < key) {
        current = current->next;
    }

    newNode->next = current->next;
    newNode->prev = current;

    if (current->next != NULL) {
        current->next->prev = newNode;
    }

    current->next = newNode;
    return 1;
}

int deleteNode(DList *list, int key, char outInfo[]) {
    if (*list == NULL) {
        return 0;
    }

    DNode *current = *list;

    while (current != NULL && current->key != key) {
        current = current->next;
    }

    if (current == NULL) {
        return 0;
    }

    strcpy(outInfo, current->info);

    if (current->prev != NULL) {
        current->prev->next = current->next;
    } else {
        *list = current->next;
    }

    if (current->next != NULL) {
        current->next->prev = current->prev;
    }

    free(current);
    return 1;
}

void destroyList(DList *list) {
    DNode *current = *list;
    while (current != NULL) {
        DNode *temp = current;
        current = current->next;
        free(temp);
    }
    *list = NULL;
}

void displayForward(DList list) {
    if (list == NULL) {
        printf("List is empty.\n");
        return;
    }

    printf("Forward: ");
    while (list != NULL) {
        printf("(%d, %s) ", list->key, list->info);
        list = list->next;
    }
    printf("\n");
}

void displayBackward(DList list) {
    if (list == NULL) {
        printf("List is empty.\n");
        return;
    }

    DNode *tail = list;
    while (tail->next != NULL) {
        tail = tail->next;
    }

    printf("Backward: ");
    while (tail != NULL) {
        printf("(%d, %s) ", tail->key, tail->info);
        tail = tail->prev;
    }
    printf("\n");
}