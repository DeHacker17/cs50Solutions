//
// Created by Kratos on 01/07/20.
//

#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //Variables
    float averageRed = 0;
    float averageBlue = 0;
    float averageGreen = 0;
    float fullAverage = 0;

    //Greyscale
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Assign pointer to the values of the pixels
            averageRed = image[i][j].rgbtRed;
            averageBlue = image[i][j].rgbtBlue;
            averageGreen = image[i][j].rgbtGreen;
            fullAverage = (averageRed + averageBlue + averageGreen) / 3;
            //Apply changes
            image[i][j].rgbtRed = round(fullAverage);
            image[i][j].rgbtBlue = round(fullAverage);
            image[i][j].rgbtGreen = round(fullAverage);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //Variables
    float sepiaRed = 0;
    float sepiaGreen = 0;
    float sepiaBlue = 0;

    //Sepia
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Apply formula
            sepiaRed = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            sepiaGreen = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            sepiaBlue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;
            //If pixel has value greater than 255, round it to 255
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            //Apply changes
            image[i][j].rgbtRed = round(sepiaRed);
            image[i][j].rgbtBlue = round(sepiaBlue);
            image[i][j].rgbtGreen = round(sepiaGreen);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //Variables
    RGBTRIPLE temp1;
    RGBTRIPLE *temp2 = NULL;
    RGBTRIPLE *temp3 = NULL;

    //Reflect
    for (int i = 0; i < height; i++)
    {
        int j = 0;
        int end = width;
        while (j < width / 2)
        {
            end--;
            temp1 = image[i][j];
            temp3 = &temp1;
            temp2 = &image[i][end];
            image[i][j] = *temp2;
            *temp2 = *temp3;
            image[i][end] = *temp2;
            j++;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Create a temporary variable
    RGBTRIPLE temp1[height][width];
    //Loop
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Reset Variables
            int divide = 0;
            float averageRed = 0;
            float averageBlue = 0;
            float averageGreen = 0;
            //Assign temporary variable to image
            temp1[i][j] = image[i][j];
            //Up
            if (i - 1 < 0)
            {
                //Up left corner
                if (j - 1 < 0)
                {
                    divide = 4;
                    averageRed = (image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed);
                    averageBlue = (image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue);
                    averageGreen = (image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen);
                }
                    //Up right corner
                else if (j + 1 > width - 1)
                {
                    divide = 4;
                    averageRed = (image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed);
                    averageBlue = (image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue);
                    averageGreen = (image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen);
                }
                    //Up edges
                else
                {
                    divide = 6;
                    averageRed = (image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed +
                                  image[i + 1][j - 1].rgbtRed + image[i][j - 1].rgbtRed);

                    averageBlue = (image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue +
                                   image[i + 1][j - 1].rgbtBlue + image[i][j - 1].rgbtBlue);

                    averageGreen = (image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen +
                                    image[i + 1][j - 1].rgbtGreen + image[i][j - 1].rgbtGreen);
                }
            }
                //Down
            else if (i + 1 > height - 1)
            {
                //Down left corner
                if (j - 1 < 0)
                {
                    divide = 4;
                    averageRed = (image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed);
                    averageBlue = (image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue);
                    averageGreen = (image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen);
                }
                    //Down right corner
                else if (j + 1 > width - 1)
                {
                    divide = 4;
                    averageRed = (image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed);
                    averageBlue = (image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue);
                    averageGreen = (image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen);
                }
                    //Down edges
                else
                {
                    divide = 6;
                    averageRed = (image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed +
                                  image[i - 1][j - 1].rgbtRed + image[i][j - 1].rgbtRed);

                    averageBlue = (image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue +
                                   image[i - 1][j - 1].rgbtBlue + image[i][j - 1].rgbtBlue);

                    averageGreen = (image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen +
                                    image[i - 1][j - 1].rgbtGreen + image[i][j - 1].rgbtGreen);
                }
            }
                //Right edges
            else if (j + 1 > width - 1)
            {
                divide = 6;
                averageRed = (image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed +
                              image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed);

                averageBlue = (image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue +
                               image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue);

                averageGreen = (image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen +
                                image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen);
            }
                //Left edges
            else if (j - 1 < 0)
            {
                divide = 6;
                averageRed = (image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed +
                              image[i + 1][j + 1].rgbtRed + image[i + 1][j].rgbtRed);

                averageBlue = (image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue +
                               image[i + 1][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue);

                averageGreen = (image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen +
                                image[i + 1][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen);
            }
                //Middle pixels
            else
            {
                divide = 9;
                averageRed = (image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed +
                              image[i + 1][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i][j - 1].rgbtRed +
                              image[i - 1][j - 1].rgbtRed);

                averageBlue = (image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue +
                               image[i + 1][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i][j - 1].rgbtBlue +
                               image[i - 1][j - 1].rgbtBlue);

                averageGreen = (image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen +
                                image[i + 1][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i][j - 1].rgbtGreen +
                                image[i - 1][j - 1].rgbtGreen);
            }
            //Round and divide floats
            temp1[i][j].rgbtRed = round(averageRed / divide);
            temp1[i][j].rgbtBlue = round(averageBlue / divide);
            temp1[i][j].rgbtGreen = round(averageGreen / divide);
        }
    }
    //Copy items of temp1 to image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp1[i][j];
        }
    }
    return;
}