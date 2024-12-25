#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define PASSW_INPUT 32
#define ASCII_MIN 32
#define ASCII_MAX 126

void remove_newline(char *str);
bool password_generator(char *password, int length, const char *input_word);

int main(void) {
    srand(time(NULL));

    bool end = false;
    while (!end) {
        char password[PASSW_INPUT];
        char input_word[PASSW_INPUT];

        printf("Please enter your input word. Enter 'end' to stop: ");
        fgets(input_word, PASSW_INPUT, stdin);
        remove_newline(input_word);
        if (strcmp(input_word, "end") == 0) {
            end = true;
        } else if (strlen(input_word) == 0) {
            printf("No word entered.\n");
        } else if (password_generator(password, PASSW_INPUT, input_word)) {
            printf("Generated password: %s\n", password);
        } else printf("Word entered is too long.\n");
    }

    return 0;
}

void remove_newline(char *str) {
    int len = strlen(str);
    if (len > 0 && str[len-1] == '\n') {
        str[len-1] = '\0';
    }
}

bool password_generator(char *password, int length, const char *input_word) {
    int word_len = strlen(input_word);
    int pass_length = word_len*2 + 1 ;

    if (pass_length > length - 1) {
        return false;
    }
    for (int i = 0; i < pass_length; ++i) {
        if (i % 2 == 0) {
            char random_char = rand() % (ASCII_MAX - ASCII_MIN + 1) + ASCII_MIN;
            password[i] = random_char;
        } else password[i] = input_word[i / 2];
    }

    password[pass_length] = '\0';
    return true;
}


