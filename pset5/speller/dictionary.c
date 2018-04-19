// usage: ./speller dictionaries/small texts/cat.txt
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

struct node* newNode(void)
{
    // malloc space for a new node
    struct node *p_node = NULL;
    p_node = (struct node *) malloc(sizeof(struct node));

    if (p_node != NULL)
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
    int len = strlen(word);
    int index = 0;

    // make a pointer to root
    node* parent = root_node;

    // source: Zamyla's walkthrough
    // traversing a trie
    // for each letter in input word
    for (int i = 0; i < len; i++)
    {
        if (word[i] == '\'')
        {
            // index for '\''
            index = 26;
            if (parent->children[index] == NULL)
            {
                // if NULL, word is misspelled or not in dictionary
                return false;
            }
            else
            {
                parent = parent->children[index];
            }
        }
        else // its alpha
        {
            // index = tolower(word[i]) - 'a';
            if (parent->children[tolower(word[i]) - 'a'] == NULL)
            {
                return false;
            }
            else
            {
                // have children[i] point to it
                parent = parent->children[tolower(word[i]) - 'a'];
            }
        }
    }

    // word found in dictionary
    if(parent->is_word) return true;

    // word not found
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
    char word[47];

    // read each character in dictionary
    // source: speller.c
    // for (char c = fgetc(inptr); c != EOF; c = fgetc(inptr))
    while(fgets(word, sizeof(word), inptr) != NULL)
    {
        int index = 0;
        // make a pointer to root
        node* parent = root_node;
        // if (c != '\n')
        while (word[index] != '\n')
        {
            // source: study.cs50.net/tries Kevin's video
            // tolower() requires <ctype.h>
            if (word[index] == '\'')
            {
                // index = 26;
                // source: Zamyla's walkthrough
                // check the value at children[i]
                if (parent->children[26] == NULL)
                {
                    // if NULL, malloc a new node
                    parent->children[26] = newNode();
                }
                // have children[i] point to it
                parent = parent->children[26];
            }
            else
            {
                if (parent->children[word[index] - 'a'] == NULL)
                {
                    parent->children[word[index] - 'a'] = newNode();
                }
                parent = parent->children[word[index] - 'a'];
            }
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
    // source: speller.c line 147
    return word_count;
}

// Deletes trie from the bottom up
void delete_node(node* a_node)
{
    // if no node return
    if(!a_node)
    {
        return;
    }

    // travel to lowest possible node
    for (int i = 0; i < 27; i++)
    {
        // free all pointers in children
       delete_node(a_node->children[i]);
    }

    // backtrack upwards, freeing all elements
    free(a_node);
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    delete_node(root_node);
    return true;
}

