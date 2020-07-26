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
            int avg = round((one_pixel.rgbtBlue +  one_pixel.rgbtGreen +  one_pixel.rgbtRed) / 3.0);
            (*(image + i) + j) -> rgbtRed = avg;
            (*(image + i) + j) -> rgbtGreen = avg;
            (*(image + i) + j) -> rgbtBlue = avg;
            
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
                for (int l = -1; l <= 1; l++)
                {
                    int new_j = j + l;
                    
                    if (new_i >= 0 && new_i <= height - 1 && new_j >= 0 && new_j <= width - 1)
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
            
            blur_red = 0;
            blur_green = 0;
            blur_blue = 0;

        }
    }
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            (*(image + i) + j) -> rgbtRed = (*(copy_image + i) + j) -> rgbtRed;
            (*(image + i) + j) -> rgbtGreen = (*(copy_image + i) + j) -> rgbtGreen;
            (*(image + i) + j) -> rgbtBlue = (*(copy_image + i) + j) -> rgbtBlue;
        }
        
    }
    
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int gx_matrix[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy_matrix[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    int sum_redx = 0;
    int sum_greenx = 0;
    int sum_bluex = 0;
    int sum_redy = 0;
    int sum_greeny = 0;
    int sum_bluey = 0;
    
    RGBTRIPLE copy_image[height][width];
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int row = 0; //gx and gy matrix row
           
            for (int k = -1; k <= 1; k++)
            {
                int new_i = i + k;
                int column = 0; //gx and gy matrix column
                for (int l = -1; l <= 1; l++)
                {
                    int new_j = j + l;
                    if (new_i >= 0 && new_i <= height - 1 && new_j >= 0 && new_j <= width - 1)
                    {
                        sum_redx += ((*(image + new_i) + new_j) -> rgbtRed) * gx_matrix[row][column];
                        sum_greenx += ((*(image + new_i) + new_j) -> rgbtGreen) * gx_matrix[row][column];
                        sum_bluex += ((*(image + new_i) + new_j) -> rgbtBlue) * gx_matrix[row][column];
                        
                        sum_redy += ((*(image + new_i) + new_j) -> rgbtRed) * gy_matrix[row][column];
                        sum_greeny += ((*(image + new_i) + new_j) -> rgbtGreen) * gy_matrix[row][column];
                        sum_bluey += ((*(image + new_i) + new_j) -> rgbtBlue) * gy_matrix[row][column];
                        
              
                    }
                    column++;
                }
                
                row++;
                
            }
            
            
            float final_red = round(sqrt(pow(sum_redx, 2) + pow(sum_redy, 2)));
            float final_green = round(sqrt(pow(sum_greenx, 2) + pow(sum_greeny, 2)));
            float final_blue = round(sqrt(pow(sum_bluex, 2) + pow(sum_bluey, 2)));
            
            if (final_red > 255)
            {
                (*(copy_image + i) + j) -> rgbtRed = 255;
            }
            else
            {
                (*(copy_image + i) + j) -> rgbtRed = final_red;
            }
            if (final_green > 255)
            {
                (*(copy_image + i) + j) -> rgbtGreen = 255;
            }
            else
            {
                (*(copy_image + i) + j) -> rgbtGreen = final_green;
            }
            if (final_blue > 255)
            {
                (*(copy_image + i) + j) -> rgbtBlue = 255;
            }
            else
            {
                (*(copy_image + i) + j) -> rgbtBlue = final_blue;
            }
            
            sum_redx = 0;
            sum_greenx = 0;
            sum_bluex = 0;
            sum_redy = 0;
            sum_greeny = 0;
            sum_bluey = 0;
             
        }
        
    }
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            (*(image + i) + j) -> rgbtRed = (*(copy_image + i) + j) -> rgbtRed;
            (*(image + i) + j) -> rgbtGreen = (*(copy_image + i) + j) -> rgbtGreen;
            (*(image + i) + j) -> rgbtBlue = (*(copy_image + i) + j) -> rgbtBlue;
        }
        
    }
    
   
    return;
}










