#include <stdio.h>
#include "mtso.h"

int main() {
    Node *front;
    int choice;
    Call c;

    initializeQueue(&front);
    loadFromFile(&front, "calls.txt");

    do {
        printf("\n===== MTSO Simulation Menu =====\n");
        printf("1. Data Call coming\n");
        printf("2. Voice Call coming\n");
        printf("3. Emergency Call coming\n");
        printf("4. Serve a call\n");
        printf("5. Dismiss calls with least priority\n");
        printf("6. Display all calls\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                inputCall(&c, DATA_CALL);
                insertCall(&front, &c);
                printf("Data call inserted.\n");
                break;

            case 2:
                inputCall(&c, VOICE_CALL);
                insertCall(&front, &c);
                printf("Voice call inserted.\n");
                break;

            case 3:
                inputCall(&c, EMERGENCY_CALL);
                insertCall(&front, &c);
                printf("Emergency call inserted.\n");
                break;

            case 4:
                serveCall(&front);
                break;

            case 5:
                dismissLeastPriority(&front);
                break;

            case 6:
                displayQueue(front);
                break;

            case 7:
                saveToFile(front, "calls.txt");
                destroyQueue(&front);
                printf("Data saved. Exiting program.\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 7);

    return 0;
}