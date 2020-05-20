//
// Created by Kratos on 02/05/20.
//
#include <stdio.h>
#include <cs50.h>

int main(void)  {
    int h;

    do {
        h = get_int("Height of tower: ");
    } while (h < 1 || h > 8);

    for (int i = 0; i < h; i++) {
        for (int k = i + 1; k < h; k++) {
            printf(" ");
        }
        for (int j = -1; j < i; j++) {
            printf("#");
        }
        printf("\n");
    }
}


