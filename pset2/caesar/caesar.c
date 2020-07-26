// encrypting messages using Caesar’s cipher

#include <cs50.h>
#include <stdio.h>
#include<ctype.h>
#include<stdlib.h>

int main(int argc, string argv[])
{
    int i = 0;
    unsigned int k = 0;

    if (argc == 1)
    {
        printf("missing command-line argument\n");
        return 1;
    }

    else if (argc != 2)
    {
        printf("more than one command-line argument\n");
        return 1;
    }

    else
    {
        while (*(argv[1] + i))
        {
            if (!isdigit(*(argv[1] + i)))
            {
                printf("Usage: ./caesar key");
                printf("%c\n", *(argv[1] + i));
                return 1;
            }
            i++;
        }

        k = atoi(argv[1]);
    }

    char *text = get_string("plaintext: ");

    int j = 0;

    while (*(text + j))
    {
        if (*(text + j) >= 0x41 && *(text + j) <= 0x5A)
        {
            *(text + j) = ((*(text + j) - 65 + k) % 26) + 65;
        }

        else if (*(text + j) >= 0x61 && *(text + j) <= 0x7A)
        {
            *(text + j) = ((*(text + j) - 97 + k) % 26) + 97;
        }

        j++;
    }

    printf("ciphertext: %s\n", text);

    return 0;
}
