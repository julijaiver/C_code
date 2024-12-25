#include <stdio.h>

#define MIN_DIE 1
#define MAX_DIE 6
#define ROUNDS 3

int read_integer(void);
int read_range(int low, int high);

int main(void) {
    int pcResult;

    printf("Let's play!\n");

    for (int i = 0; i < ROUNDS; ++i) {
        printf("Roll a die and enter your result.\n");
        int rolledDie = read_range(MIN_DIE, MAX_DIE);
        if (rolledDie < MAX_DIE) {
            pcResult = ++rolledDie;
            printf("I got %d. I win!\n", pcResult);
        } else {
            pcResult = MAX_DIE;
            printf("I got %d. It's a tie!\n", pcResult);
        }
    }

    printf("Better luck next time. Bye!\n");

    return 0;
}

/* Function from EX.4 */
int read_integer(void) {
    int readInteger, result;

    do {
        result = scanf("%d", &readInteger);

        if (result != 1) {
            while (getchar() != '\n');
            printf("Invalid input. Please enter a valid integer: ");
        }
    } while (result != 1);

    return readInteger;
}

int read_range(const int low, const int high) {
    int enteredValue;

    do {
        printf("Enter an integer between %d and %d: ", low, high);
        enteredValue = read_integer();

        if (enteredValue < low || enteredValue > high) {
            printf("Value out of range. Enter again.\n");
        }
    } while (enteredValue < low || enteredValue > high);

    return enteredValue;
}