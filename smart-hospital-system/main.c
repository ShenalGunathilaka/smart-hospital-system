#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATIENTS 100

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

Patient patients[MAX_PATIENTS];
int patientCount = 0;

void displayMenu();
void registerPatient();

int main() {
    int choice;

    do {
        displayMenu();
        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerPatient();
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

void registerPatient() {
    if (patientCount >= MAX_PATIENTS) {
        printf("\nError: System registration limit reached.\n");
        return;
    }

    Patient p;
    p.id = patientCount + 101; // Auto-generate ID starting at 101

    printf("\n--- Patient Registration (ID: %d) ---\n", p.id);

    printf("Enter Patient Full Name: ");
    getchar(); // Clear leftover newline from scanf
    fgets(p.name, sizeof(p.name), stdin);
    p.name[strcspn(p.name, "\n")] = 0; // Remove trailing newline

    printf("Enter Age: ");
    scanf("%d", &p.age);

    printf("\nSelect Urgency Level:\n");
    printf(" 1. Normal\n 2. Urgent\n 3. Critical\nChoice: ");
    scanf("%d", &p.urgency);

    printf("\nSelect Medical Specialty:\n");
    for (int i = 0; i < 4; i++) {
        printf(" %d. %s (LKR %.2f)\n", SPECIALTIES[i].id, SPECIALTIES[i].name, SPECIALTIES[i].base_fee);
    }
    printf("Choice: ");
    scanf("%d", &p.specialty_id);

    printf("\nIs admission required? (1: Yes, 0: No / Outpatient): ");
    int isAdmitted;
    scanf("%d", &isAdmitted);

    if (isAdmitted) {
        printf("\nSelect Ward:\n");
        for (int i = 0; i < 4; i++) {
            printf(" %d. %s (LKR %.2f / day)\n", WARDS[i].id, WARDS[i].name, WARDS[i].daily_rate);
        }
        printf("Choice: ");
        scanf("%d", &p.ward_id);

        printf("Enter anticipated days of stay: ");
        scanf("%d", &p.days_admitted);
    } else {
        p.ward_id = 0;
        p.days_admitted = 0;
    }

    patients[patientCount++] = p;
    printf("\nPatient %s registered successfully!\n", p.name);
}
