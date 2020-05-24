//
// Created by Kratos on 24/05/20.
//

#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int main(int argc, string argv[])
{
    //Declare variables
    float letters = 0;
    float words = 1;
    float sentences = 0;

    //Ask user for text
    string A = get_string("Enter your text: ");

    //For loop to count Letter, Words, and Sentences
    for (int i = 0; i < strlen(A); i++)
    {
        //Check if is lowercase or uppercase
        if (islower(A[i]) || isupper(A[i]))
        {
            //Increment letter by 1
            letters++;
        }
        //Count words
        if (isspace(A[i]))
        {
            words++;
        }
        //Check to see when a sentence ends
        if (A[i] == '.' || A[i] == '?' || A[i] == '!')
        {
            //Increment sentences by 1
            sentences++;
        }
    }

    //Formula to calculate Grade
    words = 100 / words;
    letters *= words;
    sentences *= words;
    float index = 0.0588 * letters - 0.296 * sentences - 15.8;

    //Print the result
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.0f\n", round(index));
    }
}
