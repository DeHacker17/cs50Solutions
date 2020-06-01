//
// Created by Kratos on 01/06/20.
//

#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    //Create a variable to store the elements of argv[1]
    //And check for duplicates
    char *duplicate = argv[1];

    //Check if user put 2 arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
        //Check if user inputted 2 argc
    else if (argc == 2)
    {
        //Check if the second argument has 26 letters
        if (strlen(argv[1]) != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
        //Check if user inputted numbers
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            if (!isalpha(argv[1][i]))
            {
                printf("Usage: ./substitution key\n");
                printf("Only letters are permitted\n");
                return 1;
            }
        }
        //Check for duplicates
        for (int k = 0; k < strlen(argv[1]); k++)
        {
            for (int j = k + 1; j < strlen(argv[1]); j++)
            {
                if (duplicate[k] == duplicate[j])
                {
                    printf("Repeated letter are not allowed\n");
                    return 1;
                }
            }
        }
    }

    //Ask user fot the plaintext
    //Use this string to store the values
    string s = get_string("plaintext: ");
    int c;
    int d;

    //Iterate through the string
    for (int i = 0; i < strlen(s); i++)
    {
        //Check if character at s[i] is alpha
        if (isalpha(s[i]))
        {
            //Cipher uppercase
            if (isupper(s[i]))
            {
                s[i] = (s[i] - 65) % 26;
                c = s[i];
                s[i] = duplicate[0 + c];
                s[i] = toupper(s[i]);
            }
                //Cipher lowercase
            else if (islower(s[i]))
            {
                s[i] = (s[i] - 97) % 26;
                c = s[i];
                s[i] = duplicate[0 + c];
                s[i] = tolower(s[i]);
            }
        }
            //Check if the character is not alpha and do not change it
        else
        {
            s[i] = s[i];
        }
    }

    //Print the ciphertext
    printf("ciphertext: %s\n", s);
}