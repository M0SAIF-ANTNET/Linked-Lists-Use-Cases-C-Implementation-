#include <stdio.h>
#include "dsorted.h"

int main() {
    DList list;
    int choice, key;
    char info[100];
    char deletedInfo[100];

    initializeList(&list);

    do {
        printf("\n===== Doubly Sorted Linked List Menu =====\n");
        printf("1. Insert element\n");
        printf("2. Delete element by key\n");
        printf("3. Display forward\n");
        printf("4. Display backward\n");
        printf("5. Destroy list\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key: ");
                scanf("%d", &key);
                printf("Enter info: ");
                scanf(" %99[^\n]", info);

                if (insertNode(&list, key, info))
                    printf("Inserted successfully.\n");
                else
                    printf("Insertion failed.\n");
                break;

            case 2:
                printf("Enter key to delete: ");
                scanf("%d", &key);

                if (deleteNode(&list, key, deletedInfo))
                    printf("Deleted node info: %s\n", deletedInfo);
                else
                    printf("Key not found.\n");
                break;

            case 3:
                displayForward(list);
                break;

            case 4:
                displayBackward(list);
                break;

            case 5:
                destroyList(&list);
                printf("List destroyed.\n");
                break;

            case 6:
                destroyList(&list);
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 6);

    return 0;
}