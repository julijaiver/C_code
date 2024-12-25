#include <stdio.h>
#include<string.h>
#include <stdbool.h>

#define LINESIZE 80

void read_string(char *string);
FILE* open_file(const char *file_name);
bool file_processing(FILE *file, int *num_of_integers, int *lowest_int, int *highest_int);

int main(void) {
    char file_name[LINESIZE];
    int num_of_integers = 0, lowest_int = 0, highest_int = 0;

    printf("Enter the name of the file: ");
    read_string(file_name);

    FILE *file = open_file(file_name);

    if (file != NULL) {
        if (file_processing(file, &num_of_integers, &lowest_int, &highest_int)) {
            printf("Number of integers read: %d\nLowest integer: %d\nHighest integer: %d\n", num_of_integers, lowest_int, highest_int);
        } else printf("File could not be processed\n");
    } else printf("File could not be opened\n");

    fclose(file);

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

FILE* open_file(const char *file_name) {
    FILE *file = fopen(file_name, "r");

    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", file_name);
        return NULL;
    }
    return file;
}

bool file_processing(FILE *file, int *num_of_integers, int *lowest_int, int *highest_int) {
    char line[LINESIZE];
    int value;

    if (file != NULL) {
        while (!feof(file)) {
            while (fgets(line, LINESIZE, file) != NULL) {
                if (sscanf(line, "%d", &value) == 1) {
                    if (value < *lowest_int) {
                        *lowest_int = value;
                    }
                    else if (value > *highest_int) {
                        *highest_int = value;
                    }
                    (*num_of_integers)++;
                }
            }
            return true;
        }
    }
    return false;
}
