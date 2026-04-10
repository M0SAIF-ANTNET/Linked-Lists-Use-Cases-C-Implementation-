#ifndef MTSO_H
#define MTSO_H

#include <stdbool.h>

typedef enum {
    DATA_CALL,
    VOICE_CALL,
    EMERGENCY_CALL
} CallType;

typedef struct {
    char tag;
    int sender;
    int receiver;
    int packets;
    bool showCallerID;
    bool roaming;
} Call;

typedef struct Node {
    Call data;
    struct Node *next;
} Node;


void initializeQueue(Node **front);

void insertCall(Node **front, const Call *callPtr);

int isEmpty(Node *front);

void serveCall(Node **front);

void dismissLeastPriority(Node **front);

void displayQueue(Node *front);

void destroyQueue(Node **front);

void saveToFile(Node *front, const char *filename);

void loadFromFile(Node **front, const char *filename);

void inputCall(Call *callPtr, CallType type);

void printCall(const Call *callPtr);

#endif