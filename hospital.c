#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define PATIENT_FILE "patients.dat"
#define DOCTOR_FILE "doctors.dat"
#define APPOINTMENT_FILE "appointments.dat"
#define DIAGNOSIS_FILE "diagnoses.dat"
#define BILL_FILE "bills.dat"
#define PRESCRIPTION_FILE "prescriptions.dat"
#define MEDICAL_HISTORY_FILE "medical_history.dat"
#define INVENTORY_FILE "inventory.dat"
#define STAFF_SCHEDULE_FILE "staff_schedule.dat"

typedef struct {
    int id;
    char name[50];
    int age;
    char gender[10];
    char phone[15];
    char address[100];
    char bloodType[5];
    char emergencyContact[15];
    char insuranceId[20];
} Patient;

typedef struct {
    int id;
    char name[50];
    char specialization[50];
    char phone[15];
    float consultationFee;
    int experienceYears;
    char qualification[100];
} Doctor;

typedef struct {
    int id;
    int patientId;
    int doctorId;
    char date[12];  
    char time[6];   
    char status[20]; 
    char type[30];   
} Appointment;

typedef struct {
    int appointmentId;
    char diagnosis[200];
    char medication[200];
    char notes[300];
    char severity[20]; 
} Diagnosis;

typedef struct {
    int appointmentId;
    float consultationFee;
    float medicationCost;
    float labCharges;
    float totalAmount;
    char paymentStatus[20]; 
} Bill;

typedef struct {
    int id;
    int patientId;
    int doctorId;
    char date[12];
    char condition[100];
    char treatment[200];
    char outcome[100];
} MedicalHistory;

typedef struct {
    int id;
    int appointmentId;
    char medicationName[50];
    char dosage[30];
    int duration; 
    char frequency[20]; 
    char instructions[100];
} Prescription;

typedef struct {
    int id;
    char itemName[50];
    int quantity;
    float unitPrice;
    char category[30]; 
    char expiryDate[12];
    int minThreshold;
} InventoryItem;

typedef struct {
    int id;
    int doctorId;
    char date[12];
    char startTime[6];
    char endTime[6];
    char shift[20]; 
    int isAvailable;
} StaffSchedule;


void addPatient();
void listPatients();
void searchPatients();
void viewPatientHistory();
void addDoctor();
void listDoctors();
void scheduleAppointment();
void listAppointments();
void recordDiagnosis();
void listDiagnoses();
void createPrescription();
void viewPrescriptions();
void addMedicalHistory();
void addInventoryItem();
void viewInventory();
void generateBill();
void listBills();
void generateFinancialReport();
void menu();
Patient* findPatientById(int id);
Doctor* findDoctorById(int id);


int generateId(const char* filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) return 1;
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    int count = size / sizeof(Patient);
    fclose(fp);
    return count + 1;
}

void getCurrentDate(char* dateStr) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(dateStr, "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
}



void addPatient() {
    FILE *fp = fopen(PATIENT_FILE, "ab");
    if (!fp) {
        printf("Error opening patient file.\n");
        return;
    }
    Patient p;
    p.id = generateId(PATIENT_FILE);
    printf("Enter patient name: ");
    fgets(p.name, sizeof(p.name), stdin);
    p.name[strcspn(p.name, "\n")] = 0;
    printf("Enter age: ");
    scanf("%d", &p.age);
    getchar();
    printf("Enter gender: ");
    fgets(p.gender, sizeof(p.gender), stdin);
    p.gender[strcspn(p.gender, "\n")] = 0;
    printf("Enter phone: ");
    fgets(p.phone, sizeof(p.phone), stdin);
    p.phone[strcspn(p.phone, "\n")] = 0;
    printf("Enter address: ");
    fgets(p.address, sizeof(p.address), stdin);
    p.address[strcspn(p.address, "\n")] = 0;
    printf("Enter blood type (A+, B-, etc.): ");
    fgets(p.bloodType, sizeof(p.bloodType), stdin);
    p.bloodType[strcspn(p.bloodType, "\n")] = 0;
    printf("Enter emergency contact: ");
    fgets(p.emergencyContact, sizeof(p.emergencyContact), stdin);
    p.emergencyContact[strcspn(p.emergencyContact, "\n")] = 0;
    printf("Enter insurance ID: ");
    fgets(p.insuranceId, sizeof(p.insuranceId), stdin);
    p.insuranceId[strcspn(p.insuranceId, "\n")] = 0;

    fwrite(&p, sizeof(Patient), 1, fp);
    fclose(fp);

    printf("Patient registered successfully with ID: %d\n", p.id);
}

void listPatients() {
    FILE *fp = fopen(PATIENT_FILE, "rb");
    if (!fp) {
        printf("No patients registered yet.\n");
        return;
    }
    Patient p;
    printf("\n--- Patient List ---\n");
    printf("ID\tName\t\tAge\tGender\tBlood Type\tPhone\n");
    while (fread(&p, sizeof(Patient), 1, fp)) {
        printf("%d\t%-15s\t%d\t%s\t%s\t\t%s\n", p.id, p.name, p.age, p.gender, p.bloodType, p.phone);
    }
    fclose(fp);
}

Patient* findPatientById(int id) {
    static Patient p;
    FILE *fp = fopen(PATIENT_FILE, "rb");
    if (!fp) return NULL;
    while (fread(&p, sizeof(Patient), 1, fp)) {
        if (p.id == id) {
            fclose(fp);
            return &p;
        }
    }
    fclose(fp);
    return NULL;
}



void addDoctor() {
    FILE *fp = fopen(DOCTOR_FILE, "ab");
    if (!fp) {
        printf("Error opening doctor file.\n");
        return;
    }
    Doctor d;
    d.id = generateId(DOCTOR_FILE);
    printf("Enter doctor name: ");
    fgets(d.name, sizeof(d.name), stdin);
    d.name[strcspn(d.name, "\n")] = 0;
    printf("Enter specialization: ");
    fgets(d.specialization, sizeof(d.specialization), stdin);
    d.specialization[strcspn(d.specialization, "\n")] = 0;
    printf("Enter phone: ");
    fgets(d.phone, sizeof(d.phone), stdin);
    d.phone[strcspn(d.phone, "\n")] = 0;
    printf("Enter consultation fee: ");
    scanf("%f", &d.consultationFee);
    printf("Enter years of experience: ");
    scanf("%d", &d.experienceYears);
    getchar();
    printf("Enter qualification: ");
    fgets(d.qualification, sizeof(d.qualification), stdin);
    d.qualification[strcspn(d.qualification, "\n")] = 0;

    fwrite(&d, sizeof(Doctor), 1, fp);
    fclose(fp);

    printf("Doctor added successfully with ID: %d\n", d.id);
}

void listDoctors() {
    FILE *fp = fopen(DOCTOR_FILE, "rb");
    if (!fp) {
        printf("No doctors added yet.\n");
        return;
    }
    Doctor d;
    printf("\n--- Doctor List ---\n");
    printf("ID\tName\t\tSpecialization\t\tFee\tExp(Years)\n");
    while (fread(&d, sizeof(Doctor), 1, fp)) {
        printf("%d\t%-15s\t%-20s\t%.2f\t%d\n", d.id, d.name, d.specialization, d.consultationFee, d.experienceYears);
    }
    fclose(fp);
}

Doctor* findDoctorById(int id) {
    static Doctor d;
    FILE *fp = fopen(DOCTOR_FILE, "rb");
    if (!fp) return NULL;
    while (fread(&d, sizeof(Doctor), 1, fp)) {
        if (d.id == id) {
            fclose(fp);
            return &d;
        }
    }
    fclose(fp);
    return NULL;
}



void scheduleAppointment() {
    FILE *fp = fopen(APPOINTMENT_FILE, "ab");
    if (!fp) {
        printf("Error opening appointment file.\n");
        return;
    }
    Appointment a;
    a.id = generateId(APPOINTMENT_FILE);

    int patientId, doctorId;
    char date[12], time[6];

    printf("Enter patient ID: ");
    scanf("%d", &patientId);
    getchar();
    if (!findPatientById(patientId)) {
        printf("No patient found with this ID.\n");
        fclose(fp);
        return;
    }

    printf("Enter doctor ID: ");
    scanf("%d", &doctorId);
    getchar();
    if (!findDoctorById(doctorId)) {
        printf("No doctor found with this ID.\n");
        fclose(fp);
        return;
    }

    printf("Enter date (YYYY-MM-DD): ");
    fgets(date, sizeof(date), stdin);
    date[strcspn(date, "\n")] = 0;

    printf("Enter time (HH:MM): ");
    fgets(time, sizeof(time), stdin);
    time[strcspn(time, "\n")] = 0;

    printf("Enter appointment type (consultation/follow-up/emergency): ");
    fgets(a.type, sizeof(a.type), stdin);
    a.type[strcspn(a.type, "\n")] = 0;

    a.patientId = patientId;
    a.doctorId = doctorId;
    strcpy(a.date, date);
    strcpy(a.time, time);
    strcpy(a.status, "scheduled");

    fwrite(&a, sizeof(Appointment), 1, fp);
    fclose(fp);

    printf("Appointment scheduled with ID: %d\n", a.id);
}

void listAppointments() {
    FILE *fp = fopen(APPOINTMENT_FILE, "rb");
    if (!fp) {
        printf("No appointments scheduled yet.\n");
        return;
    }
    Appointment a;
    printf("\n--- Appointment List ---\n");
    printf("ID\tPatient\t\tDoctor\t\tDate\t\tTime\tType\t\tStatus\n");
    while (fread(&a, sizeof(Appointment), 1, fp)) {
        Patient* p = findPatientById(a.patientId);
        Doctor* d = findDoctorById(a.doctorId);
        printf("%d\t%-15s\t%-15s\t%s\t%s\t%-12s\t%s\n", a.id,
            p ? p->name : "Unknown",
            d ? d->name : "Unknown",
            a.date, a.time, a.type, a.status);
    }
    fclose(fp);
}



void addMedicalHistory() {
    FILE *fp = fopen(MEDICAL_HISTORY_FILE, "ab");
    if (!fp) {
        printf("Error opening medical history file.\n");
        return;
    }
    
    MedicalHistory mh;
    mh.id = generateId(MEDICAL_HISTORY_FILE);
    
    printf("Enter patient ID: ");
    scanf("%d", &mh.patientId);
    getchar();
    
    if (!findPatientById(mh.patientId)) {
        printf("Patient not found.\n");
        fclose(fp);
        return;
    }
    
    printf("Enter doctor ID: ");
    scanf("%d", &mh.doctorId);
    getchar();
    
    getCurrentDate(mh.date);
    
    printf("Enter medical condition: ");
    fgets(mh.condition, sizeof(mh.condition), stdin);
    mh.condition[strcspn(mh.condition, "\n")] = 0;
    
    printf("Enter treatment given: ");
    fgets(mh.treatment, sizeof(mh.treatment), stdin);
    mh.treatment[strcspn(mh.treatment, "\n")] = 0;
    
    printf("Enter outcome: ");
    fgets(mh.outcome, sizeof(mh.outcome), stdin);
    mh.outcome[strcspn(mh.outcome, "\n")] = 0;
    
    fwrite(&mh, sizeof(MedicalHistory), 1, fp);
    fclose(fp);
    
    printf("Medical history added successfully.\n");
}

void viewPatientHistory() {
    int patientId;
    printf("Enter patient ID: ");
    scanf("%d", &patientId);
    
    FILE *fp = fopen(MEDICAL_HISTORY_FILE, "rb");
    if (!fp) {
        printf("No medical history found.\n");
        return;
    }
    
    MedicalHistory mh;
    printf("\n--- Medical History for Patient ID: %d ---\n", patientId);
    int found = 0;
    
    while (fread(&mh, sizeof(MedicalHistory), 1, fp)) {
        if (mh.patientId == patientId) {
            found = 1;
            Doctor* d = findDoctorById(mh.doctorId);
            printf("Date: %s\n", mh.date);
            printf("Doctor: %s\n", d ? d->name : "Unknown");
            printf("Condition: %s\n", mh.condition);
            printf("Treatment: %s\n", mh.treatment);
            printf("Outcome: %s\n\n", mh.outcome);
        }
    }
    
    if (!found) {
        printf("No medical history found for this patient.\n");
    }
    
    fclose(fp);
}


void createPrescription() {
    FILE *fp = fopen(PRESCRIPTION_FILE, "ab");
    if (!fp) {
        printf("Error opening prescription file.\n");
        return;
    }
    
    Prescription presc;
    presc.id = generateId(PRESCRIPTION_FILE);
    
    printf("Enter appointment ID: ");
    scanf("%d", &presc.appointmentId);
    getchar();
    
    printf("Enter medication name: ");
    fgets(presc.medicationName, sizeof(presc.medicationName), stdin);
    presc.medicationName[strcspn(presc.medicationName, "\n")] = 0;
    
    printf("Enter dosage: ");
    fgets(presc.dosage, sizeof(presc.dosage), stdin);
    presc.dosage[strcspn(presc.dosage, "\n")] = 0;
    
    printf("Enter duration (days): ");
    scanf("%d", &presc.duration);
    getchar();
    
    printf("Enter frequency: ");
    fgets(presc.frequency, sizeof(presc.frequency), stdin);
    presc.frequency[strcspn(presc.frequency, "\n")] = 0;
    
    printf("Enter special instructions: ");
    fgets(presc.instructions, sizeof(presc.instructions), stdin);
    presc.instructions[strcspn(presc.instructions, "\n")] = 0;
    
    fwrite(&presc, sizeof(Prescription), 1, fp);
    fclose(fp);
    
    printf("Prescription created successfully.\n");
}

void viewPrescriptions() {
    FILE *fp = fopen(PRESCRIPTION_FILE, "rb");
    if (!fp) {
        printf("No prescriptions found.\n");
        return;
    }
    
    Prescription presc;
    printf("\n--- Prescriptions ---\n");
    
    while (fread(&presc, sizeof(Prescription), 1, fp)) {
        printf("Prescription ID: %d\n", presc.id);
        printf("Appointment ID: %d\n", presc.appointmentId);
        printf("Medication: %s\n", presc.medicationName);
        printf("Dosage: %s\n", presc.dosage);
        printf("Duration: %d days\n", presc.duration);
        printf("Frequency: %s\n", presc.frequency);
        printf("Instructions: %s\n\n", presc.instructions);
    }
    
    fclose(fp);
}



void addInventoryItem() {
    FILE *fp = fopen(INVENTORY_FILE, "ab");
    if (!fp) {
        printf("Error opening inventory file.\n");
        return;
    }
    
    InventoryItem item;
    item.id = generateId(INVENTORY_FILE);
    
    printf("Enter item name: ");
    fgets(item.itemName, sizeof(item.itemName), stdin);
    item.itemName[strcspn(item.itemName, "\n")] = 0;
    
    printf("Enter quantity: ");
    scanf("%d", &item.quantity);
    
    printf("Enter unit price: ");
    scanf("%f", &item.unitPrice);
    getchar();
    
    printf("Enter category (medicine/equipment/supplies): ");
    fgets(item.category, sizeof(item.category), stdin);
    item.category[strcspn(item.category, "\n")] = 0;
    
    printf("Enter expiry date (YYYY-MM-DD): ");
    fgets(item.expiryDate, sizeof(item.expiryDate), stdin);
    item.expiryDate[strcspn(item.expiryDate, "\n")] = 0;
    
    printf("Enter minimum threshold: ");
    scanf("%d", &item.minThreshold);
    
    fwrite(&item, sizeof(InventoryItem), 1, fp);
    fclose(fp);
    
    printf("Inventory item added successfully.\n");
}

void viewInventory() {
    FILE *fp = fopen(INVENTORY_FILE, "rb");
    if (!fp) {
        printf("No inventory items found.\n");
        return;
    }
    
    InventoryItem item;
    printf("\n--- Inventory ---\n");
    printf("ID\tItem Name\t\tQty\tPrice\tCategory\tExpiry\t\tThreshold\n");
    
    while (fread(&item, sizeof(InventoryItem), 1, fp)) {
        printf("%d\t%-20s\t%d\t%.2f\t%s\t\t%s\t%d", 
            item.id, item.itemName, item.quantity, item.unitPrice, 
            item.category, item.expiryDate, item.minThreshold);
        
        if (item.quantity <= item.minThreshold) {
            printf(" *LOW STOCK*");
        }
        printf("\n");
    }
    
    fclose(fp);
}



void generateFinancialReport() {
    FILE *fp = fopen(BILL_FILE, "rb");
    if (!fp) {
        printf("No billing data found.\n");
        return;
    }
    
    Bill bill;
    float totalRevenue = 0;
    float consultationTotal = 0;
    float medicationTotal = 0;
    float labTotal = 0;
    int totalBills = 0;
    int paidBills = 0;
    
    printf("\n--- Financial Report ---\n");
    
    while (fread(&bill, sizeof(Bill), 1, fp)) {
        totalBills++;
        if (strcmp(bill.paymentStatus, "paid") == 0) {
            paidBills++;
            totalRevenue += bill.totalAmount;
            consultationTotal += bill.consultationFee;
            medicationTotal += bill.medicationCost;
            labTotal += bill.labCharges;
        }
    }
    
    printf("Total Bills Generated: %d\n", totalBills);
    printf("Paid Bills: %d\n", paidBills);
    printf("Payment Rate: %.2f%%\n", totalBills > 0 ? (float)paidBills/totalBills * 100 : 0);
    printf("Total Revenue: $%.2f\n", totalRevenue);
    printf("Consultation Revenue: $%.2f\n", consultationTotal);
    printf("Medication Revenue: $%.2f\n", medicationTotal);
    printf("Lab Revenue: $%.2f\n", labTotal);
    
    fclose(fp);
}

void searchPatients() {
    char searchName[50];
    printf("Enter patient name to search: ");
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = 0;
    
    FILE *fp = fopen(PATIENT_FILE, "rb");
    if (!fp) {
        printf("No patients found.\n");
        return;
    }
    
    Patient p;
    int found = 0;
    printf("\n--- Search Results ---\n");
    
    while (fread(&p, sizeof(Patient), 1, fp)) {
        if (strstr(p.name, searchName) != NULL) {
            found = 1;
            printf("ID: %d\n", p.id);
            printf("Name: %s\n", p.name);
            printf("Age: %d\n", p.age);
            printf("Gender: %s\n", p.gender);
            printf("Phone: %s\n", p.phone);
            printf("Blood Type: %s\n", p.bloodType);
            printf("Emergency Contact: %s\n", p.emergencyContact);
            printf("Insurance ID: %s\n\n", p.insuranceId);
        }
    }
    
    if (!found) {
        printf("No patients found matching '%s'\n", searchName);
    }
    
    fclose(fp);
}



void menu() {
    int choice;
    while(1) {
        printf("\n========== Advanced Hospital Management System ==========\n");
        printf("PATIENT MANAGEMENT:\n");
        printf("1. Register Patient\n");
        printf("2. List Patients\n");
        printf("3. Search Patients\n");
        printf("4. View Patient Medical History\n");
        printf("\nDOCTOR MANAGEMENT:\n");
        printf("5. Add Doctor\n");
        printf("6. List Doctors\n");
        printf("\nAPPOINTMENT MANAGEMENT:\n");
        printf("7. Schedule Appointment\n");
        printf("8. List Appointments\n");
        printf("\nMEDICAL SERVICES:\n");
        printf("9. Record Diagnosis\n");
        printf("10. List Diagnoses\n");
        printf("11. Create Prescription\n");
        printf("12. View Prescriptions\n");
        printf("13. Add Medical History\n");
        printf("\nINVENTORY & BILLING:\n");
        printf("14. Add Inventory Item\n");
        printf("15. View Inventory\n");
        printf("16. Generate Bill\n");
        printf("17. List Bills\n");
        printf("18. Financial Report\n");
        printf("\n0. Exit\n");
        printf("=========================================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch(choice) {
            case 1: addPatient(); break;
            case 2: listPatients(); break;
            case 3: searchPatients(); break;
            case 4: viewPatientHistory(); break;
            case 5: addDoctor(); break;
            case 6: listDoctors(); break;
            case 7: scheduleAppointment(); break;
            case 8: listAppointments(); break;
            case 9: recordDiagnosis(); break;
            case 10: listDiagnoses(); break;
            case 11: createPrescription(); break;
            case 12: viewPrescriptions(); break;
            case 13: addMedicalHistory(); break;
            case 14: addInventoryItem(); break;
            case 15: viewInventory(); break;
            case 16: generateBill(); break;
            case 17: listBills(); break;
            case 18: generateFinancialReport(); break;
            case 0: printf("Exiting... Goodbye!\n"); exit(0);
            default: printf("Invalid choice, try again.\n"); break;
        }
    }
}



void recordDiagnosis() {
    FILE *fp = fopen(DIAGNOSIS_FILE, "ab");
    if (!fp) {
        printf("Error opening diagnosis file.\n");
        return;
    }
    Diagnosis diag;
    int appointmentId;
    printf("Enter appointment ID: ");
    scanf("%d", &appointmentId);
    getchar();

    FILE *afp = fopen(APPOINTMENT_FILE, "rb");
    if (!afp) {
        printf("Could not open appointment file.\n");
        fclose(fp);
        return;
    }
    Appointment a;
    int found = 0;
    while (fread(&a, sizeof(Appointment), 1, afp)) {
        if (a.id == appointmentId) {
            found = 1;
            break;
        }
    }
    fclose(afp);

    if (!found) {
        printf("Appointment ID not found.\n");
        fclose(fp);
        return;
    }

    diag.appointmentId = appointmentId;
    printf("Enter diagnosis details: ");
    fgets(diag.diagnosis, sizeof(diag.diagnosis), stdin);
    diag.diagnosis[strcspn(diag.diagnosis, "\n")] = 0;

    printf("Enter prescribed medication: ");
    fgets(diag.medication, sizeof(diag.medication), stdin);
    diag.medication[strcspn(diag.medication, "\n")] = 0;

    printf("Enter additional notes: ");
    fgets(diag.notes, sizeof(diag.notes), stdin);
    diag.notes[strcspn(diag.notes, "\n")] = 0;

    printf("Enter severity (mild/moderate/severe): ");
    fgets(diag.severity, sizeof(diag.severity), stdin);
    diag.severity[strcspn(diag.severity, "\n")] = 0;

    fwrite(&diag, sizeof(Diagnosis), 1, fp);
    fclose(fp);

    printf("Diagnosis recorded successfully.\n");
}

void listDiagnoses() {
    FILE *fp = fopen(DIAGNOSIS_FILE, "rb");
    if (!fp) {
        printf("No diagnoses recorded yet.\n");
        return;
    }
    Diagnosis diag;
    printf("\n--- Diagnoses ---\n");
    while (fread(&diag, sizeof(Diagnosis), 1, fp)) {
        printf("Appointment ID: %d\n", diag.appointmentId);
        printf("Diagnosis: %s\n", diag.diagnosis);
        printf("Medication: %s\n", diag.medication);
        printf("Notes: %s\n", diag.notes);
        printf("Severity: %s\n\n", diag.severity);
    }
    fclose(fp);
}

void generateBill() {
    FILE *fp = fopen(BILL_FILE, "ab");
    if (!fp) {
        printf("Error opening bill file.\n");
        return;
    }
    Bill bill;
    int appointmentId;

    printf("Enter appointment ID: ");
    scanf("%d", &appointmentId);
    getchar();

    FILE *afp = fopen(APPOINTMENT_FILE, "rb");
    if (!afp) {
        printf("Could not open appointment file.\n");
        fclose(fp);
        return;
    }
    Appointment a;
    int found = 0;
    while (fread(&a, sizeof(Appointment), 1, afp)) {
        if (a.id == appointmentId) {
            found = 1;
            break;
        }
    }
    fclose(afp);

    if (!found) {
        printf("Appointment ID not found.\n");
        fclose(fp);
        return;
    }

    printf("Enter consultation fee: ");
    scanf("%f", &bill.consultationFee);
    printf("Enter medication cost: ");
    scanf("%f", &bill.medicationCost);
    printf("Enter lab charges: ");
    scanf("%f", &bill.labCharges);
    getchar();

    bill.appointmentId = appointmentId;
    bill.totalAmount = bill.consultationFee + bill.medicationCost + bill.labCharges;
    
    printf("Enter payment status (paid/pending/partial): ");
    fgets(bill.paymentStatus, sizeof(bill.paymentStatus), stdin);
    bill.paymentStatus[strcspn(bill.paymentStatus, "\n")] = 0;

    fwrite(&bill, sizeof(Bill), 1, fp);
    fclose(fp);

    printf("Bill generated successfully. Total Amount: $%.2f\n", bill.totalAmount);
}

void listBills() {
    FILE *fp = fopen(BILL_FILE, "rb");
    if (!fp) {
        printf("No bills generated yet.\n");
        return;
    }
    Bill bill;
    printf("\n--- Bills ---\n");
    printf("Appt ID\tConsultation\tMedication\tLab\tTotal\t\tStatus\n");
    while (fread(&bill, sizeof(Bill), 1, fp)) {
        printf("%d\t$%.2f\t\t$%.2f\t\t$%.2f\t$%.2f\t\t%s\n", 
            bill.appointmentId, bill.consultationFee, bill.medicationCost, 
            bill.labCharges, bill.totalAmount, bill.paymentStatus);
    }
    fclose(fp);
}

int main() {
    printf("Welcome to Advanced Hospital Management System\n");
    printf("Loading system...\n");
    menu();
    return 0;
}