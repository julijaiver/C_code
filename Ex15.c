#include <stdbool.h>
#include <stdio.h>
#include<string.h>

#define LINESIZE 80
#define NAME_SIZE 50
#define NUM_OF_ITEMS 40

typedef struct menu_item_ {
    char name[NAME_SIZE];
    double price;
} menu_item;

void read_string(char *string);
FILE* open_file(const char *file_name, const char *mode);
bool file_to_struct(FILE *file, struct menu_item_ *items, int *count);
void formatted_menu(const menu_item *items, int count);

int main(void) {
    char file_name[LINESIZE];
    menu_item items[NUM_OF_ITEMS];
    int count = 0;

    printf("Enter name of the file: ");
    read_string(file_name);

    FILE *file = open_file(file_name, "r");

    if (file != NULL) {
        if (file_to_struct(file, items, &count)) {
            formatted_menu(items, count);
        } else printf("Parsing to structures failed\n");
    }
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

FILE* open_file(const char *file_name, const char *mode) {
    FILE *file = fopen(file_name, mode);

    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", file_name);
        return NULL;
    }
    return file;
}

bool file_to_struct(FILE *file, struct menu_item_ *items, int *count) {
    char line[LINESIZE];
    char *price = NULL;

    if (file != NULL) {
        while (!feof(file)) {
            while(fgets(line, LINESIZE, file) != NULL && *count < NUM_OF_ITEMS) {
                price = strchr(line, ';');
                if (price != NULL) {
                    *price = '\0';
                    price++;

                    if (strlen(line) < NAME_SIZE) {
                        strncpy(items[*count].name, line, NAME_SIZE);
                        items[*count].name[NAME_SIZE - 1] = '\0';

                        if (sscanf(price, "%lf", &items[*count].price) == 1) {
                            (*count)++;
                        } else fprintf(stderr, "Error reading price for %s\n", items[*count].name);

                    } else fprintf(stderr, "Name exceeds maximum length. Product will be skipped\n");

                }
            }
        }
    }
    return (*count) > 0;
}

void formatted_menu(const menu_item *x, int count) {
    for (int i = 0; i < count; ++i) {
        printf("%8.2lf %s\n", x[i].price, x[i].name);
    }
}