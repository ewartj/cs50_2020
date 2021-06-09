// Implements a dictionary's functionality

#include <stdbool.h>
#include <stddef.h>
#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


#include "dictionary.h"

// Default dictionary
#define DICTIONARY "dictionaries/large"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table (this high number was chosen to make it comparable to the staff solution)
const unsigned int N = 250000;

// size (to be used in load)
int wordCount = 0;
node *head;
// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    // https://gist.github.com/yangrq1018/e769abd7489ea8f52351b30829796a15
    int len = strlen(word);
    char lowerWord[len + 1];
    for (int i = 0; i < len; i++)
    {
        lowerWord[i] = tolower(word[i]);
    }
    lowerWord[len] = '\0';

    int index = hash(lowerWord);


    if (table[index] == NULL)
    {
        return false;
    }

    else if (table[index] != NULL)
    {
        node *cursor = table[index];
        while (cursor != NULL)
        {
            if (strcasecmp(cursor->word, word) == 0)
            {
                return true;
            }
            else
            {
                cursor = cursor->next;
            }
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{

    // hash function from:
    // https://www.reddit.com/r/cs50/comments/1x6vc8/pset6_trie_vs_hashtable/
    unsigned int hash = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
        hash = (hash << 2) ^ word[i];
    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // load file into a dictionary
    // https://medium.com/@anthonycatantan/i-saw-the-light-my-experience-with-cs50-weeks-5-and-6-72c29a6230fb
    // setting up the environment

    //LOAD A DICTIONARY FILE
    FILE *file = fopen(dictionary, "r");

    if (file == NULL)
    {
        unload();
        return false;
    }

    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
    char word[LENGTH + 1];
    //read strings from file 1 at a time
    while (fscanf(file, "%s", word) != EOF)
    {

    // allocate space in memory for the node
        node *newNode = malloc(sizeof(node));
        if (newNode == NULL)
            {
                return false;
            }
        newNode->next = NULL;
        if (feof(file))
        {
            // hit end of file
            free(newNode);
            break;
        }
        // get hash of word for index
        int index = hash(word);

        // Copy word into node
        strcpy(newNode->word, word);

        //inserting the word into the hash table/ listed list
        if(table[index] == NULL)
            {
                table[index] = newNode;
                wordCount ++;
            }
        else
            {
                newNode->next = table[index];
                table[index] = newNode;
                wordCount ++;
            }
    }
    fclose(file);
    return true;
}


// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    // A count is made as the dictionary is built and this is passed into size as the total size
    // needs to count all the elements in the dictionary
    // for (i in dict); count++
    //ths could be done by counting all words as they are loaded
    if (wordCount > 0)
    {
        return wordCount;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Modified from:
    // a copy of https://stackoverflow.com/questions/61266621/spell-checker-program-check-function-speller-cs50
    for (int i = 0; i <N; i++)
    {
        node* cursor = table[i];
        while (cursor != NULL)
        {
            // temp vairable to keep the pointers
            node* temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }
    return true;
}


/*

Additional references:

//https://stackoverflow.com/questions/57192759/cs50-speller-all-words-misspelled-debug-shows-cursor-to-be-null-why

*/