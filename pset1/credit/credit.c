#include <stdio.h>
#include <cs50.h>

int main(void)
{
    long number = get_long("Please enter your credit card number:\n");
    int digit = 0;
    long quotient = number;
    char array[20];
    int i = 0;
    char multiply = 0;
    char sum = 0;
    
    //the digits number
    while (quotient != 0)
    {
        array[i] = quotient % 10;
        quotient = quotient / 10;
        digit++;
        i++;
    }
   
    //inverse array
    for (i = 0; i < digit / 2; i++)
    {
        char temporary = array[i];
        array[i] = array[digit - 1 - i];
        array[digit - 1 - i] = temporary;
    }

    for (i = digit - 2; i >= 0; i -= 2)
    {
        multiply = array[i] * 2;
        if (multiply > 9)
        {
            multiply = multiply % 10 + multiply / 10;
            sum += multiply;

        }
        else
        {
            sum += multiply;
        }

    }
    
    for (i = digit - 1; i >= 0; i -= 2)
    {
        sum += array[i];
    }

    if (sum % 10 == 0)
    {
        if ((sum % 10 == 0) && digit == 15 && array[0] == 3 && (array[1] == 4 || array[1] == 7))
        {
            printf("AMEX\n");
        }
        else if ((sum % 10 == 0) && digit == 16 && array[0] == 5 && (array[1] == 1 || array[1] == 2 || array[1] == 3 || array[1] == 4
                 || array[1] == 5))
        {
            printf("MASTERCARD\n");
        }
        else if ((sum % 10 == 0) && (digit == 13 || digit == 16) && array[0] == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}