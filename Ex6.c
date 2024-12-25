#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROLL_D6_OPTION 1
#define ROLL_D10_OPTION 2
#define QUIT_OPTION 3
#define D6_SIDES 6
#define D10_SIDES 10


int read_integer(void);
int roll_dice(int num_of_sides);

int main(void) {
    int selection, rolledDice;

    srand(time(NULL));

    printf("Welcome to 'Dice roller'! Select an option from the menu and type corresponding integer.\n");

    do{
      printf("1. Roll D6\n2. Roll D10\n3. Quit\n");
      printf("Enter selection: ");
      selection = read_integer();

      switch (selection) {
        case ROLL_D6_OPTION:
          rolledDice = roll_dice(D6_SIDES);
          printf("The rolled dice is: %d\n", rolledDice);
          break;
        case ROLL_D10_OPTION:
          rolledDice = roll_dice(D10_SIDES);
          printf("The rolled dice is: %d\n", rolledDice);
          break;
        case QUIT_OPTION:
          printf("Bye!\n");
          break;
        default:
          printf("Invalid selection, please try again.\n");
          break;
      }
    } while (selection != QUIT_OPTION);


    return 0;
}

/* Function from EX.4 */
int read_integer(void) {
  int readInteger, result;

  do {
    result = scanf("%d", &readInteger);

    if (result != 1) {
      while (getchar() != '\n');
      printf("Invalid input. Please enter a valid integer: ");
    }
  } while (result != 1);

  return readInteger;
}

int roll_dice(const int num_of_sides) {
  const int minSide = 1;
  return (rand() % num_of_sides) + minSide;
}