#include <stdio.h>
#include <stdlib.h>
#include "func.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Использование: %s <файл_студентов>\n", argv[0]);
        return 1;
    }

    int count = 0;
    Student *students = readStudentsFromFile(argv[1], &count);
    
    if (!students) {
        printf("Не удалось загрузить данные\n");
        return 1;
    }

    printf("Загружено %d студентов\n", count);

    int choice;
    do {
        printMenu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: searchById(students, count); break;
            case 2: searchByLastName(students, count); break;
            case 3: searchByFirstName(students, count); break;
            case 4: searchByGroup(students, count); break;
            case 5: sortById(students, count); break;
            case 6: sortByLastName(students, count); break;
            case 7: sortByFirstName(students, count); break;
            case 8: sortByGroup(students, count); break;
            case 9: writeStudentToTraceFile(students, count); break;
            case 10: writeStudentsAboveAverage(students, count); break;
            case 11: printStudents(students, count); break;
            case 0: break;
            default: printf("Неверный выбор\n");
        }
    } while (choice != 0);

    freeStudents(students, count);
    return 0;
}
