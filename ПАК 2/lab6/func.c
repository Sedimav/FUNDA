#include "func.h"

int compareById(const void *a, const void *b) {
    const Student *sa = (const Student*)a;
    const Student *sb = (const Student*)b;
    return (sa->id > sb->id) - (sa->id < sb->id);
}

int compareByLastName(const void *a, const void *b) {
    const Student *sa = (const Student*)a;
    const Student *sb = (const Student*)b;
    return strcmp(sa->lastName, sb->lastName);
}

int compareByFirstName(const void *a, const void *b) {
    const Student *sa = (const Student*)a;
    const Student *sb = (const Student*)b;
    return strcmp(sa->firstName, sb->firstName);
}

int compareByGroup(const void *a, const void *b) {
    const Student *sa = (const Student*)a;
    const Student *sb = (const Student*)b;
    return strcmp(sa->group, sb->group);
}

Student* readStudentsFromFile(const char *filename, int *count) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Ошибка: не удалось открыть файл %s\n", filename);
        return NULL;
    }

    *count = 0;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        if (strlen(buffer) > 1) (*count)++;
    }
    
    if (*count == 0) {
        fclose(file);
        return NULL;
    }

    rewind(file);
    Student *students = malloc(*count * sizeof(Student));
    
    for (int i = 0; i < *count; i++) {
        if (!fgets(buffer, sizeof(buffer), file)) break;
        
        students[i].grades = malloc(NUM_EXAMS * sizeof(unsigned char));
        
        char *token = strtok(buffer, ",");
        if (token) students[i].id = atoi(token);
        
        token = strtok(NULL, ",");
        if (token) strncpy(students[i].firstName, token, MAX_NAME_LENGTH - 1);
        
        token = strtok(NULL, ",");
        if (token) strncpy(students[i].lastName, token, MAX_NAME_LENGTH - 1);
        
        token = strtok(NULL, ",");
        if (token) strncpy(students[i].group, token, MAX_GROUP_LENGTH - 1);
        
        for (int j = 0; j < NUM_EXAMS; j++) {
            token = strtok(NULL, ",\n");
            if (token) students[i].grades[j] = atoi(token);
        }
    }
    
    fclose(file);
    return students;
}

void freeStudents(Student *students, int count) {
    for (int i = 0; i < count; i++) {
        free(students[i].grades);
    }
    free(students);
}

void searchById(const Student *students, int count) {
    unsigned int id;
    printf("Введите ID: ");
    scanf("%u", &id);
    
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            printf("Найден: %s %s, группа %s\n", 
                   students[i].firstName, students[i].lastName, students[i].group);
            found = 1;
            break;
        }
    }
    if (!found) printf("Студент с ID %u не найден\n", id);
}

void searchByLastName(const Student *students, int count) {
    char name[MAX_NAME_LENGTH];
    printf("Введите фамилию: ");
    scanf("%s", name);
    
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].lastName, name) == 0) {
            printf("Найден: %s %s, группа %s\n", 
                   students[i].firstName, students[i].lastName, students[i].group);
            found = 1;
        }
    }
    if (!found) printf("Студенты с фамилией %s не найдены\n", name);
}

void searchByFirstName(const Student *students, int count) {
    char name[MAX_NAME_LENGTH];
    printf("Введите имя: ");
    scanf("%s", name);
    
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].firstName, name) == 0) {
            printf("Найден: %s %s, группа %s\n", 
                   students[i].firstName, students[i].lastName, students[i].group);
            found = 1;
        }
    }
    if (!found) printf("Студенты с именем %s не найдены\n", name);
}

void searchByGroup(const Student *students, int count) {
    char group[MAX_GROUP_LENGTH];
    printf("Введите группу: ");
    scanf("%s", group);
    
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].group, group) == 0) {
            printf("Найден: %s %s, группа %s\n", 
                   students[i].firstName, students[i].lastName, students[i].group);
            found = 1;
        }
    }
    if (!found) printf("Студенты группы %s не найдены\n", group);
}

void sortById(Student *students, int count) {
    qsort(students, count, sizeof(Student), compareById);
    printf("Отсортировано по ID\n");
    printStudents(students, count);
}

void sortByLastName(Student *students, int count) {
    qsort(students, count, sizeof(Student), compareByLastName);
    printf("Отсортировано по фамилии\n");
    printStudents(students, count);
}

void sortByFirstName(Student *students, int count) {
    qsort(students, count, sizeof(Student), compareByFirstName);
    printf("Отсортировано по имени\n");
    printStudents(students, count);
}

void sortByGroup(Student *students, int count) {
    qsort(students, count, sizeof(Student), compareByGroup);
    printf("Отсортировано по группе\n");
    printStudents(students, count);
}

double calculateAverage(const unsigned char *grades) {
    double sum = 0;
    for (int i = 0; i < NUM_EXAMS; i++) {
        sum += grades[i];
    }
    return sum / NUM_EXAMS;
}

double calculateOverallAverage(const Student *students, int count) {
    double total = 0;
    for (int i = 0; i < count; i++) {
        total += calculateAverage(students[i].grades);
    }
    return total / count;
}

void writeStudentToTraceFile(const Student *students, int count) {
    unsigned int id;
    char filename[100];
    
    printf("Введите ID студента: ");
    scanf("%u", &id);
    printf("Введите путь к файлу: ");
    scanf("%s", filename);
    
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Ошибка создания файла\n");
        return;
    }
    
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            double avg = calculateAverage(students[i].grades);
            fprintf(file, "ФИО: %s %s\nГруппа: %s\nСредняя оценка: %.2f\n",
                   students[i].lastName, students[i].firstName, 
                   students[i].group, avg);
            found = 1;
            break;
        }
    }
    
    fclose(file);
    if (found) printf("Данные записаны в %s\n", filename);
    else printf("Студент не найден\n");
}

void writeStudentsAboveAverage(const Student *students, int count) {
    char filename[100];
    printf("Введите путь к файлу: ");
    scanf("%s", filename);
    
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Ошибка создания файла\n");
        return;
    }
    
    double overallAvg = calculateOverallAverage(students, count);
    fprintf(file, "Общий средний балл: %.2f\n", overallAvg);
    fprintf(file, "Студенты с баллом выше среднего:\n");
    
    for (int i = 0; i < count; i++) {
        double avg = calculateAverage(students[i].grades);
        if (avg > overallAvg) {
            fprintf(file, "%s %s (%.2f)\n", 
                   students[i].lastName, students[i].firstName, avg);
        }
    }
    
    fclose(file);
    printf("Данные записаны в %s\n", filename);
}

void printStudents(const Student *students, int count) {
    printf("\nСписок студентов:\n");
    for (int i = 0; i < count; i++) {
        printf("%u: %s %s, %s\n", 
               students[i].id, students[i].firstName, 
               students[i].lastName, students[i].group);
    }
    printf("\n");
}

void printMenu() {
    printf("\nМеню:\n");
    printf("1. Поиск по ID\n");
    printf("2. Поиск по фамилии\n");
    printf("3. Поиск по имени\n");
    printf("4. Поиск по группе\n");
    printf("5. Сортировка по ID\n");
    printf("6. Сортировка по фамилии\n");
    printf("7. Сортировка по имени\n");
    printf("8. Сортировка по группе\n");
    printf("9. Запись студента в файл\n");
    printf("10. Запись студентов с баллом выше среднего\n");
    printf("11. Показать всех студентов\n");
    printf("0. Выход\n");
    printf("Выбор: ");
}
