// Implements a dictionary's functionality

#include <stdbool.h>

#include "dictionary.h"

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;
unsigned int word_count = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    unsigned int i = 0;

    i = hash(word);
 
    for (node *tmp = table[i]; tmp != NULL; tmp = tmp->next)
    {
        int compare = 0;
        if(strcasecmp(tmp->word, word)==0)
        {
            return true;
        }

    }
    
    
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    
    int index = *word - 0x61;
    if(index >= 0 && index <= N)
    {
        return index;
    }
    
    return index + 0x20;

    // TODO
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open input file
    char word[LENGTH];
    node *n = NULL;
    unsigned int index= 0;
    FILE *inptr = fopen(dictionary, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", dictionary);
        return 1;
    }

    while (fscanf(inptr, "%s", word) != EOF)
    {

        index = hash(word);
  
        n = malloc(sizeof(node));
        if(n == NULL)
        {
            return 1;
        }
        strcpy(n->word, word);
        n->next = table[index];
        table[index] = n;
  

    }
    
    
    // Check whether there was an error
    if (ferror(inptr))
    {
        fclose(inptr);
        printf("Error reading %s.\n", dictionary);
        unload();
        return 1;
    }

    // Close text
    fclose(inptr);

    // TODO
    return true;
}


// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    
    for(int i=0 ; i < N; i++)
    {

        for (node *tmp = table[i]; tmp != NULL; tmp = tmp->next)
        {
            word_count++;

        }

    }
;
    // TODO
    return word_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    unsigned int free_count = 0;

    for(int i = 0; i < N; i++)
    {
        node *list = table[i];
        while (list != NULL)
        {
            node *tmp = list->next;
            free(list);
            list = tmp;
            free_count++;
        }
    
    }

    if(free_count == word_count)
    {
       
       return true;
    }


    // TODO
    return false;
}




