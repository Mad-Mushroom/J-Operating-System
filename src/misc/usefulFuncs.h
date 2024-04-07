#pragma once
#include "../Kernel.h"

bool strcmp(char arr[], const char* ch){
    while (*arr && *ch) {
        if (*arr != *ch) {
            return false;
        }
        arr++;
        ch++;
    }
    return (*arr == '\0' && *ch == '\0');
}

int strlength(const char* str){
    int length = 0;
    while (*str) {
        length++;
        *str++;
    }
    return length;
}

void strcat2(char* destination, const char* source){
    while (*destination != '\0') {
        destination++;
    }
    while (*source != '\0') {
        *destination = *source;
        destination++;
        source++;
    }
    *destination = '\0';
}

int stringToInt(const char* str) {
    int result = 0;
    int sign = 1;
    int i = 0;

    if (str[0] == '-') {
        sign = -1;
        i = 1;
    }

    for (; str[i] != '\0'; ++i) {
        if (str[i] >= '0' && str[i] <= '9') {
            result = result * 10 + (str[i] - '0');
        } else {
            break;
        }
    }

    result *= sign;
    return result;
}

/*const char* strcat(const char* str1, const char* str2) {
    int len1 = 0;
    while (str1[len1] != '\0') {
        len1++;
    }
    int len2 = 0;
    while (str2[len2] != '\0') {
        len2++;
    }
    
    char* result = new char[len1 + len2 + 1];
    
    for (int i = 0; i < len1; i++) {
        result[i] = str1[i];
    }
    
    for (int i = 0; i < len2; i++) {
        result[len1 + i] = str2[i];
    }

    result[len1 + len2] = '\0';
    
    return result;
}*/