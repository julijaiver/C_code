#include <stdio.h>

#define MONTHS_PER_YEAR 12
#define PERCENT_DIVISOR 100

int main(void) {
    double income[MONTHS_PER_YEAR];
    double taxAmount[MONTHS_PER_YEAR];

    double taxRate, incomeLimit, overLimitTaxRate, incomeSum = 0;

    printf("Enter tax rate: ");
    scanf("%lf", &taxRate);
    printf("Enter income limit: ");
    scanf("%lf", &incomeLimit);
    printf("Enter tax rate for income over the limit: ");
    scanf("%lf", &overLimitTaxRate);


    for (int index = 0; index < MONTHS_PER_YEAR; index++) {
        printf("Enter income for month %d: ", index + 1);
        scanf("%lf", &income[index]);
    }

    for (int index = 0; index < MONTHS_PER_YEAR; index++) {
        const double regularTaxPercentage = taxRate/PERCENT_DIVISOR;
        const double overLimitTaxPercentage = overLimitTaxRate/PERCENT_DIVISOR;

        incomeSum += income[index];

        if (incomeSum <= incomeLimit) {
            taxAmount[index] = income[index]*regularTaxPercentage;
        } else {
            const double previousIncomeSum = incomeSum - income[index];

            if (previousIncomeSum < incomeLimit) {
                const double underLimitIncome = incomeLimit - previousIncomeSum;
                const double overLimitIncome =  income[index] - underLimitIncome;
                taxAmount[index] = (underLimitIncome * regularTaxPercentage) + (overLimitIncome * overLimitTaxPercentage);
            } else {
                taxAmount[index] = income[index]*overLimitTaxPercentage;
            }
        }
    }

    printf("%5s%10s%9s\n", "month", "income", "tax");
    for (int index = 0; index < MONTHS_PER_YEAR; index++) {
        printf("%5d%10.2lf%9.2lf\n", index+1, income[index], taxAmount[index]);
    }

    return 0;

}