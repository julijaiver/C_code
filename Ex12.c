#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define INPUT_LENGTH 80
#define NOT_FOUND 0

int count_words(const char *str, const char *search);
bool read_string(char *string);

int main(void) {
    char string[INPUT_LENGTH];
    char search[INPUT_LENGTH];
    int firstString;
    int occurrences;

    do {
        printf("Enter a string: ");
        firstString = read_string(string);

        if (firstString) {
            printf("Enter a search string: ");
            read_string(search);

            occurrences = count_words(string, search);

            if (occurrences > 0) {
                printf("%s is found %d times.\n", search, occurrences);
            } else printf("\'%s\' is not found.\n", search);
        }
    } while (firstString);

    return 0;
}

bool read_string(char *string) {

    if (fgets(string, INPUT_LENGTH, stdin) != NULL) {
        int len = strlen(string);

        if (string[len - 1] == '\n') {
            string[len - 1] = '\0';
        }

        if (strncasecmp(string, "stop", 4) == 0 && strlen(string) == 4) {
            return false;
        }
    }
    return true;
}

int count_words(const char *str, const char *search) {
    int count = 0;
    const char *p = str;

    if (strlen(search) == 0) {
        return NOT_FOUND;
    }

    while ((p = strstr(p, search)) != NULL) {
        ++count;
        p += strlen(search);
    }
    return count;
}