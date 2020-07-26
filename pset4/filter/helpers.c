#include "helpers.h"
#include<stdio.h>
#include<math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE  one_pixel;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            one_pixel = *(*(image + i) + j);
            int avg = round( (one_pixel.rgbtBlue +  one_pixel.rgbtGreen +  one_pixel.rgbtRed) / 3.0);
            (*(*(image + i) + j)).rgbtRed = avg;
            (*(image + i) + j) -> rgbtGreen = avg;
            (*(image + i) + j) -> rgbtBlue = avg;

        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    /* sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
  sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
  sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue*/


    RGBTRIPLE  one_pixel;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            one_pixel = *(*(image+i)+j);
            int sepiaRed = round(0.393 * one_pixel.rgbtRed + 0.769 * one_pixel.rgbtGreen + 0.189 * one_pixel.rgbtBlue);
            int sepiaGreen = round( 0.349 * one_pixel.rgbtRed + 0.686 * one_pixel.rgbtGreen + 0.168 * one_pixel.rgbtBlue);
            int sepiaBlue = round(0.272 * one_pixel.rgbtRed + 0.534 * one_pixel.rgbtGreen + 0.131 * one_pixel.rgbtBlue);

            if (sepiaRed > 255)
            {
                (*(image + i) + j) -> rgbtRed = 255;
            }
            else
            {
                (*(image + i) + j) -> rgbtRed = sepiaRed;
            }
            if (sepiaGreen > 255)
            {
                (*(image +i ) + j) -> rgbtGreen = 255;
            }
            else
            {
                (*(image + i) + j) -> rgbtGreen = sepiaGreen;
            }
            if(sepiaBlue > 255)
            {
                (*(image + i) + j) -> rgbtBlue = 255;
            }
            else
            {
                (*(image +i ) + j) -> rgbtBlue = sepiaBlue;
            }
        }
    }


    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            temp = *(*(image + i) + width - 1 - j);
            *(*(image + i) + width - 1 - j) = *(*(image + i) + j);
            *(*(image + i) + j) = temp;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    int blur_red = 0;
    int blur_green = 0;
    int blur_blue = 0;


    RGBTRIPLE copy_image[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int pixel_count = 0;
            for (int k = -1; k <= 1; k++)
            {
                int new_i = i + k;
                for(int l = -1; l <= 1; l++)
                {
                    int new_j = j + l;

                    if(new_i >= 0 && new_i <= height-1 && new_j >= 0 && new_j <= width - 1)
                    {
                        blur_red += (*(image + new_i) + new_j) -> rgbtRed;
                        blur_green += (*(image + new_i) + new_j) -> rgbtGreen;
                        blur_blue += (*(image + new_i) + new_j) -> rgbtBlue;
                        pixel_count++;
                    }

                }

            }

            blur_red =  round((float)blur_red / pixel_count);
            blur_green =  round((float)blur_green / pixel_count);
            blur_blue =  round((float)blur_blue / pixel_count);

            if (blur_red > 255)
            {
                (*(copy_image + i) + j) -> rgbtRed = 255;
            }
            else
            {
                (*(copy_image + i) + j) -> rgbtRed = blur_red;
            }
            if (blur_green > 255)
            {
                (*(copy_image + i) + j) -> rgbtGreen = 255;
            }
            else
            {
                (*(copy_image + i) + j) -> rgbtGreen = blur_green;
            }
            if (blur_blue > 255)
            {
                (*(copy_image + i) + j) -> rgbtBlue = 255;
            }
            else
            {
                (*(copy_image + i) + j) -> rgbtBlue = blur_blue;
            }

            blur_red=0;
            blur_green=0;
            blur_blue=0;

        }
    }

    for (int i=0;i<height;i++)
        {
            for(int j=0;j<width;j++)
            {
                (*(image + i) + j) -> rgbtRed = (*(copy_image + i) + j) -> rgbtRed;
                (*(image + i) + j) -> rgbtGreen = (*(copy_image + i) + j) -> rgbtGreen;
                (*(image + i) + j) -> rgbtBlue = (*(copy_image + i) + j) -> rgbtBlue;
            }

        }


    return;
}



