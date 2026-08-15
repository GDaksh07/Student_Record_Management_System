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
    printf("%-10s %-20s %-5s\n", "ID", "Name", "GPA");

    for (int i = 0; i < db->count; i++) {
        printf("%-10d %-20s %-5f\n",
            db->students[i].id,
            db->students[i].name,
            db->students[i].gpa);
    }
}