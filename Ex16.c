#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define LINESIZE 80

typedef struct node {
    int number;
    struct node *next;
} nnode;

void remove_newline(char *str);
bool input_valid(int *number, const char *prompt);
void print_and_free(nnode *head);

int main(void) {
    int number;
    nnode *head = NULL;
    nnode *tail = NULL;

    while (input_valid(&number, "Enter a number. Enter 'end' to stop: ")) {
        nnode *new_node = malloc(sizeof(struct node));
        if (new_node == NULL) {
            printf("Error: malloc failed\n");
            print_and_free(head);
            return 1;
        }
        new_node->number = number;
        new_node->next = NULL;

        if (head == NULL) {
            head = new_node;
        } else {
            tail->next = new_node;
        }
        tail = new_node;
    }

    if (head != NULL) {
        print_and_free(head);
    }

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

    while (true) {
        char line[LINESIZE];
        printf("%s", prompt);
        fgets(line, LINESIZE, stdin);
        remove_newline(line);

        if(strcmp(line, "end") == 0) {
            return false;
        }

        if(sscanf(line, "%d %c", number, &additionalChar) == 1) {
            return true;
        }
        printf("Invalid input, try again\n");
    }

}

void print_and_free(nnode *head) {
    nnode *current = head;
    printf("You entered:\n");

    while (current != NULL) {
        printf("%d ", current->number);
        nnode *temp = current;
        current = current->next;
        free(temp);
    }
}