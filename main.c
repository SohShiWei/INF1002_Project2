#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_PROGRAMME_LENGTH 50
#define FILENAME "students.txt"

typedef struct StudentRecord{
    int id;
    char name[MAX_NAME_LENGTH];
    char programme[MAX_PROGRAMME_LENGTH];
    float mark;
} StudentRecord;

int readRecords(const char *filename, StudentRecord records[], int max_records) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Unable to open file");
        return -1;      // Error code for file opening failure
    }

    int count = 0;
    while (count < max_records && fscanf(file, "%d %49s %49s %f", 
            &records[count].id, records[count].name, records[count].programme, &records[count].mark) == 4) {
        count++;
    }

    if (ferror(file)) {
        perror("Error reading file");
        fclose(file);
        return -2;  // Error code for file reading failure
    }

    fclose(file);
    return count;  // Return the number of records successfully read
}

void displayRecords(StudentRecord records[], int count) {
    printf("%-10s %-15s %-25s %-5s\n", "ID", "Name", "Programme", "Mark");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-10d %-15s %-25s %.1f\n", records[i].id, records[i].name, records[i].programme, records[i].mark);
    }
}

void showMenu() {
    printf("\n--- Student Records Menu ---\n");
    printf("1. Display All Records\n");
    printf("2. Search\n");
    printf("3. Update\n");
    printf("4. Delete\n");
    printf("5. Exit\n");
}

int main() {
    StudentRecord records[100];
    int recordCount = 0;
    char choice[10];
    recordCount = readRecords(FILENAME, records, 100);
    if (recordCount >= 0) {
        while (1) {
        showMenu();
        scanf("%s", choice);
        if (strcmp(choice, "1") == 0) {
            // Display all records
            if (recordCount > 0) {
                displayRecords(records, recordCount);
            } else {
                printf("\nNo records to display. Please load records first.\n");
            }
        } 
        else if (strcmp(choice, "2") == 0) {
            // Exit the program
            printf("\nSearch\n");
        
        }
        else if (strcmp(choice, "3") == 0) {
            // Exit the program
            printf("\nUpdate\n");
        
        }
        else if (strcmp(choice, "4") == 0) {
            // Exit the program
            printf("\nDelete\n");
        }
        else if (strcmp(choice, "5") == 0) {
            // Exit the program
            printf("\nExiting the program\n");
            break;
        }
        else {
            printf("\nInvalid choice. Please try again.\n");
        }
        }
    } else {
        printf("Error reading records.\n");
    }
    return 0;
}
