#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


typedef struct flg {
    int b_number_nonblank, n_number, s__squeeze_blank, e_endstr, t_tabuleshen, v;
    char **files;
} flag;

int is_flag(char *str){
    return ((!strcmp(str, "-b")) || (!strcmp(str, "-n")) || (!strcmp(str, "-s")) || (!strcmp(str, "-E")) 
    || (!strcmp(str, "-e")) || (!strcmp(str, "-T")) || (!strcmp(str, "-t")));
}

int main (int argc, char **argv) {
    flag flags;
    int count = 0;
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (!strcmp(argv[i], "-b"))
                flags.b_number_nonblank = 1;
            else if (!strcmp(argv[i], "-n"))
                flags.n_number = 1;
            else if (!strcmp(argv[i], "-s"))
                flags.s__squeeze_blank = 1;
            else if (!strcmp(argv[i], "-E")) {
                flags.e_endstr = 1;
                flags.v = 1; }
            else if (!strcmp(argv[i], "-e"))
                flags.e_endstr = 1;
            else if (!strcmp(argv[i], "-T")) {
                flags.t_tabuleshen = 1;
                flags.v = 1; }
            else if (!strcmp(argv[i], "-t")) {
                flags.t_tabuleshen = 1;
                flags.v = 1; }
            else count++;
        }

        flags.files = malloc(sizeof(char *) * (count + 1));
        flags.files[count] = '\0';
        count = 0;
        for (int j = 1; j < argc; j++) {
            if (!is_flag(argv[j])) {
                flags.files[count] = malloc(sizeof(char) * (strlen(argv[j]) + 1));
                strcpy(flags.files[count], argv[j]);
                count++;
            }
        }
    }
    
    return 0;
}

