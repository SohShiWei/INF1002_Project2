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

void deleteRecord(StudentRecord records[], int *count, int id) {
    // Step 1: Search for the record by ID
    int index = searchRecord(records, *count, id);

    if (index == -1) {
        // If no record is found then
        printf("Record with ID %d not found.\n", id);
        return;
    }

    // Step 2: Ask for confirmation to delete
    char confirmation;
    printf("Are you sure you want to delete the record with ID %d? (Y/N): ", id);
    scanf(" %c", &confirmation);  // Notice the space before %c to skip any leftover newline

    if (confirmation == 'Y' || confirmation == 'y') {
        // Step 3: Delete the record by shifting elements
        for (int i = index; i < *count - 1; i++) {
            records[i] = records[i + 1];
        }
        (*count)--;  // Decrease the total number of records
        printf("Record with ID %d deleted successfully.\n", id);
    } else {
        // Step 4: If the user cancels the deletion
        printf("Deletion canceled. No record was deleted.\n");
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
