#include <stdio.h>
#include "student.h"
#include <string.h>

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

int main() {
    Database db;

    int capacity;
    int choice = 0;
    int id;
    float gpa;
    char name[MAX_NAME];

    // Sets size for database
    printf("Set size for database: ");
    scanf ("%d", &capacity);

    init_db(&db, capacity); // Initializes database

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
        scanf("%d", &choice);

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
                scanf ("%d", &id);
                printf("Enter student gpa: ");
                scanf ("%f", &gpa);
                printf("Enter student name: ");
                while (getchar() != '\n'); // Clears the newline character left in stdin by scanf
                readString(name, MAX_NAME);

                addStudent(&db, id, gpa, name);
                break;
            case 2: // Searches for a student by id
                printf("Enter student id: ");
                scanf ("%d", &id);

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
                scanf ("%d", &id);
                printf("Enter student gpa: ");
                scanf ("%f", &gpa);
                printf("Enter student name: ");
                while (getchar() != '\n'); // Clears the newline character left in stdin by scanf
                readString(name, MAX_NAME);

                updateStudent(&db, id, gpa, name);
                break;
            case 5: // Deletes a student from database
                printf("Enter student id: ");
                scanf ("%d", &id);

                deleteStudent(&db, id);
                break;
            case 6: // Frees memory
                free_db(&db);
                printf("Memory freed successfully");
                break;
            case 7: // Initializes a database
                // Sets size for database
                printf("Set size for database: ");
                scanf ("%d", &capacity);

                init_db(&db, capacity); // Initializes database
                printf("Database created successfully of size %d\n", capacity);
                break;
            case 8: // Exits program
                break;
            default: // Makes sure the choice is a valid option
                printf("Choice was not an option, please select a valid option \n\n");
                break;
        }
    }

    free_db(&db); // Frees memory at the end of the program in the background when program ends

    return 0;
}