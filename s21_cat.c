#include "s21_cat.h"
//Дописать флаг -v

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

void scanf_flags(int argc, char **argv, flag *flags) {
    for (int i = 1; i < argc; i++) {
        if ((!strcmp(argv[i], "-b")) || (!strcmp(argv[i], "--number-nonblank")))
            flags->b_number_nonblank = 1;
        else if (!strcmp(argv[i], "-n") || (!strcmp(argv[i], "--number")))
            flags->n_number = 1;
        else if (!strcmp(argv[i], "-s") || !strcmp(argv[i], "--squeeze-blank"))
            flags->s_squeeze_blank = 1;
        else if (!strcmp(argv[i], "-E") || !strcmp(argv[i], "-e"))
            flags->e_endstr = 1;
        else if (!strcmp(argv[i], "-T") || !strcmp(argv[i], "-t"))
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
        if (flags->n_number == 1 && flags->b_number_nonblank == 1)
            flags->n_number = 0;
    }
}

void cat(flag *flags) {
    FILE *file;
    for (int i = 0; i < flags->count; i++) {
        int charecter = 0, line_count = 1;
        file = fopen(flags->files[i], "r");
        if (file == NULL)
            continue;
        char prev_char = 0;
        int temp = 0;
        while ((charecter = fgetc(file)) != EOF) {
            // ФЛАГ -n
            if (flags->n_number && (prev_char == 0 || prev_char == '\n')) {
                printf("%6d  ", line_count);
                line_count++;
            }
            // ФЛАГ -b
            if (flags->b_number_nonblank && (prev_char == 0 || prev_char == '\n')) {
                if (charecter != '\n') {
                    printf("%6d  ", line_count);
                    line_count++;
                }
            }
            // ФЛАГ -e
            if (flags->e_endstr && charecter == '\n')
                printf("$");
            // ФЛАГ -t
            if (flags->t_tabuleshen && charecter == '\t') {
                charecter = 0;
                printf("^I");
            }
            // ФЛАГ -s
            if (flags->s_squeeze_blank && (prev_char == 0 || prev_char == '\n')) {
                if (charecter == '\n')
                    charecter = 0;
                else if (temp != 0 && prev_char != '\n')
                    printf("\n");
            }
            temp++;
            //ФЛАГ -v
            if (flags->v && (prev_char == 0 || prev_char == '\n')) {
                flag_v(charecter);
            }
            prev_char = charecter != 0 ? charecter : 0;
            printf("%c", charecter);
        }
        fclose(file);
    }
}

int flag_v(int charecter) {
    int decrements[] = {-100, -76, -74, -72, -70, -68, -66, -64, 60, -56, -54, -52, -50, -48, -46, -44};
    int decimal_original = charecter;
    if (decimal_original < 0) 
        decimal_original = -decimal_original;
    int decimal_original_copy = decimal_original;

    int octal_array_form[100];
    int octal_regular = 0;
    int i = 1;
    // octal array form
    while (decimal_original_copy > 0) {
        octal_array_form[i] = decimal_original_copy % 8;
        decimal_original_copy /= 8;

        i++;
    }
    // octal regular form
    for (int j = i - 1; j > 0; j--) {
        octal_regular = octal_regular * 10 + octal_array_form[j];
    }

    int new_octal_regular;
    new_octal_regular = octal_regular + decrements[128 - decimal_original];
    int new_decimal = 0;
    i = 0;

    while (new_octal_regular > 0) {
        new_decimal = new_decimal + (new_octal_regular % 10) * pow(8, i++);
        new_octal_regular /= 10;
    }
    char* returner = (char *)malloc(35 * sizeof(char));
    sprintf(returner, "M-^%c", new_decimal);

    return *returner;
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
        /*
        printf("\nb %d n %d s %d e %d t %d v %d", flags.b_number_nonblank, flags.n_number, 
        flags.s_squeeze_blank, flags.e_endstr, flags.t_tabuleshen, flags.v);
        if (flags.files) {
            int i = 0;
            while (i < flags.count && flags.files[i]) {
                printf("\n%s\n", flags.files[i]);
                i++;
            }
        }
        *///
        delete_flag(&flags);
    }
    return 0;
}
