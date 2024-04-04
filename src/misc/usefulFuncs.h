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