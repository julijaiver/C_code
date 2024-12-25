#include <stdio.h>
#include <string.h>

#define INPUT_LENGTH 80
#define INVALID_INPUT -1

void read_string(char *string);
int replace_char(char *str, const char *replacement);

int main(void) {
    char inputString[INPUT_LENGTH];
    char replacementString[INPUT_LENGTH];
    int changedChars;

    printf("Please enter a string: ");
    read_string(inputString);

    printf("Enter a string of two characters. First: character to replace, second: replacement character: ");
    read_string(replacementString);

    changedChars = replace_char(inputString, replacementString);

    if (changedChars > 0) {
        printf("Replaced characters: %d\n", changedChars);
        printf("Modified string: %s\n", inputString);
    } else if (changedChars == INVALID_INPUT) {
        printf("Invalid replacement string input.\n");
    } else printf("String was not modified.\n");

    return 0;
}

void read_string(char *string) {

    if (fgets(string, INPUT_LENGTH, stdin) != NULL) {
        int len = strlen(string);
        if (string[len - 1] == '\n') {
            string[len - 1] = '\0';
        }
    }
}

int replace_char(char *str, const char *replacement) {
    int returnValue = 0;

    if (strlen(replacement) == 2) {
        for (int i = 0; str[i] != '\0'; ++i) {
            if (str[i] == replacement[0]) {
                str[i] = replacement[1];
                returnValue += 1;
            }
        }
    } else return INVALID_INPUT;
    return returnValue;
}
