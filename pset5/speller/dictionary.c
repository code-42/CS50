// Implements a dictionary's functionality


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

#include "dictionary.h"

// source https://study.cs50.net/tries
typedef struct node
{
    // marker for end of word
    bool is_word;

    // pointers to other nodes
    struct node* children[27];
}
node;

struct node* newNode()
{
    struct node *p_node = NULL;
    p_node = (struct node *) malloc(sizeof(struct node));

    if (p_node)
    {
        p_node->is_word = false;

        // fill the array with NULL
        for (int i = 0; i < 27; i++)
        {
            p_node->children[i] = NULL;
        }
    }
    return p_node;
}

node *root_node;
int word_count = 0;

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

    // set a pointer to root so I can get back to it
    // struct node *root_node;
    root_node = newNode();

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
        // make a pointer to root
        node* parent = root_node;
        if (c != '\n'){
            // source: study.cs50.net/tries Kevin's video
            // tolower() requires <ctype.h>
            index = tolower(c) - 'a';
            if (c == '\'') index = 26;
            // printf("58. %i ", index);

            // build a word
            word[index] = c;
            // printf("%c\n", word[index]);

            // source: Zamyla's walkthrough
            // check the value at children[i]
            if (parent->children[index] == NULL)
            {
                // if NULL, malloc a new node
                parent->children[index] = newNode();
            }
            // have children[i] point to it
            parent = parent->children[index];
            index++;
        }
        // if at end of word, set is_word to true
        parent->is_word = true;
        word_count++;
    }
    fclose(inptr);
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