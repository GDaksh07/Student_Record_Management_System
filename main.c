#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "student.h"

// Helper method to read strings safely including spaces
void readString(char *buffer, int size) {
    if (fgets(buffer, size, stdin) != NULL) {
        // Strip trailing newline character left by fgets
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
    }
}

// Helper method to read integers safely
int readInt(int *outValue) {
    char buffer[64];

    // Read raw input line from terminal
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0; // Failed to read
    }

    char *endptr;
    // strtol converts string to long int (base 10)
    long val = strtol(buffer, &endptr, 10);

    // Check if valid digits were parsed
    if (endptr == buffer) {
        return 0; // User typed text instead of numbers (e.g., "abc")
    }

    // Check if leftover characters exist (e.g., "12abc")
    if (*endptr != '\n' && *endptr != '\0') {
        return 0; // Invalid extra input
    }

    *outValue = (int)val;
    return 1;
}

// Helper method to read floats safely
int readFloat(float *outValue) {
    char buffer[64];

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }

    char *endptr;
    float val = strtof(buffer, &endptr);

    if (endptr == buffer) {
        return 0; // No valid float found
    }

    if (*endptr != '\n' && *endptr != '\0') {
        return 0; // Invalid trailing text
    }

    *outValue = val;
    return 1;
}

void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    Database db;
    db.students = NULL;
    db.capacity = 0;
    db.count = 0;

    int capacity;
    int choice = 0;
    int id;
    float gpa;
    char name[MAX_NAME];

    // Attempt to load existing file first
    if (loadDbFromFile(&db, "students.bin")) {
        printf("Loaded existing database with %d records (Capacity: %d).\n", db.count, db.capacity);
    } else {
        printf("No existing database found. Let's create a new one.\n");
        printf("Set size for database: "); // Sets size for database
        while (!readInt(&capacity)) {
            printf("Invalid input! Please enter a numeric capacity: ");
        }

        init_db(&db, capacity); // Initializes database
    }

    // Check internal array pointer instead of struct variable
    if (db.students == NULL) {
        printf("Error: Database allocation failed or initialized with 0 capacity.\n");
        return 1; // Exit main early
    }

    printf("Database created successfully of size %d", capacity); // Tells user that database was created with no errors

    while (choice != 8) {
        // Prompts user for selection of what they want to do to the database
        printf("Select one of the following options:\n"
               "1: Add a student\n"
               "2: Search for a student by id\n"
               "3: Display all students\n"
               "4: Update a students information\n"
               "5: Delete a student from the database\n"
               "6: Free database\n"
               "7: Create a Database\n"
               "8: Exit\n"
               "Choice: ");
        while (!readInt(&choice)) {
            printf("Invalid input! Please enter a numeric choice: ");
        }

        // Checks to see if database exists
        if (choice >= 1 && choice <= 6 && db.capacity == 0) {
            printf("Database doesn't exist, please initialize a capacity for the database");
            continue;
        } else if (choice == 7 && db.capacity != 0) {
            printf("Database already exists");
            continue;
        }

        switch (choice) {
            case 1: // Adds a student to database
                printf("Enter student id: ");
                while (!readInt(&id)) {
                    printf("Invalid input! Please enter a numeric ID: ");
                }
                printf("Enter student gpa: ");
                while (!readFloat(&gpa)) {
                    printf("Invalid input! Please enter a valid decimal GPA: ");
                }
                printf("Enter student name: ");
                readString(name, MAX_NAME);

                addStudent(&db, id, gpa, name);
                break;
            case 2: // Searches for a student by id
                printf("Enter student id: ");
                while (!readInt(&id)) {
                    printf("Invalid input! Please enter a numeric ID: ");
                }

                Student* s = searchById(&db, id);

                if (s != NULL) {
                    printf("%s has a gpa of %.2f\n", s->name, s->gpa);
                } else {
                    printf("Student with ID %d not found.\n", id);
                }
                break;
            case 3: // Displays all students in database
                displayAll(&db);
                break;
            case 4: // Updates a students information
                printf("Enter student id: ");
                while (!readInt(&id)) {
                    printf("Invalid input! Please enter a numeric ID: ");
                }
                printf("Enter student gpa: ");
                while (!readFloat(&gpa)) {
                    printf("Invalid input! Please enter a valid decimal GPA: ");
                }
                printf("Enter student name: ");
                readString(name, MAX_NAME);

                updateStudent(&db, id, gpa, name);
                break;
            case 5: // Deletes a student from database
                printf("Enter student id: ");
                while (!readInt(&id)) {
                    printf("Invalid input! Please enter a numeric ID: ");
                }

                deleteStudent(&db, id);
                break;
            case 6: // Frees memory
                free_db(&db);
                printf("Memory freed successfully");
                break;
            case 7: // Initializes a database
                // Sets size for database
                printf("Set size for database: ");
                while (!readInt(&capacity)) {
                    printf("Invalid input! Please enter a numeric capacity: ");
                }

                init_db(&db, capacity); // Initializes database
                printf("Database created successfully of size %d\n", capacity);
                break;
            case 8: // Exits program
                break;
            default: // Makes sure the choice is a valid option
                printf("Choice was not an option, please select a valid option \n\n");
                break;
        }

        saveDbToFile(&db, "students.bin");
    }

    free_db(&db); // Frees memory at the end of the program in the background when program ends

    return 0;
}