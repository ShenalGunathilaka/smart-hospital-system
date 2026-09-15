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
float getSpecialtyBaseFee(int specialty_id);

int main() {
    int choice;

    do {
        displayMenu();
        printf("Enter Choice: ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("\nInvalid input. Please enter a number.\n");
            continue;
        }

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
                printf("\nInvalid option. Please choose between 1 and 4.\n");
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

float getSpecialtyBaseFee(int specialty_id) {
    for (int i = 0; i < 4; i++) {
        if (SPECIALTIES[i].id == specialty_id) {
            return SPECIALTIES[i].base_fee;
        }
    }
    return 0.0f; // Default fallback
}

void registerPatient() {
    if (patientCount >= MAX_PATIENTS) {
        printf("\nError: System registration limit reached.\n");
        return;
    }

    Patient p;
    p.id = patientCount + 101;

    printf("\n--- Patient Registration (ID: %d) ---\n", p.id);

    printf("Enter Patient Full Name: ");
    getchar();
    fgets(p.name, sizeof(p.name), stdin);
    p.name[strcspn(p.name, "\n")] = 0;

    do {
        printf("Enter Age (0 - 120): ");
        if (scanf("%d", &p.age) != 1 || p.age < 0 || p.age > 120) {
            while (getchar() != '\n');
            printf("Invalid age! Please enter a value between 0 and 120.\n");
        } else {
            break;
        }
    } while (1);

    do {
        printf("\nSelect Urgency Level:\n");
        printf(" 1. Normal\n 2. Urgent\n 3. Critical\nChoice (1-3): ");
        if (scanf("%d", &p.urgency) != 1 || p.urgency < 1 || p.urgency > 3) {
            while (getchar() != '\n');
            printf("Invalid selection! Please enter 1, 2, or 3.\n");
        } else {
            break;
        }
    } while (1);

    do {
        printf("\nSelect Medical Specialty:\n");
        for (int i = 0; i < 4; i++) {
            printf(" %d. %s (LKR %.2f)\n", SPECIALTIES[i].id, SPECIALTIES[i].name, SPECIALTIES[i].base_fee);
        }
        printf("Choice (1-4): ");
        if (scanf("%d", &p.specialty_id) != 1 || p.specialty_id < 1 || p.specialty_id > 4) {
            while (getchar() != '\n');
            printf("Invalid specialty choice! Pick between 1 and 4.\n");
        } else {
            break;
        }
    } while (1);

    // Look up base fee dynamically
    p.base_fee = getSpecialtyBaseFee(p.specialty_id);

    int isAdmitted;
    do {
        printf("\nIs admission required? (1: Yes, 0: No / Outpatient): ");
        if (scanf("%d", &isAdmitted) != 1 || (isAdmitted != 0 && isAdmitted != 1)) {
            while (getchar() != '\n');
            printf("Invalid option! Enter 1 for Yes or 0 for No.\n");
        } else {
            break;
        }
    } while (1);

    if (isAdmitted) {
        do {
            printf("\nSelect Ward:\n");
            for (int i = 0; i < 4; i++) {
                printf(" %d. %s (LKR %.2f / day)\n", WARDS[i].id, WARDS[i].name, WARDS[i].daily_rate);
            }
            printf("Choice (1-4): ");
            if (scanf("%d", &p.ward_id) != 1 || p.ward_id < 1 || p.ward_id > 4) {
                while (getchar() != '\n');
                printf("Invalid ward selection! Pick between 1 and 4.\n");
            } else {
                break;
            }
        } while (1);

        do {
            printf("Enter anticipated days of stay (1 - 365): ");
            if (scanf("%d", &p.days_admitted) != 1 || p.days_admitted < 1 || p.days_admitted > 365) {
                while (getchar() != '\n');
                printf("Invalid duration! Please enter a number between 1 and 365.\n");
            } else {
                break;
            }
        } while (1);
    } else {
        p.ward_id = 0;
        p.days_admitted = 0;
    }

    patients[patientCount++] = p;
    printf("\nPatient %s registered! Base Consultation Fee calculated: LKR %.2f\n", p.name, p.base_fee);
}
