#include "func.h"
#include <stddef.h>
#include <string.h>

void *my_memchr(const void *str, int c, size_t n) {
    unsigned char C = (unsigned char)c;
    const unsigned char *sstr = (const unsigned char *)str;
    
    for (size_t i = 0; i < n; i++) {
        if (sstr[i] == C) {
            return (void *)(sstr + i);
        }
    }
    return NULL;
}

int my_memcmp(const void *str1, const void *str2, size_t n) {
    const unsigned char *sstr1 = (const unsigned char *)str1;
    const unsigned char *sstr2 = (const unsigned char *)str2;
    
    for (size_t i = 0; i < n; i++) {
        if (sstr1[i] != sstr2[i]) {
            return sstr1[i] - sstr2[i];
        }
    }
    return 0;
}

void *my_memcpy(void *dest, const void *src, size_t n) {
    unsigned char *sstr1 = (unsigned char *)dest;
    const unsigned char *sstr2 = (const unsigned char *)src;

    if (sstr1 > sstr2 && sstr1 < sstr2 + n) {
        for (int i = n - 1; i >= 0; i--) {
            sstr1[i] = sstr2[i];
        }
    } else {
        for (size_t i = 0; i < n; i++) {
            sstr1[i] = sstr2[i];
        }
    }
    return dest;
}

void *my_memset(void *str, int c, size_t n) {
    unsigned char C = (unsigned char)c;
    unsigned char *sstr = (unsigned char *)str;
    
    for (size_t i = 0; i < n; i++) {
        sstr[i] = C;
    }
    return str;
}

char *my_strncat(char *dest, const char *src, size_t n) {
    size_t len1 = my_strlen(dest);
    size_t i;
    
    for (i = 0; i < n && src[i] != '\0'; i++) {
        dest[len1 + i] = src[i];
    }
    dest[len1 + i] = '\0';
    
    return dest;
}

char *my_strchr(const char *str, int c) {
    unsigned char C = (unsigned char)c;
    
    for (size_t i = 0; ; i++) {
        if (str[i] == C) {
            return (char *)(str + i);
        }
        if (str[i] == '\0') {
            break;
        }
    }
    return NULL;
}

int my_strncmp(const char *str1, const char *str2, size_t n) {
    for (size_t i = 0; i < n; i++) {
        if (str1[i] != str2[i]) {
            return (unsigned char)str1[i] - (unsigned char)str2[i];
        }
        if (str1[i] == '\0') {
            return 0;
        }
    }
    return 0;
}

char *my_strncpy(char *dest, const char *src, size_t n) {
    size_t i;
    
    for (i = 0; i < n && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    for (; i < n; i++) {
        dest[i] = '\0';
    }
    
    return dest;
}

size_t my_strcspn(const char *str1, const char *str2) {
    for (size_t i = 0; str1[i] != '\0'; i++) {
        for (size_t j = 0; str2[j] != '\0'; j++) {
            if (str1[i] == str2[j]) {
                return i;
            }
        }
    }
    return my_strlen(str1);
}

size_t my_strlen(const char *str) {
    size_t i = 0;
    while (str[i] != '\0') {
        ++i;
    }
    return i;
}

char *my_strpbrk(const char *str1, const char *str2) {
    for (size_t i = 0; str1[i] != '\0'; i++) {
        for (size_t j = 0; str2[j] != '\0'; j++) {
            if (str1[i] == str2[j]) {
                return (char *)(str1 + i);
            }
        }
    }
    return NULL;
}

char *my_strrchr(const char *str, int c) {
    unsigned char C = (unsigned char)c;
    const char *last = NULL;
    
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] == C) {
            last = str + i;
        }
    }
    
    return (char *)last;
}

char *my_strstr(const char *haystack, const char *needle) {
    if (needle[0] == '\0') {
        return (char *)haystack;
    }
    
    size_t needle_len = my_strlen(needle);
    size_t haystack_len = my_strlen(haystack);
    
    if (needle_len > haystack_len) {
        return NULL;
    }
    
    for (size_t i = 0; i <= haystack_len - needle_len; i++) {
        size_t j;
        for (j = 0; j < needle_len; j++) {
            if (haystack[i + j] != needle[j]) {
                break;
            }
        }
        if (j == needle_len) {
            return (char *)(haystack + i);
        }
    }
    
    return NULL;
}

char *my_strtok(char *str, const char *delim) {
    static char *strtok_save = NULL;
    char *token_start;
    char *current;
    
    if (str != NULL) {
        strtok_save = str;
    }
    
    if (strtok_save == NULL || *strtok_save == '\0') {
        return NULL;
    }
    
    token_start = strtok_save;
    while (*token_start != '\0' && my_strchr(delim, *token_start) != NULL) {
        token_start++;
    }
    
    if (*token_start == '\0') {
        strtok_save = NULL;
        return NULL;
    }
    
    current = token_start;
    while (*current != '\0' && my_strchr(delim, *current) == NULL) {
        current++;
    }
    
    if (*current != '\0') {
        *current = '\0';
        strtok_save = current + 1;
    } else {
        strtok_save = NULL;
    }
    
    return token_start;
}

char *my_strerror(int errnum) {
    static const char *error_messages[] = {
        "Success",
        "Operation not permitted",
        "No such file or directory",
        "No such process",
        "Interrupted system call",
        "I/O error",
        "No such device or address",
        "Argument list too long",
        "Exec format error",
        "Bad file number"
    };
    
    static const int error_count = sizeof(error_messages) / sizeof(error_messages[0]);
    
    if (errnum >= 0 && errnum < error_count) {
        return (char *)error_messages[errnum];
    } else {
        return (char *)"Неизвестная ошибка";
    }
}
