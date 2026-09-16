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
    int bed_number; // 0 if outpatient
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

// Bed Occupancy Matrix: 4 Wards x Max 20 Beds (0: Empty, 1: Occupied)
int bedOccupancy[4][20] = {0};

void displayMenu();
void registerPatient();
float getSpecialtyBaseFee(int specialty_id);
float calculateSurcharge(float base_fee, int urgency);
float calculateWardCost(int ward_id, int days_admitted);
float calculateDiscount(int age, float subtotal);
int calculateWaitTime(int specialty_id, int urgency);
int allocateBed(int ward_id);

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
    return 0.0f;
}

float calculateSurcharge(float base_fee, int urgency) {
    if (urgency == 2) {
        return base_fee * 0.15f;
    } else if (urgency == 3) {
        return base_fee * 0.35f;
    }
    return 0.0f;
}

float calculateWardCost(int ward_id, int days_admitted) {
    if (ward_id == 0 || days_admitted <= 0) return 0.0f;

    for (int i = 0; i < 4; i++) {
        if (WARDS[i].id == ward_id) {
            return WARDS[i].daily_rate * days_admitted;
        }
    }
    return 0.0f;
}

float calculateDiscount(int age, float subtotal) {
    if (age < 12) {
        return subtotal * 0.15f;
    } else if (age >= 65) {
        return subtotal * 0.20f;
    }
    return 0.0f;
}

int calculateWaitTime(int specialty_id, int urgency) {
    if (urgency == 3) return 0;

    int avg_time = 15;
    for (int i = 0; i < 4; i++) {
        if (SPECIALTIES[i].id == specialty_id) {
            avg_time = SPECIALTIES[i].avg_time;
            break;
        }
    }

    if (urgency == 2) {
        return (int)(avg_time * 0.5);
    }
    return (int)(avg_time * 1.5);
}

int allocateBed(int ward_id) {
    int wardIdx = ward_id - 1;
    int maxCapacity = WARDS[wardIdx].capacity;

    for (int bed = 0; bed < maxCapacity; bed++) {
        if (bedOccupancy[wardIdx][bed] == 0) {
            bedOccupancy[wardIdx][bed] = 1; // Mark as occupied
            return bed + 1; // Return 1-based bed number
        }
    }
    return -1; // Ward full
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
        printf(" 1. Normal (0%% surcharge)\n 2. Urgent (15%% surcharge)\n 3. Critical (35%% surcharge)\nChoice (1-3): ");
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
                p.bed_number = allocateBed(p.ward_id);
                if (p.bed_number == -1) {
                    printf("Warning: Selected ward is at maximum capacity! Re-select or enter 0 for outpatient.\n");
                } else {
                    break;
                }
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
        p.bed_number = 0;
        p.days_admitted = 0;
    }

    p.base_fee = getSpecialtyBaseFee(p.specialty_id);
    p.surcharge = calculateSurcharge(p.base_fee, p.urgency);
    p.ward_cost = calculateWardCost(p.ward_id, p.days_admitted);
    p.gross_total = p.base_fee + p.surcharge + p.ward_cost;
    p.discount = calculateDiscount(p.age, p.base_fee + p.surcharge);
    p.final_amount = p.gross_total - p.discount;
    p.wait_time = calculateWaitTime(p.specialty_id, p.urgency);

    patients[patientCount++] = p;

    printf("\n=========================================");
    printf("\n         PATIENT REGISTRATION BILL       ");
    printf("\n=========================================");
    printf("\n  Patient Name:      %s", p.name);
    printf("\n  Estimated Wait:    %d minutes", p.wait_time);
    if (p.ward_id > 0) {
        printf("\n  Assigned Bed:      Ward %d, Bed #%d", p.ward_id, p.bed_number);
    }
    printf("\n  ---------------------------------------");
    printf("\n  Base Consultation: LKR %.2f", p.base_fee);
    printf("\n  Urgency Surcharge: LKR %.2f", p.surcharge);
    printf("\n  Ward Accommodation:LKR %.2f", p.ward_cost);
    printf("\n  Gross Total:       LKR %.2f", p.gross_total);
    printf("\n  Age Discount:     -LKR %.2f", p.discount);
    printf("\n  ---------------------------------------");
    printf("\n  FINAL AMOUNT DUE:  LKR %.2f", p.final_amount);
    printf("\n=========================================\n");
}
