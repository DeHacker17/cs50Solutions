//
// Created by Kratos on 01/06/20.
//

#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    //Check if user put 2 arguments
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
        //Check is the second argument is an integer
    else if (argc == 2)
    {
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            if (!isdigit(argv[1][i]))
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
    }

    //Convert argv[1] to an int
    int k = atoi(argv[1]);

    //Ask user fot the plaintext
    //Use this string to store the values
    string s = get_string("plaintext: ");

    //Iterate through the string
    for (int i = 0; i < strlen(s); i++)
    {
        //Check if character at s[i] is alpha
        if (isalpha(s[i]))
        {
            //Cipher uppercase
            if (isupper(s[i]))
            {
                s[i] -= 65;
                s[i] = ((s[i] + k) % 26) + 65;
            }
                //Cipher lowercase
            else if (islower(s[i]))
            {
                s[i] -= 97;
                s[i] = ((s[i] + k) % 26) + 97;
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