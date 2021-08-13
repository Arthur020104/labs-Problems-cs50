#include "helpers.h"
#include <math.h>

int calcsepia(double ori[3], float rgbt[3]);
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height - 1; i++)
    {
        for(int j = 0; j < width - 1; j++)
        {
            double rgb = 0;
            rgb += image[i][j].rgbtRed;
            rgb += image[i][j].rgbtGreen;
            rgb += image[i][j].rgbtBlue;
            rgb /= 3;
            rgb = round(rgb);
            image[i][j].rgbtRed = rgb;
            image[i][j].rgbtGreen = rgb;
            image[i][j].rgbtBlue = rgb;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height - 1; i++)
    {
        for(int j = 0; j < width - 1; j++)
        {
            float rgb[3];
            double ori[]={image[i][j].rgbtRed, image[i][j].rgbtGreen, image[i][j].rgbtBlue};
            rgb[0] = (0.393 * ori[0]);
            rgb[0] += (0.769 * ori[1]);
            rgb[0] += (0.189 * ori[2]);

            rgb[1] = (0.349 * ori[0]);
            rgb[1] += (0.686 * ori[1]);
            rgb[1] += (0.168 * ori[2]);

            rgb[2] = (0.272 * ori[0]);
            rgb[2] += (0.534 * ori[1]);
            rgb[2] += (0.131 * ori[2]);

            for(int f = 0; f < 3; f++)
                {
                    rgb[f] = round(rgb[f]);
                    if(rgb[f] > 255)
                    {
                        rgb[f] = 255;
                    }
                }

            image[i][j].rgbtRed = rgb[0];
            image[i][j].rgbtGreen = rgb[1];
            image[i][j].rgbtBlue = rgb[2];
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height - 1; i++)
    {
        int jota = width - 1;
        RGBTRIPLE temp;
        for(int j = 0; j < width - 1; j++)
        {
            image[i][j] = image[i][width - j - 1];
        }
    }
    return;
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height - 1; i++)
    {
        for(int j = 0; j < width - 1; j++)
        {
            double rgb[] ={0 , 0 , 0};
            int arg = 0;
            int divisor = 0;
        top:
            for(int f = -1; f < 2; f++)
            {
                for(int h = -1; h < 2; h++)
                {
                    if(i != 0 && j != 0)
                    {
                        if(arg == 1)
                        {
                            image[i + f][j + h].rgbtRed = rgb[0];
                            image[i + f][j + h].rgbtGreen = rgb[1];
                            image[i + f][j + h].rgbtBlue = rgb[2];
                        }
                        if((image[i + f][j + h].rgbtRed > 0 ||image[i + f][j + h].rgbtGreen > 0|| image[i + f][j + h].rgbtBlue > 0) && arg == 0)
                        {
                            rgb[0] += image[i + f][j + h].rgbtRed;
                            rgb[1] += image[i + f][j + h].rgbtGreen;
                            rgb[2] += image[i + f][j + h].rgbtBlue;
                            divisor++;
                        }
                    }
                }
            rgb[0] /= divisor;
            rgb[1] /= divisor;
            rgb[2] /= divisor;
            rgb[0] = round(rgb[0]);
            rgb[1] = round(rgb[1]);
            rgb[2] = round(rgb[2]);
            for(int w = 0; w < 3; w++)
                {
                    rgb[w] = round(rgb[w]);
                    if(rgb[w] > 255)
                    {
                        rgb[w] = 255;
                    }
                }
            arg += 1;
            if(arg == 1)
                {
                goto top;
                }
            }
        }
    }
    return;
}

