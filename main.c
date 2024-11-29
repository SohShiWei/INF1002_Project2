

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_NAME_LENGTH 50
#define MAX_PROGRAMME_LENGTH 50
#define FILENAME "./P7_7-CMS.txt"

typedef struct StudentRecord{
    int id;
    char name[MAX_NAME_LENGTH];
    char programme[MAX_PROGRAMME_LENGTH];
    float mark;
} StudentRecord;

int isValidInt(const char *str);

int InsertRecord(StudentRecord records[], int count){
    int c; 
    //Wait for response
    while ((c = getchar()) != '\n' && c!= EOF);
    int inputid;
    char buffer[100];
    char *endptr;
    //Retrieve ID of new record
    printf("Enter the student ID you wish to insert:\n");
    fgets(buffer,sizeof(buffer),stdin);
    int isValid = 1;
    for (int i = 0; buffer[i] != '\n' && buffer[i] != '\0'; i++) {
        if (!isdigit(buffer[i])) {
            isValid = 0;
            break;
        }
    }

    if (!isValid) {
        printf("Invalid input: Please enter only numeric digits.\n");
        return count;
    }
    int len = strlen(buffer);
    inputid = atoi(buffer);
    //Calculate digits to ensure student ID is a valid combination of 7 numbers
    int digitcount = (int)log10(inputid)+1;
    if (digitcount < 7 || digitcount > 7){
        printf("Please enter a valid student ID");
        return count;
    }
    else{
        //Check if ID already used in records
        for (int i=0; i < count; i++){
            if(inputid == records[i].id){
                printf("student ID already exists!");
                inputid = 0;
            }
        }
        if (inputid != 0){    
            char name [50];
            printf("Enter the name of the student:\n");
            fgets(name,sizeof(name),stdin);
            name[strcspn(name, "\n")] = '\0';
            
            for (int i = 0; name[i] != '\0'; i++) {
                if (!isalpha(name[i]) && name[i] != ' ') { // Allow alphabetic characters and spaces
                    printf("Name can only include alphabets. Please enter a valid name.\n");
                    return count; // Return 0 if non-alphabetic character is found
                }
            }
            if (strlen(name) == 0) {
                printf("Name cannot be empty. Please enter a valid name.\n");
                return count;
            } 
            for(int i = 0; name[i] != '\0'; i++){
                if(name[i]==' '){
                    name[i] = '_';
                }
            }
            char programme [50];
            printf("Enter the programme of the student:\n");
            fgets(programme,sizeof(programme),stdin);
            programme[strcspn(programme,"\n")] = '\0';
            for (int i = 0; programme[i] != '\0'; i++) {
                if (!isalpha(programme[i]) && programme[i] != ' ') { // Allow alphabetic characters and spaces
                    printf("Programme can only include alphabets. Please enter a valid programme.\n");
                    return count; // Return 0 if non-alphabetic character is found
                }
            }
            if (strlen(programme) == 0) {
                printf("Programme cannot be empty. Please enter a valid programme.\n");
                return count;
            } 
            printf("Enter the marks of the student:\n"); 
            char markbuffer[100];
            fgets(markbuffer,sizeof(markbuffer),stdin);
            markbuffer[strcspn(markbuffer, "\n")] = '\0';
            // Check if input is valid
            if (markbuffer[0] == '\0'){
                printf("Invalid marks");
                return count;
            }
            float inputFloat = strtof(markbuffer,&endptr);
            //Check for valid input for Marks
            if(inputFloat < 0){
                printf("Marks cannot be negative, Please enter a valid value for Marks");
                return count;
            }else if (inputFloat > 100){
                printf("Marks cannot be more than 100, Please enter a valid value for Marks");
                return count;
            }
            else{
                //Insert into records
                records[count].id = inputid;
                strcpy(records[count].name, name);
                strcpy(records[count].programme, programme);
                records[count].mark = inputFloat;
                printf("A new record with ID=%i is successfully inserted.\n",inputid);
                count = count+1;
                return count;
            }
        }
        else{
            return count;
        }
    }
}

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

    if (scanf("%d", &id) != 1 || id < 0) {
        printf("\nInvalid input. Please enter a valid integer ID.\n");
        while (getchar() != '\n'); // Clear the input buffer
        return;
    }

    if (id >= 1000000 && id <= 9999999) // Checks if the ID is exactly 7 digits //Checks if the ID is valid
        {
        int index = queryRecord(records, count, id); //Calls the queryRecord function to search for the record
        if (index != -1) {
            printf("\nThe record with ID=%d is found in the data table.\n\n", id);
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
// Delete record
void deleteRecord(StudentRecord records[], int *count, int id) {
    int index = queryRecord(records, *count, id);
    if (index != -1) {
        char confirmation;
        printf("Are you sure you want to delete the record with ID %d? (y/n): ", id);
        // Wait for the user to enter 'y' or 'n'
        while (1) {
            scanf(" %c", &confirmation);  // Adding a space before %c to skip any leftover newline characters
            if (confirmation == 'y' || confirmation == 'Y') {
                // Proceed to delete the record
                records[index] = records[--(*count)];  // Replace the record with the last record and reduce count
                printf("Record with ID %d deleted successfully.\n", id);
                return;
            } else if (confirmation == 'n' || confirmation == 'N') {
                printf("Record deletion canceled.\n");
                return;
            } else {
                printf("Invalid input. Please enter 'y' for yes or 'n' for no: ");
            }
        }
    } else {
        printf("Record with ID %d not found.\n", id);
    }
}
int readRecords(const char *filename, StudentRecord records[], int max_records) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("Unable to open file");
        return -1;      // Error code for file opening failure
    }

    int count = 0;
    printf("Opened File: %s\n", FILENAME);
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

int isValidInt(const char *str) {
    char *endptr;
    strtol(str, &endptr, 10); // Convert string to long, store pointer to endptr

    // Check if the entire string was converted, points to null terminator which is at the end of the string
    // if entire string is converted, points '\0' and return '1' (TRUE)
    // if not, it points to the char found and not to '\0', and return '0' (FALSE)
    return *endptr == '\0'; 
}

int isValidStr(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isalpha(str[i]) && str[i] != '_' && str[i] != ' ') {
            return 0; // Return 0 if invalid character found
        }
        if (str[i] == '_' && str[i+1] == '_') { //Check for double underscore
            printf("Multiple underscore found. Please enter a valid name.\n");
            return 0; // Return 0 if double underscore found
        }
        if (str[i] == ' ') { //Convert space to underscore
                str[i] = '_';
            }
    }
    return 1; // Return 1 if all characters are valid
}

int isValidFloat(const char *str) {
    char *endptr;
    strtof(str, &endptr); // Convert string to float, store pointer to endptr

    // Check if the entire string was converted, points to null terminator which is at the end of the string
    // if entire string is converted, points '\0' and return '1' (TRUE)
    // if not, it points to the char found and not to '\0', and return '0' (FALSE)
    return *endptr == '\0'; 
}

void updateRecord(StudentRecord records[], int count) {
    int updateId;
    char idBuffer[50];
    getchar(); //Clear input buffer

    do {
        printf("Enter the ID of the record to update: ");
        fgets(idBuffer, sizeof(idBuffer), stdin);
        idBuffer[strcspn(idBuffer, "\n")] = '\0'; //Remove newline char
        int digitcount = (int)log10(atoi(idBuffer))+1;
        if (strlen(idBuffer) == 0) {
            printf("ID cannot be empty. Please enter a valid ID.\n");
        } else if (!isValidInt(idBuffer)) {
            printf("Invalid characters found. Please enter a valid ID.\n");
        } else if (digitcount < 7 || digitcount > 7) {
            printf("Please enter a valid student ID. \n");
        }
    } while (strlen(idBuffer) == 0 || !isValidInt(idBuffer) || (int)log10(atoi(idBuffer))+1 < 7 || (int)log10(atoi(idBuffer))+1 > 7); 
    //While input is empty OR not a valid int OR not valid ID length, repeat

    char *endptr;
    updateId = strtol(idBuffer, &endptr, 10); // Convert string to long, store pointer to endptr

    for (int i = 0; i < count; i++) {
        if (records[i].id == updateId) { //If ID found, proceed to update
            int choice;
            char buffer[50];
            float mark;
            do {
                printf("1. Name\n");
                printf("2. Programme\n");
                printf("3. Mark\n");
                printf("4. All fields\n");
                printf("5. Exit\n");
                printf("Enter your choice: ");
                fgets(buffer, sizeof(buffer), stdin); //Read input from user, prevent empty input
                buffer[strcspn(buffer, "\n")] = '\0'; //Remove newline char
                if (strlen(buffer) == 0) {
                    printf("Name cannot be empty. Please enter a valid option.\n");
                } else if (!isValidInt(buffer)) {
                    printf("Invalid characters found. Please enter a valid option.\n");
                } else if ((choice = strtol(buffer, NULL, 10)) < 0) {
                    printf("Please enter a valid option.\n");
                } else if ((choice = strtol(buffer, NULL, 10)) > 5) {
                    printf("Please enter a valid option.\n");
                }
                choice = strtol(buffer, NULL, 10);
            } while (strlen(buffer) == 0 || !isValidInt(buffer) || choice < 1 || choice > 5);

            if (choice == 1) {
                do {
                    printf("Enter new name: ");
                    fgets(buffer, sizeof(buffer), stdin); //Read input from user, prevent empty input
                    buffer[strcspn(buffer, "\n")] = '\0'; //Remove newline char
                    if (strlen(buffer) == 0) {
                        printf("Name cannot be empty. Please enter a valid name.\n");
                    } else if (!isValidStr(buffer)) {
                        printf("Invalid characters found. Please enter a valid name.\n");
                    }
                } while (strlen(buffer) == 0 || !isValidStr(buffer)); //While input empty OR not valid str
                strcpy(records[i].name, buffer);

            } else if (choice == 2) {
                do {
                    printf("Enter new programme: ");
                    fgets(buffer, sizeof(buffer), stdin); //Read input from user, prevent empty input
                    buffer[strcspn(buffer, "\n")] = '\0'; //Remove newline char
                    if (strlen(buffer) == 0) {
                        printf("Programme cannot be empty. Please enter a valid programme.\n");
                    } else if (!isValidStr(buffer)) {
                        printf("Invalid characters found. Please enter a valid programme.\n");
                    }
                } while (strlen(buffer) == 0 || !isValidStr(buffer)); //While input empty OR not valid str
                strcpy(records[i].programme, buffer);

            } else if (choice == 3) {
                do {
                    printf("Enter new mark: ");
                    fgets(buffer, sizeof(buffer), stdin);
                    buffer[strcspn(buffer, "\n")] = '\0'; //Remove newline char
                    if (strlen(buffer) == 0) {
                        printf("Mark cannot be empty. Please enter a valid mark.\n");
                    } else if (!isValidFloat(buffer)) {
                        printf("Invalid characters found. Please enter a valid mark.\n");
                    } else if ((mark = strtof(buffer, NULL)) < 0) {
                        printf("Mark cannot be negative. Please enter a valid mark.\n");
                    } else if ((mark = strtof(buffer, NULL)) > 100) {
                        printf("Mark cannot be more than 100. Please enter a valid mark.\n");
                    }
                } while (strlen(buffer) == 0 || !isValidFloat(buffer) || (mark = strtof(buffer, NULL)) < 0 || (mark = strtof(buffer, NULL)) > 100); 
                //while input empty OR not valid float OR negative value OR more than 100, repeat
                records[i].mark = mark;

            } else if (choice == 4) {
                do {
                    printf("Enter new name: ");
                    fgets(buffer, sizeof(buffer), stdin); //Read input from user, prevent empty input
                    buffer[strcspn(buffer, "\n")] = '\0'; //Remove newline char
                    if (strlen(buffer) == 0) {
                        printf("Name cannot be empty. Please enter a valid name.\n");
                    } else if (!isValidStr(buffer)) {
                        printf("Invalid characters found. Please enter a valid name.\n");
                    }
                } while (strlen(buffer) == 0 || !isValidStr(buffer)); //While input empty OR not valid str
                strcpy(records[i].name, buffer);

                do {
                    printf("Enter new programme: ");
                    fgets(buffer, sizeof(buffer), stdin); //Read input from user, prevent empty input
                    buffer[strcspn(buffer, "\n")] = '\0'; //Remove newline char
                    if (strlen(buffer) == 0) {
                        printf("Programme cannot be empty. Please enter a valid programme.\n");
                    } else if (!isValidStr(buffer)) {
                        printf("Invalid characters found. Please enter a valid programme.\n");
                    }
                } while (strlen(buffer) == 0 || !isValidStr(buffer)); //While input empty OR not valid str
                strcpy(records[i].programme, buffer);

                do {
                    printf("Enter new mark: ");
                    fgets(buffer, sizeof(buffer), stdin);
                    buffer[strcspn(buffer, "\n")] = '\0'; //Remove newline char
                    if (strlen(buffer) == 0) {
                        printf("Mark cannot be empty. Please enter a valid mark.\n");
                    } else if (!isValidFloat(buffer)) {
                        printf("Invalid characters found. Please enter a valid mark.\n");
                    } else if ((mark = strtof(buffer, NULL)) < 0) {
                        printf("Mark cannot be negative. Please enter a valid mark.\n");
                    } else if ((mark = strtof(buffer, NULL)) > 100) {
                        printf("Mark cannot be more than 100. Please enter a valid mark.\n");
                    }
                } while (strlen(buffer) == 0 || !isValidFloat(buffer) || (mark = strtof(buffer, NULL)) < 0 || (mark = strtof(buffer, NULL)) > 100); 
                //while input empty OR not valid float OR negative value OR more than 100, repeat
                records[i].mark = mark;

            } else if (choice == 5) {
                return;
            } 
        
        
        printf("Record updated successfully.\n");
        return; 
        }
    }
    printf("Record with ID %d not found.\n", updateId); //Error message if ID not found
}

void showMenu() {
    printf("\n--- Student Records Menu ---\n");
    printf("0. Open File\n");
    printf("1. Display All Records\n");
    printf("2. Insert\n");
    printf("3. Search\n");
    printf("4. Update\n");
    printf("5. Delete\n");
    printf("6. Save\n");
    printf("7. Exit\n");
    printf("\nEnter your choice: ");
}

int Save(const char *filename, StudentRecord records[], int max_records) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Unable to open file");
        return -1;      // Error code for file opening failure
    }
    if (ferror(file)) {
        perror("Error reading file");
        fclose(file);
        return -2;  // Error code for file reading failure
    }
    for(int i = 0; i<max_records;i++){
        fprintf(file, "%-10d %-20s %-25s %8.1f\n",records[i].id,records[i].name,records[i].programme,records[i].mark);
    }
    printf("The database %s is successfully saved",FILENAME);
    fclose(file);

    return 0;
}

void Declaration() {
    printf("\"\n");
    printf("                                             Declaration                      \n");
    printf("SIT's policy on copying does not allow the students to copy source code as well as assessment solutions\nfrom another person or other places. It is the students’ responsibility to guarantee that their assessment\nsolutions are their own work. Meanwhile, the students must also ensure that their work is not accessible\nby others. Where such plagiarism is detected, both of the assessments involved will receive ZERO mark.\n\n");

    printf("We hereby declare that:\n");
    printf("- We fully understand and agree to the abovementioned plagiarism policy.\n");
    printf("- We did not copy any code from others or from other places.\n");
    printf("- We did not share our codes with others or upload to any other places for public access and will\n  not do that in the future.\n");
    printf("- We agree that our project will receive Zero mark if there is any plagiarism detected.\n");
    printf("- We agree that we will not disclose any information or material of the group project to others or upload to any other places for public access.\n\n");

    printf("Declared by: P7_7\n");
    printf("Team members:\n");
    printf("1. Matthew Chua Xiang Jun\n");
    printf("2. Pek Jun Teck Keith\n");
    printf("3. Soh Shi Wei\n");
    printf("4. Hing Zheng Wen\n");
    printf("5. Choo Zhi Xuan\n\n");
    printf("Date: 29 November 2024.\n");
    printf("\"");
}

int main() {
    StudentRecord records[100];
    Declaration();
    int recordCount = 0;
    char choice[10];
    if (recordCount >= 0) {
        while (1) {
        showMenu();
        scanf("%s", choice);
        if (strcmp(choice, "0") == 0) {
            recordCount = readRecords(FILENAME, records, 100);
        } 
        else if (strcmp(choice,"1")== 0){
            // Display all records
            if (recordCount > 0) {
                displayRecords(records, recordCount);
            } else {
                printf("\nNo records to display. Please load records first.\n");
            }
        }
        else if (strcmp(choice, "2") == 0) {
            if (recordCount > 0) {    
                recordCount = InsertRecord(records,recordCount);   
            }else{
                printf("\nNo records available. Please load records first.\n");
            }
        }
        else if (strcmp(choice, "3") == 0) {
            // Search for a record
            queryById(records, recordCount);
        }
        else if (strcmp(choice, "4") == 0) {
            // Update selected record based on ID
            updateRecord(records, recordCount);
        }
        else if (strcmp(choice, "5") == 0) {
            // Delete existing records
             if (recordCount > 0) {
                int id;
                printf("Enter the ID of the record to delete: ");
                scanf("%d", &id);
                deleteRecord(records, &recordCount, id);
            } else {
                printf("\nNo records available to delete.\n");
            }
        } 
        else if (strcmp(choice, "6") == 0){
            // Save to file
            Save(FILENAME,records,recordCount);
            printf("\nSave\n");
        }
        else if (strcmp(choice, "7") == 0) {
            // Exit the program
            char saveorno[2];
            printf("Do you wish to save before you exit? (Y/N)");
            scanf("%s",saveorno);
            if(strcmp(saveorno, "Y") == 0){
                Save(FILENAME,records,recordCount);
                break;
            }
            else if(strcmp(saveorno, "N") == 0) {
                printf("Exiting... \n");
                break;
            }
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
