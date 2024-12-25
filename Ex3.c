#include <stdio.h>

#define MIN_GRADE 0
#define MAX_GRADE 5
#define NO_GRADE -1
#define INVALID_GRADE -2
#define STOP_INDICATOR 0

int main(void) {
    int numOfStudents, studentNumber, studentGrade;

    do {
        printf("Enter number of students: ");
        if (scanf("%d", &numOfStudents) != 1 || numOfStudents <= 0) {
            while (getchar() != '\n');
            printf(("Invalid input. Please enter a positive number.\n"));
            numOfStudents = 0;
        }
    } while (numOfStudents <= 0);


    int students[numOfStudents];

    for (int index = 0; index < numOfStudents; index++) {
        students[index] = NO_GRADE;
    }

    do {
        do {
            printf("Enter student number 1-%d or 0 to stop: ", numOfStudents);
            if (scanf("%d", &studentNumber) != 1) {
                while (getchar() != '\n');
                printf("Invalid input. Please enter a number 1-%d.\n", numOfStudents);
                studentNumber = NO_GRADE;
            }
        } while (studentNumber < 0 || studentNumber > numOfStudents);


        if (studentNumber <= numOfStudents && studentNumber > STOP_INDICATOR) {
            do {
                printf("Enter grade (0 - 5) for student %d or -1 to cancel: ", studentNumber);
                if (scanf("%d", &studentGrade) != 1) {
                    while (getchar() != '\n');
                    studentGrade = INVALID_GRADE;
                }

                if (studentGrade >= MIN_GRADE && studentGrade <= MAX_GRADE) {
                    students[studentNumber-1] = studentGrade;
                } else if (studentGrade < NO_GRADE || studentGrade > MAX_GRADE) {
                    printf("Invalid grade. Enter a grade 0 - 5.\n");
                }
            } while (studentGrade < NO_GRADE || studentGrade > MAX_GRADE);

        } else if (studentNumber < STOP_INDICATOR || studentNumber > numOfStudents) {
            printf("Invalid student number. Enter a number from 1 to %d.\n", numOfStudents);
        }
    } while (studentNumber != STOP_INDICATOR);

    printf("%-10s%-5s\n", "Student", "Grade");
    for (int index = 0; index < numOfStudents; index++) {
        if (students[index] == NO_GRADE) {
            printf("%-10d%-5s\n", index+1, "N/A");
        } else {
            printf("%-10d%-5d\n", index+1, students[index]);
        }

    }

    return 0;

}