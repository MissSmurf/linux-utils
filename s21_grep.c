#include "s21_grep.h"

void init_flags(flag *f) {
    f->c_count = 0;
    f->files = NULL;
    f->count = 0;
}

int is_flag(char *str) {
    return (!strcmp(str, "-c"));
}

void scanf_flag(int argc, char **argv, flag *flags) {
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-c"))
            flags->c_count = 1;
        else flags->count++;
        flags->files = malloc(sizeof(char *) * flags->count);
        flags->count = 0;
    }
    for (int j = 1; j < argc; j++) {
        if (!is_flag(argv[j])) {
            flags->files[flags->count] = malloc(sizeof(char) * (strlen(argv[j]) + 1));
            strcpy(flags->files[flags->count], argv[j]);
            flags->count++;
        }
    }
}

void grep(flag *flags) {
    FILE *file1;
    FILE *file2;
    for (int i = 0; i < flags->count; i++) {
        int charecter = 0;
        file1 = fopen(flags->files[i], "r");
        if (file1 == NULL)
            continue;
        while ((charecter = fgetc(file1)) != EOF) {
            if ()
        }
        file2 = fopen(flags->files[i], "r");
        while ((charecter = fgetc(file2)) != EOF) {
            printf("%c", charecter);
        }
        fclose(file1);
        fclose(file2);
    }
}

void delete_flag(flag *flags) {
    for (int i = 0; i < flags->count; i++) {
        free(flags->files[i]);
    }
    free(flags->files);
}

int main(int argc, char **argv) {
    flag flags;
    if (argc > 1) {
        init_flags(&flags);
        scanf_flag(argc, argv, &flags);
        grep(&flags);

        if (flags.files) {
            int i = 0;
            while (i < flags.count && flags.files[i]) {
                printf("\n%s\n", flags.files[i]);
                i++;
            }
        }

        delete_flag(&flags);
    }  
    return 0;
}
