#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

// Initialize memory for database
void init_db (Database *db, size_t initialCapacity) {
    if (db == NULL) return;

    db->capacity = initialCapacity;
    db->count = 0;
    db->students = (Student *)malloc (initialCapacity * sizeof(Student));

    // Fail-safe for memory allocation
    if (db->students == NULL) {
        printf ("Failed to allocate memory for students\n");
        db->capacity = 0;
        return;
    }
}

// Free allocated memory
void free_db (Database *db) {
    if (db == NULL) return;

    free (db->students);
    db->students = NULL;
    db->count = 0;
    db->capacity = 0;
}

// Adds a student to the database and dynamically reallocates memory if more memory for the array is needed
int addStudent (Database *db, int id, float gpa, const char *name) {
    if (db == NULL || name == NULL) return 0;

    if (searchById(db, id) != NULL) {
        printf ("Student ID %d already exists\n", id);
        return 0;
    }

    if (db->count == db->capacity) {
        size_t newCapacity = (db->capacity == 0) ? 4 : db->capacity * 2;

        Student *temp = (Student *) realloc(db->students, newCapacity * sizeof(Student));

        if (temp == NULL) {
            printf ("Failed to allocate memory for students\n");
            return 0;
        }

        db->students = temp;
        db->capacity = newCapacity;
    }

    // Adds the student to respected value in the array
    db->students[db->count].id = id;
    db->students[db->count].gpa = gpa;
    strncpy(db->students[db->count].name, name, sizeof(db->students[db->count].name) - 1);
    db->students[db->count].name[sizeof(db->students[db->count].name) - 1] = '\0';

    db->count++;
    return 1;
}

// Displays all information about students inside the database
void displayAll (Database *db) {
    if (db == NULL || db->count == 0) {
        printf ("No data available\n");
        return;
    }

    printf("Student Database Records\n");
    printf("%-10s %-20s %-5.2s\n", "ID", "Name", "GPA");

    for (int i = 0; i < db->count; i++) {
        printf("%-10d %-20s %-5.2f\n",
            db->students[i].id,
            db->students[i].name,
            db->students[i].gpa);
    }
}

// Searches through the database for a specific id
Student* searchById (Database *db, int id) {
    if (db == NULL || db->count == 0) return NULL; // checks if database is empty

    // Looks through database to find student
    for (int i = 0; i < db->count; i++) {
        if (db->students[i].id == id) return &db->students[i];
    }

    // Returns NULL if no student found for specified id
    return NULL;
}

// Updates a specific students information
Student* updateStudent (Database *db, int id, float gpa, const char *name) {
    if (db == NULL || db->count == 0) return NULL; // checks if database is empty

    // Goes through the searchById function to see if a student exists
    Student *result = searchById(db, id);
    if (result == NULL) return NULL; // returns NULL if no student found

    // Updates the target record directly in place
    result->gpa = gpa;
    strncpy(result->name, name, MAX_NAME - 1);
    result->name[MAX_NAME - 1] = '\0';

    return result;
}

int deleteStudent (Database *db, int id) {
    if (db == NULL || db->count == 0) return 0; // checks if database is empty

    int index = -1;

    // finds students index
    for (int i = 0; i < db->count; i++) {
        if (db->students[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) return 0; // If no student is found

    // Shifts elements to the left by 1 starting at targeted index
    for (int i = index; i < db->count - 1; i++) {
        db->students[i] = db->students[i + 1];
    }

    db->count--; // count goes down by 1 for the student removal
    return 1;
}