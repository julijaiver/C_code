#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define LINESIZE 80
#define MIN_TEMP 0
#define MAX_TEMP 30
#define HALF_CENTIGRADE 0.5

void remove_newline(char *str);
bool validate_filename(char *str);
FILE* open_file(const char *file_name, const char *mode);
int room_selection(char **rooms, int num_of_rooms);
char **room_array(FILE *file, int *num_of_rooms);
double* file_to_array(FILE *file, const char *room_name, int *count);
void print_array(double *room_temp, int count);
char *calculate_dashes(double value);
void free_rooms(char **rooms, int num_of_rooms);

int main(void) {
    char file_name[LINESIZE];
    int num_of_rooms = 0;
    int selected_room;

    printf("Enter name of the csv file to be read: ");
    if (fgets(file_name, LINESIZE, stdin) != NULL) {
        remove_newline(file_name);
    }

    if (validate_filename(file_name)) {
        FILE *file = open_file(file_name, "r");
        if (file) {
            char **rooms = room_array(file, &num_of_rooms);
            if (rooms == NULL) {
                printf("No rooms found\n");
                fclose(file);
                return 0;
            }

            do {
                selected_room = room_selection(rooms, num_of_rooms);
                if (selected_room > 0) {
                    rewind(file); /*To be able to read with multiple selections in one program*/
                    int count = 0;
                    double *room_temp = file_to_array(file, rooms[selected_room - 1], &count);
                    if (room_temp != NULL) {
                        printf("%s\n", rooms[selected_room - 1]);
                        print_array(room_temp, count);
                        free(room_temp);
                    } else {
                        printf("No temperature data found for %s.\n", rooms[selected_room - 1]);
                    }
                }
            } while (selected_room != 0);

            fclose(file);
            free_rooms(rooms, num_of_rooms);
        } else {
            printf("File not found\n");
        }
    } else {
        printf("File name needs to contain .csv extension.\n");
    }

    return 0;
}

void remove_newline(char *str) {
    int len = strlen(str);
    if (len > 0 && str[len-1] == '\n') {
        str[len-1] = '\0';
    }
}

bool validate_filename(char *str) {
    char *extension = strchr(str, '.');

    if (extension != NULL && strcmp(extension, ".csv") == 0) {
        return true;
    }
}

FILE* open_file(const char *file_name, const char *mode) {
    FILE *file = fopen(file_name, mode);
    if (file == NULL) {
        fprintf(stderr, "Error opening file %s\n", file_name);
    }
    return file;
}

int room_selection(char **rooms, int const num_of_rooms) {
    int selected_room;
    char input[LINESIZE];

    printf("Select room by entering the room number. Enter 0 to stop: ");
    printf("\n");
    for (int i = 0; i < num_of_rooms; ++i) {
        printf("%d. %s\n", i + 1, rooms[i]);
    }

    if (fgets(input, LINESIZE, stdin) && sscanf(input, "%d", &selected_room) == 1) {
         if (selected_room >= 1 && selected_room <= num_of_rooms) {
             return selected_room;
         } printf("Entered number out of scope. Please enter a number 1-%d.\n", num_of_rooms);
    } else printf("Invalid input. Please enter a number.\n");

    return 0;
}

char **room_array(FILE *file, int *num_of_rooms) {
    char line[LINESIZE];
    char **rooms = NULL;
    char *comma;

    /*Skip the first header line in the file*/
    if (fgets(line, LINESIZE, file) == NULL) {
        printf("Error reading file header\n");
        return NULL;
    }

    while (fgets(line, LINESIZE, file) != NULL) {
        /*Separate temperature from room namw*/
        comma = strchr(line, ',');
        if (comma) {
            *comma = '\0';
            remove_newline(comma + 1);
            bool room_exists = false;

            for (int i = 0; i < *num_of_rooms; ++i) {
                if (strcmp(rooms[i], comma + 1) == 0) {
                    room_exists = true;
                    break;
                }
            }

            if (!room_exists) {
                rooms = realloc(rooms, sizeof(char *) * (*num_of_rooms + 1));
                if (rooms == NULL) {
                    printf("Memory allocation error\n");
                    return NULL;
                }
                /*Add room to room array*/
                rooms[*num_of_rooms] = strdup(comma + 1);
                (*num_of_rooms)++;
            }
        }
    }
    return rooms;
}

double* file_to_array(FILE *file, const char *room_name, int *count) {
    char line[LINESIZE];
    double *room_temp = NULL;
    *count = 0;

    if (fgets(line, LINESIZE, file) == NULL) {
        printf("Error reading file header\n");
        return NULL;
    }

    while (fgets(line, LINESIZE, file) != NULL) {
        char *comma = strchr(line, ',');
        if (comma) {
            *comma = '\0';
            remove_newline(comma + 1);
            char *endp;
            double temp = strtod(line, &endp);
            /*Storing room temperatures in a list*/
            if (strcmp(comma + 1, room_name) == 0 && *endp == '\0') {
                room_temp = realloc(room_temp, sizeof(double) * (*count + 1));
                if (room_temp == NULL) {
                    printf("Memory allocation error\n");
                    return NULL;
                }
                room_temp[*count] = temp;
                (*count)++;
            }
        }
    }
    return room_temp;
}

/*Calculating num of dashes for temperature value & storing in array*/
char *calculate_dashes(double value) {
    int num_of_dashes = (int) (value / HALF_CENTIGRADE);
    char *dashes = malloc((num_of_dashes + 1) * sizeof(char));

    if (dashes != NULL) {
        for(int i = 0; i < num_of_dashes; ++i) {
            dashes[i] = '-';
        }
        dashes[num_of_dashes] = '\0';
    } else printf("Memory allocation error while calculating dashes.\n");

    return dashes;
}

void print_array(double *room_temp, int count) {
    for (int i = 0; i < count; ++i) {
        double temp = room_temp[i];
        if (temp >= MIN_TEMP && temp <= MAX_TEMP) {
            char *dashes = calculate_dashes(temp);
            printf("%3.1f %s\n", temp, dashes);
            free(dashes);
        } else {
            printf("%3.1f X\n", temp);
        }
    }
}

/*Freeing the whole array and each pointer*/
void free_rooms(char **rooms, int num_of_rooms) {
    for (int i = 0; i < num_of_rooms; ++i) {
        free(rooms[i]);
    }
    free(rooms);
}

