#include <stdio.h>

int read_integer(void);

int main(void) {
    int number, numOfIntegers = 0, sum = 0;

    do {
        printf("Enter positive numbers or a negative number to stop: ");
        number = read_integer();
        if (number >= 0) {
            sum += number;
            ++numOfIntegers;
        }
    } while (number >= 0);

    if(numOfIntegers > 0) {
        const double average = sum / (double) numOfIntegers;
        printf("You entered %d positive integers. Average is: %.3lf\n", numOfIntegers, average);
    } else printf("No integers were entered");


    return 0;
}

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