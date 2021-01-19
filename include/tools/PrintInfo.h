#pragma once

#include <stdio.h>
#include <stdlib.h>

#define GRAMMER_ERROR(str)   \
        printf("[Error] line %d: %s\n", (ptoken->lineno), (str));  \
        exit(0);

#define PRINT_TOKEN_INFO(str) \
        printf("ptoken->lineno: %-4d ptoken->value: %-15s info: %-15s\n", \
               ptoken->lineno, ptoken->value, str);

    
