#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_PROGRAMME_LENGTH 50
#define FILENAME "./students.txt"

typedef struct StudentRecord{
    int id;
    char name[MAX_NAME_LENGTH];
    char programme[MAX_PROGRAMME_LENGTH];
    float mark;
} StudentRecord;

int queryRecord(StudentRecord records[], int count, int id) // Function to search for a record by ID
{
    for (int i = 0; i < count; i++) {
        if (records[i].id == id) {
            return i;
        }
    }
    return -1;
}
void queryById(StudentRecord records[], int count) // Function to search for a record by ID
{
    int id;
    printf("\nEnter the student ID to search: ");
    scanf("%d", &id);

    if (id >= 0) //Checks if the ID is valid
        {
        int index = queryRecord(records, count, id); //Calls the queryRecord function to search for the record
        if (index != -1) {
            printf("\nThe record with ID=%d is found in the data table.\n", id);
            printf("%-10s %-15s %-25s %-5s\n", "ID", "Name", "Programme", "Mark");
            printf("---------------------------------------------------------------\n");
            printf("%-10d %-15s %-25s %.1f\n", records[index].id, records[index].name, records[index].programme, records[index].mark);
        }
        else //If the ID does not exist
        {
            printf("\nThe record with ID = %d does not exist.\n", id);

        }
    }
    else//If the ID is invalid
    {
        printf("\nInvalid ID. Please try again.\n");
        return;
    }

}

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
void Declaration() {
    printf("\"\n");
    printf("                                             Declaration                      \n");
    printf("SIT’s policy on copying does not allow the students to copy source code as well as assessment solutions\nfrom another person or other places. It is the students’ responsibility to guarantee that their assessment\nsolutions are their own work. Meanwhile, the students must also ensure that their work is not accessible\nby others. Where such plagiarism is detected, both of the assessments involved will receive ZERO mark.\n\n");

    printf("We hereby declare that:\n");
    printf("• We fully understand and agree to the abovementioned plagiarism policy.\n");
    printf("• We did not copy any code from others or from other places.\n");
    printf("• We did not share our codes with others or upload to any other places for public access and will\n  not do that in the future.\n");
    printf("• We agree that our project will receive Zero mark if there is any plagiarism detected.\n");
    printf("• We agree that we will not disclose any information or material of the group project to others or upload to any other places for public access.\n\n");

    printf("Declared by: P7_7\n");
    printf("Team members:\n");
    printf("1. Matthew Chua Xiang Jun\n");
    printf("2. Pek Jun Teck Keith\n");
    printf("3. Soh Shi Wei\n");
    printf("4. Hing Zheng Wen\n");
    printf("5. Choo Zhi Xuan\n\n");
    printf("Date: (please insert the date when you submit your group project).\n");
    printf("\"");
}

int main() {
    StudentRecord records[100];
    Declaration();
    int recordCount = 0;
    char choice[10];
    recordCount = readRecords(FILENAME, records, 100);
    if (recordCount >= 0) {
        while (1) {
        showMenu();
        printf("\nEnter your choice: ");
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
            // Search for a record
            queryById(records, recordCount);

        
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
