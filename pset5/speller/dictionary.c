// Implements a dictionary's functionality

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

#include "dictionary.h"

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // eat the error message
    // error: unused parameter 'word'
    word++;
    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // open input file
    FILE *inptr = fopen(dictionary, "r");

    // check if something went wrong
    if (inptr == NULL)
    {
        fprintf(stderr, "93. Could not open %s.\n", dictionary);
        return 2;
    }

    // LENGTH is defined in dictionary.h
    // Maximum length for a word
    char word[LENGTH + 1];
    for (int i = 0; i < 46; i++)
    {
        // fill word array with zeros
        (word[i] = 0);
    }

    int index = 0;

    // read each character in dictionary
    // source: speller.c
    for (char c = fgetc(inptr); c != EOF; c = fgetc(inptr))
    {
        if (c != '\n'){
            // source: study.cs50.net/tries Kevin's video
            // tolower() requires <ctype.h>
            index = tolower(c) - 'a';
            if (c == '\'') index = 26;
            printf("58. %i ", index);
            // build a word
            word[index] = c;
            printf("%c\n", word[index]);
        }
    }
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    return false;
}