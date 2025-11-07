#include <stdio.h>
#include <string.h>
#include "func.h"

int main() {
    int choice;
    
    do {
        print_menu();
        scanf("%d", &choice);
        getchar();
        
        switch (choice) {
            case 1: demo_strlen(); break;
            case 2: demo_strncpy(); break;
            case 3: demo_strncat(); break;
            case 4: demo_strncmp(); break;
            case 5: demo_strchr(); break;
            case 6: demo_strstr(); break;
            case 7: demo_strtok(); break;
            case 8: demo_memset(); break;
            case 9: demo_memcpy(); break;
            case 10: demo_memchr(); break;
            case 11: demo_memcmp(); break;
            case 12: demo_strcspn(); break;
            case 13: demo_strpbrk(); break;
            case 14: demo_strrchr(); break;
            case 15: demo_strerror(); break;
            case 0: printf("Выход...\n"); break;
            default: printf("Неверный выбор!\n");
        }
    } while (choice != 0);
    
    return 0;
}