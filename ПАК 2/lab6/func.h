#ifndef FUNC_H
#define FUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_GROUP_LENGTH 20
#define NUM_EXAMS 5

typedef struct {
    unsigned int id;
    char firstName[MAX_NAME_LENGTH];
    char lastName[MAX_NAME_LENGTH];
    char group[MAX_GROUP_LENGTH];
    unsigned char *grades;
} Student;

Student* readStudentsFromFile(const char *filename, int *count);
void freeStudents(Student *students, int count);

void searchById(const Student *students, int count);
void searchByLastName(const Student *students, int count);
void searchByFirstName(const Student *students, int count);
void searchByGroup(const Student *students, int count);

void sortById(Student *students, int count);
void sortByLastName(Student *students, int count);
void sortByFirstName(Student *students, int count);
void sortByGroup(Student *students, int count);

void writeStudentToTraceFile(const Student *students, int count);
void writeStudentsAboveAverage(const Student *students, int count);

void printStudents(const Student *students, int count);
void printMenu();

#endif
