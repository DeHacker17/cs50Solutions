//
// Created by Kratos on 20/05/20.
//

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //Varaible
    int h;
    //While loop for user if input is incorrect
    do
    {
        h = get_int("Height of tower: ");
    }
    while (h < 1 || h > 8);

    for (int i = 0; i < h; ++i)
    {
        for (int k = i + 1; k < h; ++k)
        {
            printf(" ");
        }

        for (int j = -1; j < i; ++j)
        {
            printf("#");
        }

        printf("  ");

        for (int n = -1; n < i; n++)
        {
            printf("#");
        }

        printf("\n");
    }
}
