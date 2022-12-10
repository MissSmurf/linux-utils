#ifndef S21_GREP_H_
#define S21_GREP_H_
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct flg {
    int e_patterns, 
        c_count,
        count;
    char **files;
} flag;

#endif