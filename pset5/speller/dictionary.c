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
    // malloc space for a new node pointer
    struct node *p_node = NULL;
    p_node = (struct node *) malloc(sizeof(struct node));

    // malloc was successful and created new node
    if (p_node)
    {
        // set is_word to false
        p_node->is_word = false;

        for (int i = 0; i < 27; i++)
        {
            // fill the array with NULL
            p_node->children[i] = NULL;
        }
    }
    return p_node;
}

node *root_node;
int word_count = 0;
int word_index = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // eat the error message
    // error: unused parameter 'word'
    // word++;
    // return false;

        int len = strlen(word);
    // printf("50. %s passed in len == %d \n", word, len);

    // make a pointer to root
    node* parent = root_node;

    // source: Zamyla's walkthrough
    // traversing a trie
    // for each letter in input word
    for (int i = 0; i < len; i++)
    {
        if(isalpha(word[i]))
        {
            word_index = tolower(word[i])-'a';
            // printf("65. %c index == %d \n", word[i], word_index);

            if (parent->is_word){
                // printf("72. char is %c\n", word[i]);
                // go to corresponding element in children
                if (parent->children[word_index] == NULL)
                {
                    // if NULL word is misspelled
                    printf("79. %s is misspelled \n", word);
                    // return false;
                }

                // have children[i] point to it
                parent = parent->children[word_index];
            }

        }
        else
        {
            // index for '\''
            word_index = 26;
        }

        // once at end of input word
        // check if is_word is true
        return true;
    }

    // word not found in dictionary
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

            // build a word
            word[index] = c;

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
    return word_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    return true;
}