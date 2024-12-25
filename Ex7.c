#include <stdio.h>
#include <stdbool.h>

#define INPUT_LENGTH 50
#define EXTRA_COMPUTER_MONEY 20
#define NUM_OF_TRIES 3

bool read_integer(int *number, const char *prompt);
bool read_positive(int *number, const char *prompt);

int main(void) {
    int guess, computerMoney, incorrectInput = 0;

    do {
        printf("Guess how much money I have!\n");
        if (read_positive(&guess, "Please enter a positive number: ")) {
            computerMoney = (guess * 2) + EXTRA_COMPUTER_MONEY;
            printf("You didn't get it right. I have %d euros.\n", computerMoney);
        } else incorrectInput += 1;
    } while (incorrectInput < NUM_OF_TRIES);

    printf("I give up! See you later!");

    return 0;
}

bool read_integer(int *number, const char *prompt) {
    char input[INPUT_LENGTH];
    char additionalChar;

    printf("%s", prompt);

    fgets(input, INPUT_LENGTH, stdin);
    if (sscanf(input, "%d %c", number, &additionalChar) == 1) {
        return true;
    }
    printf("Invalid input. Enter an integer.\n");
    return false;
}

bool read_positive(int *number, const char *prompt) {
    if (read_integer(number, prompt)) {
        if (*number > 0) {
            return true;
        }
        printf("The number must be positive");
    }
    return false;
}


