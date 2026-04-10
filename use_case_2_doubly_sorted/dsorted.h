#ifndef DSORTED_H
#define DSORTED_H

typedef struct DNode {
    int key;
    char info[100];
    struct DNode *prev;
    struct DNode *next;
} DNode;

typedef DNode* DList;

void initializeList(DList *list);

int insertNode(DList *list, int key, const char info[]);

int deleteNode(DList *list, int key, char outInfo[]);

void destroyList(DList *list);

void displayForward(DList list);

void displayBackward(DList list);

#endif