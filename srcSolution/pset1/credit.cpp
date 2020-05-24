//
// Created by Kratos on 20/05/20.
//

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Variable for user input
    long getCard;
    long checkCard;
    //Variable for checking sum
    long checkSum1;
    long checkSum2;
    long checkSum3;
    long checkSum4 = 0;
    //Variable if checksum of 2 is >= 10
    long splitResult = 0;

    do
    {
        //Get user input
        getCard = get_long("Enter credit card: ");
    }
    while (getCard < 0);
    checkCard = getCard;

    //Use for loop for getting checkSum
    for (int i = 0; i < 8; i++)
    {
        //Get first number of the card
        checkSum1 = getCard % 10;
        getCard /= 10;
        //Use for loop to get the second number and multiply it by 2
        for (int j = i - 1; j < i; j++)
        {
            checkSum2 = getCard % 10;
            checkSum2 *= 2;
        }
        //If the checkSum2 number is >= 10 divide it and sum both numbers
        if (checkSum2 >= 10)
        {
            long splitNum1 = checkSum2 / 10;
            long splitNum2 = checkSum2 % 10;
            splitResult = splitNum1 + splitNum2;
            checkSum2 = splitResult;
        }
        //Add checkSum2 and checkSum1
        checkSum3 = checkSum2 + checkSum1;
        checkSum4 += checkSum3;
        //Divide it 10 so the card number gets smaller
        getCard /= 10;
        printf("%li\n", checkSum4);
    }

    //Check if it is an AMEX
    if ((checkCard > 340000000000000 && checkCard < 350000000000000) || (checkCard > 370000000000000 && checkCard < 380000000000000))
    {
        //The value of checkSum must be 0
        if (checkSum4 % 10 == 0)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
        //Check if it is a MASTERCARD
    else if (checkCard > 5100000000000000 && checkCard < 5600000000000000)
    {
        if (checkSum4 % 10 == 0)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
        //Check if it is a VISA
    else if ((checkCard > 4000000000000000 && checkCard < 5000000000000000) || (checkCard < 5000000000000 && checkCard > 4000000000000))
    {
        if (checkSum4 % 10 == 0)
        {
            printf("VISA\n");
        }
            //Add extra else to all if statements in case it enters
        else
        {
            printf("INVALID\n");
        }
    }
        //Else is valid
    else
    {
        printf("INVALID\n");
    }
}