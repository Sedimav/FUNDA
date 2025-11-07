#include "func.h"
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 256

void print_menu() {
    printf("\n~~~ String Functions ~~~\n");
    printf("1.  strlen   - Длина строки\n");
    printf("2.  strncpy  - Копирование строки\n");
    printf("3.  strncat  - Конкатенация строк\n");
    printf("4.  strncmp  - Сравнение строк\n");
    printf("5.  strchr   - Поиск символа\n");
    printf("6.  strstr   - Поиск подстроки\n");
    printf("7.  strtok   - Разбиение на токены\n");
    printf("8.  memset   - Заполнение памяти\n");
    printf("9.  memcpy   - Копирование памяти\n");
    printf("10. memchr   - Поиск символа в памяти\n");
    printf("11. memcmp   - Сравнение памяти\n");
    printf("12. strcspn  - Поиск любого из разделителей\n");
    printf("13. strpbrk  - Поиск любого символа из набора\n");
    printf("14. strrchr  - Поиск последнего вхождения символа\n");
    printf("15. strerror - Текст ошибки\n");
    printf("0. Выход\n");
    printf("Выберите функцию: ");
}

void demo_strlen() {
    char str[BUFFER_SIZE];
    printf("Введите строку: ");
    fgets(str, BUFFER_SIZE, stdin);
    str[strcspn(str, "\n")] = '\0';
    
    printf("Длина строки '%s': %zu\n", str, my_strlen(str));
}

void demo_strncpy() {
    char src[BUFFER_SIZE];
    char dest[BUFFER_SIZE];
    
    printf("Введите исходную строку: ");
    fgets(src, BUFFER_SIZE, stdin);
    src[strcspn(src, "\n")] = '\0';
    
    printf("Сколько символов копировать? ");
    int n;
    scanf("%d", &n);
    getchar();
    
    my_strncpy(dest, src, n);
    dest[n] = '\0';
    printf("Результат: %s\n", dest);
}

void demo_strncat() {
    char dest[BUFFER_SIZE] = "";
    char src[BUFFER_SIZE];
    
    printf("Введите первую строку (базу): ");
    fgets(dest, BUFFER_SIZE, stdin);
    dest[strcspn(dest, "\n")] = '\0';
    
    printf("Введите строку для добавления: ");
    fgets(src, BUFFER_SIZE, stdin);
    src[strcspn(src, "\n")] = '\0';
    
    printf("Сколько символов добавить? ");
    int n;
    scanf("%d", &n);
    getchar();
    
    my_strncat(dest, src, n);
    printf("Результат: %s\n", dest);
}

void demo_strncmp() {
    char str1[BUFFER_SIZE], str2[BUFFER_SIZE];
    
    printf("Введите первую строку: ");
    fgets(str1, BUFFER_SIZE, stdin);
    str1[strcspn(str1, "\n")] = '\0';
    
    printf("Введите вторую строку: ");
    fgets(str2, BUFFER_SIZE, stdin);
    str2[strcspn(str2, "\n")] = '\0';
    
    printf("Сколько символов сравнивать? ");
    int n;
    scanf("%d", &n);
    getchar();
    
    int result = my_strncmp(str1, str2, n);
    printf("Результат сравнения: %d\n", result);
    printf("(0 - равны, >0 - первая больше, <0 - вторая больше)\n");
}

void demo_strchr() {
    char str[BUFFER_SIZE];
    char ch;
    
    printf("Введите строку: ");
    fgets(str, BUFFER_SIZE, stdin);
    str[strcspn(str, "\n")] = '\0';
    
    printf("Введите символ для поиска: ");
    scanf("%c", &ch);
    getchar();
    
    char *result = my_strchr(str, ch);
    if (result) {
        printf("Символ '%c' найден на позиции: %ld\n", ch, result - str);
    } else {
        printf("Символ '%c' не найден\n", ch);
    }
}

void demo_strstr() {
    char haystack[BUFFER_SIZE], needle[BUFFER_SIZE];
    
    printf("Введите строку для поиска: ");
    fgets(haystack, BUFFER_SIZE, stdin);
    haystack[strcspn(haystack, "\n")] = '\0';
    
    printf("Введите подстроку: ");
    fgets(needle, BUFFER_SIZE, stdin);
    needle[strcspn(needle, "\n")] = '\0';
    
    char *result = my_strstr(haystack, needle);
    if (result) {
        printf("Подстрока '%s' найдена на позиции: %ld\n", needle, result - haystack);
    } else {
        printf("Подстрока '%s' не найдена\n", needle);
    }
}

void demo_strtok() {
    char str[BUFFER_SIZE];
    char delim[BUFFER_SIZE];
    
    printf("Введите строку для разбиения: ");
    fgets(str, BUFFER_SIZE, stdin);
    str[strcspn(str, "\n")] = '\0';
    
    printf("Введите разделители: ");
    fgets(delim, BUFFER_SIZE, stdin);
    delim[strcspn(delim, "\n")] = '\0';
    
    printf("Токены:\n");
    char *token = my_strtok(str, delim);
    int count = 1;
    
    while (token) {
        printf("%d: '%s'\n", count++, token);
        token = my_strtok(NULL, delim);
    }
}

void demo_memset() {
    char str[BUFFER_SIZE];
    char ch;
    int n;
    
    printf("Введите строку: ");
    fgets(str, BUFFER_SIZE, stdin);
    str[strcspn(str, "\n")] = '\0';
    
    printf("Введите символ для заполнения: ");
    scanf("%c", &ch);
    getchar();
    
    printf("Сколько символов заполнить? ");
    scanf("%d", &n);
    getchar();
    
    if (n > BUFFER_SIZE - 1) n = BUFFER_SIZE - 1;
    
    my_memset(str, ch, n);
    printf("Результат: %s\n", str);
}

void demo_memcpy() {
    char src[BUFFER_SIZE];
    char dest[BUFFER_SIZE] = "";
    
    printf("Введите исходную строку: ");
    fgets(src, BUFFER_SIZE, stdin);
    src[strcspn(src, "\n")] = '\0';
    
    printf("Сколько символов копировать? ");
    int n;
    scanf("%d", &n);
    getchar();
    
    if (n > BUFFER_SIZE - 1) n = BUFFER_SIZE - 1;
    
    my_memcpy(dest, src, n);
    dest[n] = '\0';
    printf("Результат: %s\n", dest);
}

void demo_memchr() {
    char str[BUFFER_SIZE];
    char ch;
    int n;
    
    printf("Введите строку: ");
    fgets(str, BUFFER_SIZE, stdin);
    str[strcspn(str, "\n")] = '\0';
    
    printf("Введите символ для поиска: ");
    scanf("%c", &ch);
    getchar();
    
    printf("Сколько символов проверять? ");
    scanf("%d", &n);
    getchar();
    
    if (n > BUFFER_SIZE - 1) n = BUFFER_SIZE - 1;
    
    void *result = my_memchr(str, ch, n);
    if (result) {
        printf("Символ '%c' найден на позиции: %ld\n", ch, (char*)result - str);
    } else {
        printf("Символ '%c' не найден в первых %d символах\n", ch, n);
    }
}

void demo_memcmp() {
    char str1[BUFFER_SIZE], str2[BUFFER_SIZE];
    int n;
    
    printf("Введите первую строку: ");
    fgets(str1, BUFFER_SIZE, stdin);
    str1[strcspn(str1, "\n")] = '\0';
    
    printf("Введите вторую строку: ");
    fgets(str2, BUFFER_SIZE, stdin);
    str2[strcspn(str2, "\n")] = '\0';
    
    printf("Сколько символов сравнивать? ");
    scanf("%d", &n);
    getchar();
    
    if (n > BUFFER_SIZE - 1) n = BUFFER_SIZE - 1;
    
    int result = my_memcmp(str1, str2, n);
    printf("Результат сравнения: %d\n", result);
    printf("(0 - равны, >0 - первая больше, <0 - вторая больше)\n");
}

void demo_strcspn() {
    char str[BUFFER_SIZE];
    char reject[BUFFER_SIZE];
    
    printf("Введите строку: ");
    fgets(str, BUFFER_SIZE, stdin);
    str[strcspn(str, "\n")] = '\0';
    
    printf("Введите символы для поиска: ");
    fgets(reject, BUFFER_SIZE, stdin);
    reject[strcspn(reject, "\n")] = '\0';
    
    size_t pos = my_strcspn(str, reject);
    printf("Позиция первого найденного символа: %zu\n", pos);
    if (pos < my_strlen(str)) {
        printf("Найден символ: '%c'\n", str[pos]);
    } else {
        printf("Ни один из символов не найден\n");
    }
}

void demo_strpbrk() {
    char str[BUFFER_SIZE];
    char accept[BUFFER_SIZE];
    
    printf("Введите строку: ");
    fgets(str, BUFFER_SIZE, stdin);
    str[strcspn(str, "\n")] = '\0';
    
    printf("Введите символы для поиска: ");
    fgets(accept, BUFFER_SIZE, stdin);
    accept[strcspn(accept, "\n")] = '\0';
    
    char *result = my_strpbrk(str, accept);
    if (result) {
        printf("Первый найденный символ '%c' на позиции: %ld\n", *result, result - str);
    } else {
        printf("Ни один из символов не найден\n");
    }
}

void demo_strrchr() {
    char str[BUFFER_SIZE];
    char ch;
    
    printf("Введите строку: ");
    fgets(str, BUFFER_SIZE, stdin);
    str[strcspn(str, "\n")] = '\0';
    
    printf("Введите символ для поиска: ");
    scanf("%c", &ch);
    getchar();
    
    char *result = my_strrchr(str, ch);
    if (result) {
        printf("Последнее вхождение символа '%c' на позиции: %ld\n", ch, result - str);
    } else {
        printf("Символ '%c' не найден\n", ch);
    }
}

void demo_strerror() {
    int errnum;
    
    printf("Введите код ошибки (0-9 для теста): ");
    scanf("%d", &errnum);
    getchar();
    
    printf("Ошибка %d: %s\n", errnum, my_strerror(errnum));
}
