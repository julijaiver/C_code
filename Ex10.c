#include <stdio.h>
#include <string.h>

#define INPUT_LENGTH 80
#define STOP -1
#define NOT_READ 0

int read_string(void);

int main(void) {
    int result;

    do {
        printf("Enter a string. Enter 'stop' to stop the program: ");
        result = read_string();
        if (result != STOP) {
            if (result == NOT_READ) {
                printf("Error reading result\n");
            } else printf("Length of entered string is %d\n", result);
        }
    } while (result != STOP);

    return 0;
}

int read_string(void) {
    char input[INPUT_LENGTH];

    if (fgets(input, INPUT_LENGTH, stdin) != NULL) {
        int len = strlen(input);

        if (input[len - 1] == '\n') {
            input[len - 1] = '\0';
            --len;
        }

        if (strncasecmp(input, "stop", 4) == 0 && len == 4) {
            return STOP;
        }
        return len;
    }
    return NOT_READ;
}