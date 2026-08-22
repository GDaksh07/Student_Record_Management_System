#include <stdio.h>
#include "student.h"

int main() {
    Database db;

    // Initializes memory
    printf("Creating database with a capacity of 2\n");
    init_db(&db, 2);

    // Adds students
    printf("Adding students\n");
    addStudent(&db, 101, 3.85f, "Alice Smith");
    addStudent(&db, 102, 3.42f, "Bob Jones");
    addStudent(&db, 103, 3.91f, "Charlie Brown");
    addStudent(&db, 104, 2.95f, "Diana Prince");

    displayAll(&db);

    // Frees memory
    free_db(&db);
    printf("Memory freed successfully");

    return 0;
}