//
// Created by Kratos on 20/05/20.
//

#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float cashOwed;

    //Get input from user
    do
    {
        //Prompt user to enter valid amount
        cashOwed = get_float("Change owed: ");
    }
    while (cashOwed < 0.0);

    //Variables
    int cents = round(cashOwed * 100);
    int numCoins = 0;
    int pennies = 1;
    int nickels = 5;
    int dimes = 10;
    int quarters = 25;

    //Calculates how many quarters will be given
    while (cents >= quarters)
    {
        cents -= 25;
        numCoins++;
    }
    //Calculates how many dimes will be given
    while (cents >= dimes)
    {
        cents -= 10;
        numCoins++;
    }
    //Calculates how many nickels will be given
    while (cents >= nickels)
    {
        cents -= 5;
        numCoins++;
    }
    //Calculates how many cents will be given
    while (cents >= pennies)
    {
        cents -= 1;
        numCoins++;
    }

    //Prints remaining change
    printf("%i\n", cents);

    printf("The number of coins used was: %i\n", numCoins);
}