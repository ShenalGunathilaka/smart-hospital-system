#include <stdio.h>
#include <stdlib.h>

void displayMenu();

int main() {
    int choice;

    do {
        displayMenu();
        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\n[Feature Pending] Register New Patient\n");
                break;
            case 2:
                printf("\n[Feature Pending] Display Triage Priority List\n");
                break;
            case 3:
                printf("\n[Feature Pending] Generate System Analytics\n");
                break;
            case 4:
                printf("\nExiting system...\n");
                break;
            default:
                printf("\nInvalid option. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}

void displayMenu() {
    printf("\n=========================================");
    printf("\n  SMART HOSPITAL MANAGEMENT SYSTEM");
    printf("\n=========================================");
    printf("\n1. Register New Patient");
    printf("\n2. Display Triage Priority List");
    printf("\n3. Generate System Analytics");
    printf("\n4. Exit");
    printf("\n=========================================\n");
}
