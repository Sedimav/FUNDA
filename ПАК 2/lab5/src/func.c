#include "func.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int is_readable_char(char c) {
    return isprint((unsigned char)c) && !isspace((unsigned char)c);
}

// Остальные функции остаются без изменений...
StatusCode obrez(const char* input, char** result, char* remaining) {
    if (!input || !result || !remaining) {
        return ERROR_NULL_POINTER;
    }
    
    size_t len = strlen(input);
    
    if (len == 0) {
        *result = malloc(1);
        if (!*result) return ERROR_MEMORY_ALLOCATION;
        (*result)[0] = '\0';
        remaining[0] = '\0';
        return SUCCESS;
    }
    
    if (len <= 80) {
        *result = malloc(len + 1);
        if (!*result) return ERROR_MEMORY_ALLOCATION;
        strcpy(*result, input);
        remaining[0] = '\0';
        return SUCCESS;
    }
    
    size_t break_pos = 79;
    
    if (input[break_pos + 1] == ' ' && is_readable_char(input[break_pos])) {
        break_pos++;
    } else {
        while (break_pos > 0 && input[break_pos] != ' ') {
            break_pos--;
        }
        
        if (break_pos == 0) {
            break_pos = 79;
            while (break_pos < len && input[break_pos] != ' ') {
                break_pos++;
            }
        }
    }
    
    *result = malloc(break_pos + 1);
    if (!*result) return ERROR_MEMORY_ALLOCATION;
    
    strncpy(*result, input, break_pos);
    (*result)[break_pos] = '\0';
    
    size_t remaining_len = len - break_pos;
    size_t copy_start = break_pos;
    
    while (copy_start < len && isspace((unsigned char)input[copy_start])) {
        copy_start++;
    }
    
    if (copy_start >= len) {
        remaining[0] = '\0';
    } else {
        strncpy(remaining, input + copy_start, remaining_len);
        remaining[remaining_len - (copy_start - break_pos)] = '\0';
    }
    
    return SUCCESS;
}

StatusCode add_probel(char** string, size_t target_length) {
    if (!string || !*string) {
        return ERROR_NULL_POINTER;
    }
    
    char* input = *string;
    size_t current_length = strlen(input);
    
    if (current_length >= target_length) {
        return SUCCESS;
    }
    
    size_t space_count = 0;
    size_t word_count = 0;
    int in_word = 0;
    
    for (size_t i = 0; i < current_length; i++) {
        if (isspace((unsigned char)input[i])) {
            if (in_word) {
                in_word = 0;
            }
        } else {
            if (!in_word) {
                word_count++;
                in_word = 1;
            }
        }
    }
    
    for (size_t i = 0; i < current_length; i++) {
        if (isspace((unsigned char)input[i])) {
            space_count++;
        }
    }
    
    if (word_count <= 1 || space_count == 0) {
        char* new_str = malloc(target_length + 1);
        if (!new_str) return ERROR_MEMORY_ALLOCATION;
        
        strcpy(new_str, input);
        for (size_t i = current_length; i < target_length; i++) {
            new_str[i] = ' ';
        }
        new_str[target_length] = '\0';
        
        free(input);
        *string = new_str;
        return SUCCESS;
    }
    
    size_t spaces_to_add = target_length - current_length;
    size_t gaps_count = word_count - 1;
    
    char* new_str = malloc(target_length + 1);
    if (!new_str) return ERROR_MEMORY_ALLOCATION;
    
    size_t new_pos = 0;
    size_t spaces_added = 0;
    size_t gaps_processed = 0;
    
    for (size_t i = 0; i < current_length; i++) {
        if (!isspace((unsigned char)input[i])) {
            new_str[new_pos++] = input[i];
        } else {
            if (new_pos > 0 && !isspace((unsigned char)new_str[new_pos - 1])) {
                new_str[new_pos++] = ' ';
                spaces_added++;
                
                size_t extra_spaces = spaces_to_add / gaps_count;
                if (gaps_processed < (spaces_to_add % gaps_count)) {
                    extra_spaces++;
                }
                
                for (size_t j = 0; j < extra_spaces; j++) {
                    new_str[new_pos++] = ' ';
                    spaces_added++;
                }
                
                gaps_processed++;
            }
            
            while (i < current_length && isspace((unsigned char)input[i])) {
                i++;
            }
            i--;
        }
    }
    
    new_str[new_pos] = '\0';
    free(input);
    *string = new_str;
    
    return SUCCESS;
}
