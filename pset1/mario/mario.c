#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int h = 0xFF; // height

    while (h < 1 || h > 8)
    {
        h = get_int("Please enter height between 1 to 8: ");
    }

 
    for (int i = 1; i <= h; i++)
    {
        for (int j = h - 1; j >= i; j--)
        {
            printf(" ");
        }

        for (int k = 1; k <= i; k++)
        {
            printf("#");
        }

        printf("  ");

        for (int k = 1; k <= i; k++)
        {
            printf("#");
        }

        printf("\n");
    }
}