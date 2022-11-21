#include "s21_cat.h"

void init_flags(flag *f) {
    f->b_number_nonblank = 0;
    f->n_number = 0;
    f->s_squeeze_blank = 0;
    f->e_endstr = 0;
    f->t_tabuleshen = 0;
    f->v = 0;
    f->files = NULL;
    f->count = 0;
}

int is_flag(char *str) {
    return ((!strcmp(str, "-b")) || (!strcmp(str, "-n")) || (!strcmp(str, "-s")) || (!strcmp(str, "-E")) 
    || (!strcmp(str, "-e")) || (!strcmp(str, "-T")) || (!strcmp(str, "-t")) || (!strcmp(str, "-v"))
    || (!strcmp(str, "--number-nonblank")) || (!strcmp(str, "--number")) || (!strcmp(str, "--squeeze-blank")));
}

void scanf_flags (int argc, char **argv, flag *flags) {
    for (int i = 1; i < argc; i++) {
        if ((!strcmp(argv[i], "-b")) || (!strcmp(argv[i], "--number-nonblank")))
            flags->b_number_nonblank = 1;
        else if (!strcmp(argv[i], "-n") || (!strcmp(argv[i], "--number")))
            flags->n_number = 1;
        else if (!strcmp(argv[i], "-s") || (!strcmp(argv[i], "--squeeze-blank")))
            flags->s_squeeze_blank = 1;
        else if (!strcmp(argv[i], "-E")) {
            flags->e_endstr = 1;
            flags->v = 1; }
        else if (!strcmp(argv[i], "-e"))
            flags->e_endstr = 1;
        else if (!strcmp(argv[i], "-T")) {
            flags->t_tabuleshen = 1;
            flags->v = 1; }
        else if (!strcmp(argv[i], "-t")) 
            flags->t_tabuleshen = 1;
        else if (!strcmp(argv[i], "-v"))
            flags->v = 1;
        else flags->count++;
    }
    flags->files = malloc(sizeof(char *) * flags->count);
    flags->count = 0;
    for (int j = 1; j < argc; j++) {
        if (!is_flag(argv[j])) {
            flags->files[flags->count] = malloc(sizeof(char) * (strlen(argv[j]) + 1));
            strcpy(flags->files[flags->count], argv[j]);
            flags->count++;
        }
    }
    if (flags->t_tabuleshen == 1 && flags->v == 0)
        flags->t_tabuleshen = 0;
    if (flags->e_endstr == 1 && flags->v == 0)
        flags->e_endstr = 0;
}

void cat (flag *flags) {
    FILE *file;
    for (int i = 0; i < flags->count; i++) {
        int charecter = 0, line_count = 1;
        file = fopen(flags->files[i], "r");
        if (file == NULL)
            continue;
        char prev_char = 0;
        while (charecter != EOF) {
            prev_char = charecter != 0 ? charecter : 0;
            printf("%c", charecter);
            // ФЛАГ -n
            if (flags->n_number && (charecter == 0 || charecter == '\n')) {
                printf("%d  ", line_count);
                line_count++;
            }
            charecter = fgetc(file);
            // ФЛАГ -b
            if (flags->b_number_nonblank && (prev_char == 0 || prev_char == '\n')) {
                if (charecter != '\n') {
                    printf("%d  ", line_count);
                    line_count++;
                }
            }
            // ФЛАГ -e
            if (flags->e_endstr && charecter == '\n')
                printf("$");
            // ФЛАГ -t (Нужно проверить как это работает на маке и поправить)
            if (flags->t_tabuleshen && charecter == ' ') {
                charecter = 0;
                printf("^I");
            }
            // ФЛАГ -s
            if (flags->s_squeeze_blank && (prev_char == 0 || prev_char == '\n')) {
                if (charecter == '\n')
                    charecter = 0;
                if (prev_char != 0) 
                    printf("\n");
            }
        }
        fclose(file);
    }
}

void delete_flag (flag *flags) {
    for (int i = 0; i < flags->count; i++) {
        free(flags->files[i]);
    }
    free(flags->files);
}

int main (int argc, char **argv) {
    flag flags;
    if (argc > 1) {
        init_flags (&flags);
        scanf_flags(argc, argv, &flags);
        cat(&flags);
        //вывод работают ли флаги
        printf("\nb %d n %d s %d e %d t %d v %d", flags.b_number_nonblank, flags.n_number, 
        flags.s_squeeze_blank, flags.e_endstr, flags.t_tabuleshen, flags.v);
        if (flags.files) {
            int i = 0;
            while (i < flags.count && flags.files[i]) {
                printf("\n%s\n", flags.files[i]);
                i++;
            }
        }
        //
        delete_flag(&flags);
    }
    return 0;
}
