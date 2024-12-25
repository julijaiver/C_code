#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "debug.h"

#define LINESIZE 80
#define PRINT_LINES 5

bool read_integer(int *number, const char *prompt);


int main(void) {
    srand(time(NULL));
    int debug_level;
    bool valid_input = false;

    while (!valid_input) {
        valid_input = read_integer(&debug_level, "Enter debug level 0-4: ");
        if (valid_input && (debug_level < 0 || debug_level > 4)) {
            printf("Debug level must be from 0 to 4. Try again.\n");
            valid_input = false;
        }
    }

    set_debug_level(debug_level);

    for (int i = 1; i <= PRINT_LINES; ++i) {
        int random_debug_lvl = rand() % 5;
        dprintf(random_debug_lvl,"%d.\n", i);
    }

}

bool read_integer(int *number, const char *prompt) {
    char input[LINESIZE];
    char additionalChar;

    printf("%s", prompt);

    fgets(input, LINESIZE, stdin);
    if (sscanf(input, "%d %c", number, &additionalChar) == 1) {
        return true;
    }
    printf("Invalid input. Enter an integer.\n");
    return false;
}