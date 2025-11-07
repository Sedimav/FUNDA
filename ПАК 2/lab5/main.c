#include "func.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

StatusCode read_input_filenames(char** filein_name, char** fileout_name) {
    if (!filein_name || !fileout_name) {
        return ERROR_NULL_POINTER;
    }
    
    printf("Введите путь к исходному файлу: ");
    size_t len1 = 0;
    ssize_t read1 = getline(filein_name, &len1, stdin);
    
    printf("Введите путь к целевому файлу: ");
    size_t len2 = 0;
    ssize_t read2 = getline(fileout_name, &len2, stdin);
    
    if (read1 == -1 || read2 == -1) {
        return ERROR_INVALID_INPUT;
    }
    
    (*filein_name)[strcspn(*filein_name, "\n")] = '\0';
    (*fileout_name)[strcspn(*fileout_name, "\n")] = '\0';
    
    return SUCCESS;
}

StatusCode validate_filenames(const char* filein_name, const char* fileout_name) {
    if (!filein_name || !fileout_name) {
        return ERROR_NULL_POINTER;
    }
    
    if (strcmp(filein_name, fileout_name) == 0) {
        return ERROR_INVALID_INPUT;
    }
    
    if (strlen(filein_name) == 0 || strlen(fileout_name) == 0) {
        return ERROR_INVALID_INPUT;
    }
    
    return SUCCESS;
}

StatusCode open_files(const char* filein_name, const char* fileout_name,
                     FILE** filein, FILE** fileout) {
    if (!filein_name || !fileout_name || !filein || !fileout) {
        return ERROR_NULL_POINTER;
    }
    
    *filein = fopen(filein_name, "r");
    if (!*filein) {
        return ERROR_INVALID_INPUT;
    }
    
    *fileout = fopen(fileout_name, "w");
    if (!*fileout) {
        fclose(*filein);
        return ERROR_INVALID_INPUT;
    }
    
    return SUCCESS;
}

StatusCode process_line(const char* line, FILE* output) {
    if (!line || !output) {
        return ERROR_NULL_POINTER;
    }
    
    size_t len = strlen(line);
    
    if (len == 0) {
        if (fputc('\n', output) == EOF) {
            return ERROR_INVALID_INPUT;
        }
        return SUCCESS;
    }
    
    int start = 0;
    while (start < (int)len && isspace((unsigned char)line[start])) {
        start++;
    }
    
    if (start >= (int)len) {
        if (fputc('\n', output) == EOF) {
            return ERROR_INVALID_INPUT;
        }
        return SUCCESS;
    }
    
    const char* trimmed = line + start;
    size_t trimmed_len = strlen(trimmed);
    
    if (!is_readable_char(trimmed[0])) {
        return ERROR_INVALID_INPUT;
    }
    
    if (trimmed_len <= 80) {
        if (fprintf(output, "%s\n", trimmed) < 0) {
            return ERROR_INVALID_INPUT;
        }
        return SUCCESS;
    }
    
    char* work_buf = malloc(trimmed_len + 1);
    if (!work_buf) {
        return ERROR_MEMORY_ALLOCATION;
    }
    strcpy(work_buf, trimmed);
    
    StatusCode status = SUCCESS;
    
    while (strlen(work_buf) > 0 && status == SUCCESS) {
        char* current_line = NULL;
        char remaining[4096] = {0};
        
        status = obrez(work_buf, &current_line, remaining);
        if (status != SUCCESS) {
            break;
        }
        
        if (strlen(current_line) > 0) {
            int first_char_pos = 0;
            while (current_line[first_char_pos] && isspace((unsigned char)current_line[first_char_pos])) {
                first_char_pos++;
            }
            
            if (current_line[first_char_pos] && is_readable_char(current_line[first_char_pos])) {
                status = add_probel(&current_line, 80);
                if (status == SUCCESS) {
                    if (fprintf(output, "%s\n", current_line) < 0) {
                        status = ERROR_INVALID_INPUT;
                    }
                }
            } else {
                status = ERROR_INVALID_INPUT;
            }
        }
        
        free(current_line);
        
        strcpy(work_buf, remaining);
    }
    
    free(work_buf);
    return status;
}

int main(void) {
    char* filein_name = NULL;
    char* fileout_name = NULL;
    FILE* filein = NULL;
    FILE* fileout = NULL;
    char* buffer = NULL;
    size_t buffer_size = 0;
    StatusCode status = SUCCESS;
    
    printf("=== Форматирование текста по 80 символов ===\n");
    
    status = read_input_filenames(&filein_name, &fileout_name);
    if (status != SUCCESS) {
        fprintf(stderr, "Ошибка: невозможно прочитать имена файлов\n");
        goto cleanup;
    }
    
    status = validate_filenames(filein_name, fileout_name);
    if (status != SUCCESS) {
        fprintf(stderr, "Ошибка: некорректные имена файлов\n");
        goto cleanup;
    }
    
    status = open_files(filein_name, fileout_name, &filein, &fileout);
    if (status != SUCCESS) {
        fprintf(stderr, "Ошибка: невозможно открыть файлы '%s' или '%s'\n", filein_name, fileout_name);
        goto cleanup;
    }
    
    printf("Обработка файла...\n");
    
    while (getline(&buffer, &buffer_size, filein) != -1 && status == SUCCESS) {
        buffer[strcspn(buffer, "\n")] = '\0';
        status = process_line(buffer, fileout);
    }
    
    if (status == SUCCESS) {
        printf("Форматирование завершено успешно!\n");
        printf("Результат сохранен в: %s\n", fileout_name);
    } else {
        fprintf(stderr, "Ошибка во время обработки файла\n");
    }
    
cleanup:
    if (buffer) {
        free(buffer);
    }
    if (filein) {
        fclose(filein);
    }
    if (fileout) {
        fclose(fileout);
    }
    if (filein_name) {
        free(filein_name);
    }
    if (fileout_name) {
        free(fileout_name);
    }
    
    return (status == SUCCESS) ? 0 : 1;
}
