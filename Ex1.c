#include <stdio.h>
#define BUS_OPTION 1
#define TAXI_OPTION 2

int main(void) {
    double busTicket, taxiRide, moneyInPocket;
    int selection;

    printf("Enter price of bus ticket: ");
    scanf("%lf", &busTicket);
    printf("Enter price of taxi ride: ");
    scanf("%lf", &taxiRide);
    printf("How much money you have: ");
    scanf("%lf", &moneyInPocket);

    if (moneyInPocket < busTicket && moneyInPocket < taxiRide) {
        printf("You don't have enough money for transport.\n");
    } else {
        while (moneyInPocket >= busTicket || moneyInPocket >= taxiRide) {
            printf("You have %.2lf euros left.\n", moneyInPocket);
            printf("Do you want to take \n\t1) bus (%.2lf euros)\n\t2) taxi(%.2lf euros)\n", busTicket, taxiRide);
            printf("Enter your selection: ");
            scanf("%d", &selection);
            switch (selection) {
                case BUS_OPTION:
                    if (moneyInPocket >= busTicket) {
                        printf("You chose bus.\n");
                        moneyInPocket -= busTicket;
                    } else printf("You don't have enough money for bus.");
                break;
                case TAXI_OPTION:
                    if (moneyInPocket >= taxiRide) {
                        printf("You chose taxi.\n");
                        moneyInPocket -= taxiRide;
                    } else printf("You don't have enough money for taxi.");
                break;
                default: printf("Invalid selection. Please enter 1 or 2\n");
            }
        }

    }

    printf("You have %.2lf euros left.\n", moneyInPocket);
    printf("You need to walk. Bye");

    return 0;
}

