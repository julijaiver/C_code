#include <stdio.h>
#include <string.h>

#define LINESIZE 80

void read_string(char *string);
FILE* open_file(const char *file_name, const char *mode);
void process_file(FILE *file);

int main(void) {
    char file_name[LINESIZE];

    printf("Enter the file name: ");
    read_string(file_name);
    FILE *file = open_file(file_name, "r");
    if (file != NULL) {
        process_file(file);
        fclose(file);
    }

    return 0;
}

void read_string(char *string) {
    if (fgets(string, LINESIZE, stdin) != NULL) {
        int len = strlen(string);
        if (string[len - 1] == '\n') {
            string[len - 1] = '\0';
        }
    }
}

FILE* open_file(const char *file_name, const char *mode) {
    FILE *file = fopen(file_name, mode);
    if (file == NULL) {
        fprintf(stderr, "Error opening file %s\n", file_name);
    }
    return file;
}

unsigned char calculate_checksum(const char *line) {
    unsigned char checksum = 0;
    const char *p = line + 1;

    while (*p != '*' && *p != '\0') {
        checksum ^= *p;
        ++p;
    }
    return checksum;
}

int verify_checksum(const char *line) {
    if (line[0] != '$') {
        return 0;
    }

    char *asterisk = strchr(line, '*');
    if (asterisk == NULL) {
        return 0;
    }

    unsigned int str_checksum;
    if (sscanf(asterisk + 1, "%2x", &str_checksum) != 1) {
        return 0;
    }

    unsigned char checksum = calculate_checksum(line);

    return checksum == str_checksum;
}

void process_file(FILE *file) {
    char line[LINESIZE];

    while (!feof(file)) {
        while (fgets(line, LINESIZE, file) != NULL) {
            line[strcspn(line, "\n")] = '\0';

            if (verify_checksum(line)) {
                printf("[OK] %s\n", line);
            } else printf("[FAIL] %s\n", line);
        }
    }
}

