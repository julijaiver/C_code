#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define INPUT_LENGTH 50
#define ARRAY_LENGTH 20
#define NUM_OF_INTEGERS (ARRAY_LENGTH - 1)
#define NOT_FOUND -1

bool read_positive(unsigned int *number, const char *prompt);
bool read_integer(unsigned int *number, const char *prompt);
int find_first(const unsigned int *array, unsigned int what);


int main(void) {
    unsigned int array[ARRAY_LENGTH], numberToLook;
    int searchResult;

    srand(time(NULL));

    for(int i = 0; i < NUM_OF_INTEGERS; ++i) {
        array[i] = (unsigned int) rand() % ARRAY_LENGTH +1;
        printf("%d\n", array[i]);
    }
    array[ARRAY_LENGTH - 1] = 0;

    do {
        printf("Enter a number to look. Enter 0 to stop.\n");
        if (read_positive(&numberToLook, "Please enter a positive number: ")) {
            searchResult = find_first(array, numberToLook);
            if (searchResult == NOT_FOUND) {
                printf("Number not found.\n");
            } else printf("Number found at index: %d\n", searchResult);
        }
    } while(numberToLook != 0);

    return 0;
}


bool read_integer(unsigned int *number, const char *prompt) {
    char input[INPUT_LENGTH];
    char additionalChar;

    printf("%s", prompt);

    fgets(input, INPUT_LENGTH, stdin);
    if (sscanf(input, "%u %c", number, &additionalChar) == 1) {
        return true;
    }
    printf("Invalid input. Enter an integer.\n");
    return false;
}

bool read_positive(unsigned int *number, const char *prompt) {
    if (read_integer(number, prompt)) {
        if (*number > 0) {
            return true;
        } else if (*number < 0) {
            printf("The number must be positive");
        }
    }
    return false;
}

int find_first(const unsigned int *array, unsigned int what) {
    int index = 0;
    while (array[index] != 0) {
        if (array[index] == what) {
            return index;
        }
        ++index;
    }
    return NOT_FOUND;
}