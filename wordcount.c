#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int num_of_lines(FILE *file) {
    char ch;
    int lines = 0;
    rewind(file);
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            lines++;
        }
    }
    return lines;
    //printf("%i ", lines);
}

int num_of_words(FILE *file) {
    char ch;
    int words = 0;
    int prev_char_was_space = 1;
    rewind(file);
    while ((ch = fgetc(file)) != EOF) {
        if (ch == ' ' || ch == '\n') {
            prev_char_was_space = 1;
        } else {
            if (prev_char_was_space) {
                words++;
                prev_char_was_space = 0;
            }
        }
    }
    return(words);
}

int num_of_chars(FILE *file) {
    char ch;
    int chars = 0;
    rewind(file);
    while ((ch = fgetc(file)) != EOF) {
        chars++;
    }
    return chars;
}


int total_lines = 0;

void do_something_with_a_file(FILE *file, char *fto, char option) {
    if (option == 'l') {
        printf("%i\n", num_of_lines(file));
    } else if (option == 'w') {
        printf("%i\n", num_of_words(file));
    } else if (option == 'c') {
        printf("%i\n", num_of_chars(file));
    } else if (option == 'a') {
        int nl = num_of_lines(file);
        int nw = num_of_words(file);
        int nc = num_of_chars(file);
        printf("%i %i %i %s\n", nl, nw, nc, fto);
        total_lines += num_of_lines(file);
    }
}

void checkUsage(int argc, int mode) {
    if (argc < (mode + 2)) {
        printf("Usage: ./wordcount requires an input file.\n");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
  int i;
  int start = 1;
  char option = 'a';

      // if they are passing an option
    if (strcmp(argv[1], "-l") == 0) {
        option = 'l';
    } else if (strcmp(argv[1], "-w") == 0) {
        option = 'w';
    } else if (strcmp(argv[1], "-c") == 0) {
        option = 'c';
    } else {
        start = 0;
    }

    checkUsage(argc, start);

    for (i = (start + 1); i < argc; i++) {

        char *file_to_open = argv[i];
        FILE *file = fopen(file_to_open, "r");

        if (file) {
        do_something_with_a_file(file, file_to_open, option);
        fclose(file);
        } else {
        fprintf(stderr, "%s will not open.  Skipping.\n", file_to_open);
        }

    }


    if (option == 'a') {
        printf("Total Lines = %i\n", total_lines);
    }

  return EXIT_SUCCESS;
}