#ifndef STUDENT_RECORD_MANAGEMENT_SYSTEM_STUDENT_H
#define STUDENT_RECORD_MANAGEMENT_SYSTEM_STUDENT_H

#include <stddef.h>

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
Student* searchById(Database *db, int id);
Student* updateStudent(Database *db, int id, float gpa, const char *name);
int deleteStudent(Database *db, int id);
int saveDbToFile(Database *db, const char *filename);
int loadDbFromFile(Database *db, const char *filename);
int compareByGPAAscending(const void *a, const void *b);
int compareByGPADescending(const void *a, const void *b);
int compareByNameAscending(const void *a, const void *b);
int compareByNameDescending(const void *a, const void *b);
void sortByGPAAscending(Database *db);
void sortByGPADescending(Database *db);
void sortByNameAscending(Database *db);
void sortByNameDescending(Database *db);

#endif //STUDENT_RECORD_MANAGEMENT_SYSTEM_STUDENT_H