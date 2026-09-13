#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATIENTS 100

// Data structures for hospital entities
typedef struct {
    int id;
    char name[30];
    float base_fee;
    int avg_time;
    int daily_cap;
} Specialty;

typedef struct {
    int id;
    char name[30];
    float daily_rate;
    int capacity;
} Ward;

typedef struct {
    int id;
    char name[50];
    int age;
    int urgency; // 1: Normal, 2: Urgent, 3: Critical
    int specialty_id;
    int ward_id; // 0 if outpatient
    int days_admitted;

    // Financial and billing details
    float base_fee;
    float surcharge;
    float ward_cost;
    float gross_total;
    float discount;
    float final_amount;
    int wait_time;
} Patient;

// Constant lookup tables
const Specialty SPECIALTIES[4] = {
    {1, "General Practice (OPD)", 1500.00, 15, 30},
    {2, "Paediatrics", 2500.00, 20, 20},
    {3, "Cardiology", 4500.00, 30, 12},
    {4, "Neurology", 5000.00, 30, 10}
};

const Ward WARDS[4] = {
    {1, "General Ward", 3000.00, 20},
    {2, "Paediatric Ward", 6000.00, 10},
    {3, "Surgical Ward", 12000.00, 10},
    {4, "ICU (Intensive Care Unit)", 25000.00, 5}
};

// Global state tracking
int bedOccupancy[4][20] = {0}; // 2D array: 4 wards, max 20 beds
int specialtyQueue[4] = {0};   // Track active queue count per specialty

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
