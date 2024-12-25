#include <ctype.h>
#include <stdio.h>
#include<string.h>
#include <stdbool.h>
#include <stdlib.h>

#define LINECOUNT 100
#define LINESIZE 80
#define OUT_FILE "out.txt"

void read_string(char *string);
FILE* open_file(const char *file_name, const char *mode);
bool file_to_array(FILE *file, char *array[],int *line_count);
void array_to_upper(char *array[], int line_count);
bool array_to_file(FILE *file, char *array[], int line_count);


int main(void) {
    char *strings[LINECOUNT] = {0};
    char file_name[LINESIZE];
    int line_count=0;

    printf("Enter the file name: ");
    read_string(file_name);

    FILE *file = open_file(file_name, "r");
    FILE *out_file = open_file(OUT_FILE, "w");

    if (file != NULL) {
        if (file_to_array(file, strings, &line_count)) {
            printf("Lines of file stored in the array. %d lines read\n", line_count);
            array_to_upper(strings, line_count);

            if (array_to_file(out_file, strings, line_count)) {
                printf("File written to %s\n", OUT_FILE);
            } else printf("Failed to write file to %s\n", OUT_FILE);

        } else {
            printf("Failed to read and process the file\n");
        }
    }

    fclose(file);
    fclose(out_file);

    for (int i = 0; i < line_count; i++) {
        free(strings[i]);
    }

    return 0;
}

void read_string(char *string) {

    if (fgets(string, LINESIZE, stdin) != NULL) {
        int len = strlen(string);
        if (string[len - 1] == '\n') {
            string[len - 1] = '\0';
        }
    }
}

FILE* open_file(const char *file_name, const char *mode) {
    FILE *file = fopen(file_name, mode);

    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", file_name);
        return NULL;
    }
    return file;
}

bool file_to_array(FILE *file, char *array[],int *line_count) {
    char line[LINESIZE];

    if (file != NULL) {
        while (!feof(file)) {
            while (fgets(line, LINESIZE, file) != NULL && *line_count < LINECOUNT) {
                array[*line_count] = strdup(line);
                if (array[*line_count] == NULL) {
                    return false;
                }
                (*line_count)++;
            }
            return true;
        }
    }
    return false;
}

void array_to_upper(char *array[], const int line_count) {
    for (int i = 0; i < line_count; ++i) {
        if (array[i] != NULL) {
            for (int j = 0; j < strlen(array[i]); j++) {
                array[i][j] = toupper(array[i][j]);
            }
        }
    }
}

bool array_to_file(FILE *file, char *array[], int line_count) {
    for (int i = 0; i < line_count; ++i) {
        if (array[i] != NULL) {
            if (fputs(array[i], file) == EOF) {
                return false;
            }
        }
    }
    return true;
}