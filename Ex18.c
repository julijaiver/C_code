#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define LINESIZE 80
#define MIN_INPUT 0
#define MAX_INPUT 15

void remove_newline(char *str);
bool input_valid(int *number, const char *prompt);
void print_hex(int *hex_value);
void print_shifted_hex(int input, int hex_value);

int main(void) {
    int input;
    int hex_value;

    srand(time(NULL));
    do {
        while (!input_valid(&input, "Enter a number 0-15 or negative number to stop: ")) {
        }

        if (input < MIN_INPUT) {
            break;
        }
            print_hex(&hex_value);
            print_shifted_hex(input, hex_value);
    } while (input > MIN_INPUT);

    return 0;
}

void remove_newline(char *str) {
    int len = strlen(str);
    if (len > 0 && str[len-1] == '\n') {
        str[len-1] = '\0';
    }
}

bool input_valid(int *number, const char *prompt) {
    char additionalChar;
    char line[LINESIZE];

    printf("%s", prompt);
    fgets(line, LINESIZE, stdin);
    remove_newline(line);

    if(sscanf(line, "%d %c", number, &additionalChar) == 1) {
        if (*number >= MIN_INPUT && *number <= MAX_INPUT) {
            return true;
        } else if (*number < MIN_INPUT) {
            return true;
        } else printf("Input over the range of 0-15. Please enter a valid number.\n");
    } else printf("Invalid input.\n");

    return false;
}

void print_hex(int *hex_value) {
    *hex_value = rand();  /*Was not sure about the range of the value*/
    printf("Random hexadecimal value: 0x%x\n", *hex_value);
}

void print_shifted_hex(int input, int hex_value) {
    int shifted = hex_value >> input;
    int significant_bits = shifted & 0x3F;
    printf("Hexadecimal value shifted by %d bits to the right (6 significant bits masked):"
           " 0x%02x\n", input, significant_bits );
}
