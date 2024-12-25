#include <ctype.h>
#include <stdio.h>
#include <string.h>

void process_string(char *string);

int main(void) {
    char string[] = "+ID: DevEui, 2C:F7:F1:20:32:30:A5:70";
    process_string(string);
    printf("%s\n", string);

    return 0;
}

void process_string(char *string) {
    char *read_ptr = string;
    char *write_ptr = string;
    int found_comma = 0;

    while (*read_ptr != '\0') {
        if (!found_comma) {
            if (*read_ptr == ',') {
                found_comma = 1;
            }
        } else {
            if (*read_ptr != ' ' && *read_ptr != ':') {
                *write_ptr++ = *read_ptr;
            }
        }
        read_ptr++;
    }
    *write_ptr = '\0';

    int len = strlen(string);
    for (int i = 0; i < len; ++i) {
        string[i] = tolower(string[i]);
    }
}