#include <stdio.h>
#include <cs50.h>
#include<string.h>
#include<math.h>

// Implement a program that computes the approximate grade level needed to comprehend some text

int main(void)
{
    char *text = get_string("Text: ");
    int i = 0;
    char count_spacebar = 0;
    char count_word = 0;
    int count_letter = 0;
    char count_sentence = 0;
    float L, S = 0;
    int index = 0;
  
    while (*(text + i))
    {

        char temp = *(text + i);

        if ((temp >= 0x61 && temp <= 0x7A) || (temp >= 0x41 && temp <= 0x6A))
        {
            count_letter++;
        }

        if (temp == 0x20)
        {
            count_spacebar++;
        }
        
        if (temp == 0x21 || temp == 0x2E || temp == 0x3F) // 0x21: ! 0x2E: . 0x3F: ?
        {
            count_sentence++;
        }

        i++;

    }
    
    count_word = count_spacebar + 1;
    L = (float)(100 * count_letter) / count_word; //  avg of letters per 100 words 
    S = (float)(100 * count_sentence) / count_word; // avg of sentences per 100 words 
    index =  round(0.0588 * L - 0.296 * S - 15.8); // grade level, Coleman-Liau formula
   
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %d\n", index);
    }
  




}