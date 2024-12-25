#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define LINESIZE 80
#define NAME_SIZE 50
#define NUM_OF_ITEMS 40

typedef struct menu_item_ {
    char name[NAME_SIZE];
    double price;
} menu_item;

typedef int (*compare_func)(const void *, const void *);

void read_string(char *string);
int read_choice(int *choice, const char *prompt);
FILE* open_file(const char *file_name, const char *mode);
bool file_to_struct(FILE *file, struct menu_item_ *items, int *count);
void formatted_menu(const menu_item *items, int count);
int compare_by_name (const void *a, const void *b);
int compare_by_price (const void *a, const void *b);
void sort_menu(menu_item *items, int count, compare_func compare);

int main(void) {
    char file_name[LINESIZE];
    menu_item items[NUM_OF_ITEMS];
    int count = 0;
    int choice = 0;

    printf("Enter name of the file: ");
    read_string(file_name);

    FILE *file = open_file(file_name, "r");

    if (file != NULL) {
        if (file_to_struct(file, items, &count)) {
            do {
                printf("How would you like to sort the menu?\n");
                printf("1. Sort by name\n2. Sort by price\n");
                choice = read_choice(&choice, "Enter 1 or 2: ");
                if (choice == 1) {
                    sort_menu(items, count, compare_by_name);
                } else if (choice == 2) {
                    sort_menu(items, count, compare_by_price);
                }
            } while (choice != 1 && choice != 2);

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

int read_choice(int *choice, const char *prompt) {
    char line[LINESIZE];
    while (true) {
        printf("%s", prompt);
        if (fgets(line, LINESIZE, stdin) != NULL) {
            if (sscanf(line, "%d", choice) == 1 && (*choice == 1 || *choice == 2)) {
                break;
            } else printf("Invalid choice. Please enter 1 or 2.\n");
        }
    }
    return *choice;
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

int compare_by_name (const void *a, const void *b) {
    const menu_item *item1 = (const menu_item *)a;
    const menu_item *item2 = (const menu_item *)b;
    return strcmp(item1->name, item2->name);
}

int compare_by_price (const void *a, const void *b) {
    const menu_item *item1 = (const menu_item *)a;
    const menu_item *item2 = (const menu_item *)b;
    if (item1->price < item2->price) return -1;
    else if (item1->price > item2->price) return 1;
    else return 0;
}

void sort_menu(menu_item *items, int count, compare_func compare) {
    qsort(items, count, sizeof(menu_item), compare);
}
