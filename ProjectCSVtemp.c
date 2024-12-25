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
double** file_to_array(FILE *file, const char *room_name);
void print_array(double **room_temp);
char *calculate_dashes(double value);
void free_array(double **room_temp);

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
        if (file != NULL) {
            char **rooms = room_array(file, &num_of_rooms);
            if (rooms == NULL) {
                printf("No rooms found\n");
                fclose(file);
            }

            do {
                selected_room = room_selection(rooms, num_of_rooms);
                if (selected_room != 0) {
                    rewind(file); /*To be able to read with multiple selections in one program*/
                    double **room_temp = file_to_array(file, rooms[selected_room - 1]);
                    if (room_temp != NULL) {
                        printf("%s\n", rooms[selected_room - 1]);
                        print_array(room_temp);
                        free_array(room_temp);
                    } else printf("No temperature data found.\n");
                }
            } while (selected_room != 0);
            fclose(file);

            for (int i = 0; i < num_of_rooms; ++i) {
                free(rooms[i]);
            }
            free(rooms);

        } else printf("File not found\n");
    } else printf("File name needs to contain .csv extension.\n");

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
    return false;
}

FILE* open_file(const char *file_name, const char *mode) {
    FILE *file = fopen(file_name, mode);

    if (file == NULL) {
        fprintf(stderr, "Error opening file %s\n", file_name);
        return NULL;
    }
    return file;
}

int room_selection(char **rooms, int num_of_rooms) {
    printf("Select room by entering the room number: ");
    for (int i = 0; i < num_of_rooms; ++i) {
        printf("%d. %s\n", i+1, rooms[i]);
    }

    char input[LINESIZE];
    int selected_room;

    fgets(input, LINESIZE, stdin);

    if (sscanf(input, "%d", &selected_room) != 1) {
        printf("Invalid input. Please enter a number\n");
        return 0;
    }

    return selected_room;
}

char **room_array(FILE *file, int *num_of_rooms) {
    char line[LINESIZE];
    char **rooms = NULL;

    if(fgets(line, LINESIZE, file) == NULL) {
        printf("Error reading file header\n");
        return NULL;
    }

    while (!feof(file)) {
        while (fgets(line, LINESIZE, file) != NULL) {
            /*Separating temperatures and room names by finding the comma*/
            char *comma = strchr(line, ',');
            if (comma != NULL) {
                *comma = '\0';
                remove_newline(comma + 1);
            }

            bool room_exists = false;
            for(int i=0; i<*num_of_rooms; ++i) {
                if (strcmp (rooms[i], comma + 1) == 0) {
                    room_exists = true;
                    break;
                }
            }

            if (!room_exists) {
                char **new_rooms = realloc(rooms, (*num_of_rooms + 1) * sizeof(char *));
                if (new_rooms == NULL) {
                    printf("Memory allocation error\n");
                    free(rooms);
                    return NULL;
                }
                rooms = new_rooms;
                rooms[*num_of_rooms] = strdup(comma + 1);
                if (rooms[*num_of_rooms] == NULL) {
                    printf("Memory allocation error\n");
                    free(rooms);
                }
                (*num_of_rooms)++;
            }
        }
    }
    return rooms;
}


/*Use of pointer that points to array of dynamically allocated array pointers of temperature values read from a file*/
double** file_to_array(FILE *file, const char *room_name) {
    char line[LINESIZE];
    int count = 0;
    double **room_temp = NULL;

    /*Reading the first header line and skipping it before the loop*/
    if(fgets(line, LINESIZE, file) == NULL) {
        printf("Error reading file header\n");
        return NULL;
    }

    while (!feof(file)) {
        while (fgets(line, LINESIZE, file) != NULL) {
            /*Separating temperatures and room names by finding the comma*/
            char *comma = strchr(line, ',');
            if (comma != NULL) {
                *comma = '\0';

                /*Removing newline after room name(room name starts at comma +1 pointer)*/
                remove_newline(comma+1);

                char *endptr;
                double temp = strtod(line, &endptr); /*String conversion to double*/

                /*Dynamically allocating memory for room_temp array*/
                if (strcmp(comma + 1, room_name) == 0 && *endptr == '\0') {
                    /*Using new pointer to not lose room_temp if realloc fails*/
                    double **new_room_temp = realloc(room_temp, sizeof(double*) * (count + 1));
                    if (new_room_temp == NULL) {
                        printf("Room temperature reallocation error\n");
                        free_array(room_temp);
                        return NULL;
                    }
                    room_temp = new_room_temp;
                    room_temp[count] = malloc(sizeof(double));
                    if (room_temp[count] == NULL) {
                        printf("Room temperature memory allocation error\n");
                        free_array(room_temp);
                        return NULL;
                    }
                    *room_temp[count] = temp;
                    ++count;
                }
            }
        }
    }
    /*Terminating array of pointers with NULL*/
    if (room_temp != NULL) {
        room_temp[count] = NULL;
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

/*Formatting print*/
void print_array(double **room_temp) {
    if(room_temp != NULL) {
        printf("");
        for(int i = 0; room_temp[i] != NULL; ++i) {
            double temp = *room_temp[i];
            if (temp >= MIN_TEMP && temp <= MAX_TEMP) {
                char *dashes = calculate_dashes(temp);
                printf("%3.1f %s\n", temp, dashes);
                free(dashes);
            } else printf("%3.1f X\n", temp);
        }
    } else printf("No temperatures found for selected room.\n");
}

/*Freeing allocated memory*/
void free_array(double **room_temp) {
    for (int i=0; room_temp[i] != NULL; ++i) {
        free(room_temp[i]);
    }
    free(room_temp);
}
