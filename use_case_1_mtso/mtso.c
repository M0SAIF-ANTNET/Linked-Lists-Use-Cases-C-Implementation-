#include <stdio.h>
#include <stdlib.h>
#include "mtso.h"

static Node *createNode(const Call *callPtr) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = *callPtr;
    newNode->next = NULL;
    return newNode;
}

static int getPriority(char tag) {
    if (tag == 'E') return 3;
    if (tag == 'V') return 2;
    return 1; /* D */
}

void initializeQueue(Node **front) {
    *front = NULL;
}

int isEmpty(Node *front) {
    return (front == NULL);
}

void inputCall(Call *callPtr, CallType type) {
    printf("Enter sender ID: ");
    scanf("%d", &callPtr->sender);

    printf("Enter receiver ID: ");
    scanf("%d", &callPtr->receiver);

    if (type == DATA_CALL) {
        callPtr->tag = 'D';
        printf("Enter number of packets: ");
        scanf("%d", &callPtr->packets);
        callPtr->showCallerID = false;
        callPtr->roaming = false;
    } else if (type == VOICE_CALL) {
        int x;
        callPtr->tag = 'V';
        callPtr->packets = 0;

        printf("Show caller ID? (1 = Yes, 0 = No): ");
        scanf("%d", &x);
        callPtr->showCallerID = (x != 0);

        printf("Roaming enabled? (1 = Yes, 0 = No): ");
        scanf("%d", &x);
        callPtr->roaming = (x != 0);
    } else {
        int x;
        callPtr->tag = 'E';
        callPtr->packets = 0;

        printf("Show caller ID? (1 = Yes, 0 = No): ");
        scanf("%d", &x);
        callPtr->showCallerID = (x != 0);

        printf("Roaming enabled? (1 = Yes, 0 = No): ");
        scanf("%d", &x);
        callPtr->roaming = (x != 0);
    }
}

void printCall(const Call *callPtr) {
    printf("Tag: %c | Sender: %d | Receiver: %d",
           callPtr->tag, callPtr->sender, callPtr->receiver);

    if (callPtr->tag == 'D') {
        printf(" | Packets: %d", callPtr->packets);
    } else {
        printf(" | ShowCallerID: %s | Roaming: %s",
               callPtr->showCallerID ? "Yes" : "No",
               callPtr->roaming ? "Yes" : "No");
    }
    printf("\n");
}

void insertCall(Node **front, const Call *callPtr) {
    Node *newNode = createNode(callPtr);
    int newPriority = getPriority(callPtr->tag);

    if (*front == NULL) {
        *front = newNode;
        return;
    }

    if (newPriority > getPriority((*front)->data.tag)) {
        newNode->next = *front;
        *front = newNode;
        return;
    }

    Node *current = *front;
    while (current->next != NULL &&
           getPriority(current->next->data.tag) >= newPriority) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
}

void serveCall(Node **front) {
    if (isEmpty(*front)) {
        printf("No calls in the system.\n");
        return;
    }

    Node *temp = *front;
    printf("\nServing call:\n");
    printCall(&temp->data);

    *front = (*front)->next;
    free(temp);
}

void dismissLeastPriority(Node **front) {
    if (isEmpty(*front)) {
        printf("No calls to dismiss.\n");
        return;
    }

    Node *current = *front;
    int hasData = 0, hasVoice = 0;

    while (current != NULL) {
        if (current->data.tag == 'D') hasData = 1;
        if (current->data.tag == 'V') hasVoice = 1;
        current = current->next;
    }

    char targetTag;
    if (hasData) {
        targetTag = 'D';
        printf("Dismissing all data calls...\n");
    } else if (hasVoice) {
        targetTag = 'V';
        printf("Dismissing all voice calls...\n");
    } else {
        printf("No data or voice calls to dismiss.\n");
        return;
    }

    while (*front != NULL && (*front)->data.tag == targetTag) {
        Node *temp = *front;
        *front = (*front)->next;
        free(temp);
    }

    current = *front;
    while (current != NULL && current->next != NULL) {
        if (current->next->data.tag == targetTag) {
            Node *temp = current->next;
            current->next = temp->next;
            free(temp);
        } else {
            current = current->next;
        }
    }
}

void displayQueue(Node *front) {
    if (isEmpty(front)) {
        printf("Queue is empty.\n");
        return;
    }

    printf("\nCurrent calls in system:\n");
    while (front != NULL) {
        printCall(&front->data);
        front = front->next;
    }
}

void destroyQueue(Node **front) {
    Node *current = *front;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    *front = NULL;
}

void saveToFile(Node *front, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Could not open file for saving.\n");
        return;
    }

    while (front != NULL) {
        fprintf(fp, "%c %d %d %d %d %d\n",
                front->data.tag,
                front->data.sender,
                front->data.receiver,
                front->data.packets,
                front->data.showCallerID,
                front->data.roaming);
        front = front->next;
    }

    fclose(fp);
}

void loadFromFile(Node **front, const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        return;
    }

    Call c;
    while (fscanf(fp, " %c %d %d %d %d %d",
                  &c.tag,
                  &c.sender,
                  &c.receiver,
                  &c.packets,
                  (int *)&c.showCallerID,
                  (int *)&c.roaming) == 6) {
        insertCall(front, &c);
    }

    fclose(fp);
}