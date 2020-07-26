// encrypting messages using Caesar’s cipher

#include<cs50.h>
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>


int main(int argc, string argv[])
{
    
    if (argc == 1)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        printf("%lu\n", strlen(argv[1]));
        return 1;
    }
    else
    {
        //checks if there is non alphabetic character in command line argument
        int i = 0;
        while (*(argv[1] + i))
        {
            if (!isalpha(*(argv[1] + i)))
            {
                printf("not an alphabetic character");
                printf("%c\n", *(argv[1] + i));
                return 1;
            }
            i++;
        }
        
        //checks whether all letters are used once
        for (int k = 0; k < strlen(argv[1]) - 1; k++)
        {
            for (int j = k + 1; j < strlen(argv[1]); j++)
            {
                if ((*(argv[1] + k) == *(argv[1] + j)) || (*(argv[1] + k) == *(argv[1] + j) + 0x20) || (*(argv[1] + k) == *(argv[1] + j) - 0x20))
                {
                    return 1;
                }
                
            }
        }
     
    }
    
    char *text = get_string("plaintext: ");
    
    int m = 0;
    int index = 0;
    
    while (*(text + m))
    {
        if (isalpha(*(text + m)))
        {
            if (isupper(*(text + m)))
            {
                index = *(text + m) - 65;
                if (isupper(argv[1][index]))
                {
                    *(text + m) = argv[1][index];
                }
                else
                {
                    *(text + m) = argv[1][index] - 0x20;
                }
            }
            else
            {
                index = *(text + m) - 97;
                if (isupper(argv[1][index]))
                {
                    *(text + m) = argv[1][index] + 0x20;
                    
                }
                else
                {
                    *(text + m) = argv[1][index];
                }
            }
        }
        m++;
    }

    printf("ciphertext: %s\n", text);
    

    
    return 0;
}
