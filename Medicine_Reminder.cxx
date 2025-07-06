#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifdef _WIN32
#include <windows.h>
#define SLEEP(ms) Sleep(ms)
#else
#include <unistd.h>
#define SLEEP(ms) usleep(ms * 1000)
#endif

#define MAX_TIMES 5
#define MAX_MEDICINES 100

struct Medicine {
    char name[50];
    char dosage[20];
    int numTimes;
    int hour[MAX_TIMES];
    int minute[MAX_TIMES];
};


void displayTime(int hour, int minute) {
    char ampm[3] = "AM";
    if (hour >= 12) {
        ampm[0] = 'P';
        if (hour > 12) hour -= 12;
    }
    if (hour == 0) hour = 12;
    printf("%02d:%02d %s", hour, minute, ampm);
}

void addMedicine() {
    struct Medicine med;
    FILE *fp = fopen("medicine_data.txt", "a");

    if (fp == NULL) {
        printf(" Error opening file!\n");
        return;
    }

    printf("\nEnter medicine name: ");
    scanf(" %[^\n]", med.name);

    printf("Enter dosage (e.g., 1 tablet): ");
    scanf(" %[^\n]", med.dosage);

    printf("How many times to take per day (max %d)? ", MAX_TIMES);
    scanf("%d", &med.numTimes);

    for (int i = 0; i < med.numTimes; i++) {
        printf("Enter time %d (24-hour format - HH MM): ", i + 1);
        scanf("%d %d", &med.hour[i], &med.minute[i]);
    }

    fwrite(&med, sizeof(struct Medicine), 1, fp);
    fclose(fp);
    printf("Medicine added successfully!\n");
}

void viewMedicines() {
    struct Medicine med;
    FILE *fp = fopen("medicine_data.txt", "r");

    if (fp == NULL) {
        printf(" No medicine data found.\n");
        return;
    }

    printf("\n Saved Medicines:\n");

    while (fread(&med, sizeof(struct Medicine), 1, fp)) {
        printf("\nMedicine: %s\nDosage: %s\nTimes: ", med.name, med.dosage);
        for (int i = 0; i < med.numTimes; i++) {
            displayTime(med.hour[i], med.minute[i]);
            printf("  ");
        }
        printf("\n");
    }

    fclose(fp);
}

void checkReminder() {
    struct Medicine med;
    FILE *fp;
    time_t now;
    struct tm *current;
    
    printf("\n Reminder system started. It will check every 30 seconds.\nPress Ctrl+C to exit.\n");

    while (1) {
        now = time(NULL);
        current = localtime(&now);

        int currHour = current->tm_hour;
        int currMin = current->tm_min;

        fp = fopen("medicine_data.txt", "r");
        if (fp == NULL) continue;

        while (fread(&med, sizeof(struct Medicine), 1, fp)) {
            for (int i = 0; i < med.numTimes; i++) {
                if (currHour == med.hour[i] && currMin == med.minute[i]) {
                    printf("\a");
                    printf("\n Reminder: Take %s (%s) now at ", med.name, med.dosage);
                    displayTime(currHour, currMin);
                    printf("!\n");
                    
                    char snooze;
                    printf("Snooze reminder for 5 mins? (y/n): ");
                    scanf(" %c", &snooze);
                    if (snooze == 'y' || snooze == 'Y') {
                        printf(" Snoozed for 5 minutes...\n");
                        SLEEP(300000); 
                    } else
                     {
                        SLEEP(60000); 
                    }
                }
            }
        }
        fclose(fp);
        SLEEP(30000);  
    }
}

int main() {
    int choice;
    while (1) {
        printf("\n===== Smart Medicine Reminder Menu =====\n");
        printf("1.Add Medicine\n");
        printf("2.View Medicines\n");
        printf("3.Start Reminder System\n");
        printf("4.Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addMedicine(); break;
            case 2: viewMedicines(); break;
            case 3: checkReminder(); break;
            case 4: exit(0);
            default: printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}
