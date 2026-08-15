#ifndef STUDENT_RECORD_MANAGEMENT_SYSTEM_STUDENT_H
#define STUDENT_RECORD_MANAGEMENT_SYSTEM_STUDENT_H

#define MAX_NAME 50

typedef struct {
    int id;
    char name[MAX_NAME];
    float gpa;
} Student;

typedef struct {
    Student *students;
    int count;
    int capacity;
} Database;

// Function Prototypes
void init_db(Database *db, size_t initialCapacity);
void free_db(Database *db);
int addStudent(Database *db, int id, float gpa, const char *name);
void displayAll(Database *db);

#endif //STUDENT_RECORD_MANAGEMENT_SYSTEM_STUDENT_H