#ifndef S21_CAT_H_
#define S21_CAT_H_
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct flg {
    int b_number_nonblank, 
        n_number, 
        s_squeeze_blank, 
        e_endstr, 
        t_tabuleshen, 
        v, 
        count;
    char **files;
} flag;

int is_flag(char *str);
void scanf_flags (int argc, char **argv, flag *flags);
void cat (flag *flags);
void delete_flag (flag *flags);
int main (int argc, char **argv);

#endif