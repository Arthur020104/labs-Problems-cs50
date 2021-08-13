#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <strings.h>
#include <string.h>
#include "dictionary.h"

typedef uint8_t BYTE;
// Representa um node um uma hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 17576;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int valuehash = hash(word);

    for(node *tmp = table[valuehash]; tmp != NULL; tmp = tmp->next)
    {
        if(strcasecmp(tmp->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int a = 0;
    for(int i = 0; i < 3; i++)
        {
            a += tolower(word[i]);
            if(a >= 97 && a <= 122)
            {
                a -= 97;
                if(i < 2 && a != 0)
                {
                    a *= 26;
                    a -= 1;
                }
            }
        }
    if(a > -1 && a < N - 1)
    {
        return a;
    }
    return 0;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    char word[LENGTH + 1];
    FILE *file = fopen(dictionary, "r");
    if(file == NULL)
    {
        return false;
    }
    do
    {
        fscanf(file, "%s", word);
        node *n = malloc(sizeof(node));
        if(n == NULL)
        {
        return false;
        }
        
        strcpy(n->word, word);
        int hashh = hash(n->word);
        n->next = NULL;
        if(table[hashh] == NULL)
        {
        table[hashh] = n;
        }
        else if(table[hashh] != NULL)//
        {
            n->next = table[hashh];
            table[hashh] = n;
        }
    }
    while(fscanf(file, "%s", word) != EOF);

    fclose(file);
    return true;

}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    int size = 0;
    for(int i = 0; i < N - 1; i++)
    {
        if(table[i] == NULL)
        {
            size += 0;
        }
        else if(table[i] != NULL)
        {
            size += 1;
            for(node *tmp = table[i]; tmp != NULL; tmp = tmp->next)
            {
                size += 1;
            }
        }
    }
    return size;
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    int liberou = 0;
    for(int i = 0; i < N - 1; i++)
    {
        liberou++;
        node *libera;
        for(node *tmp = table[i]; tmp != NULL; tmp = libera)
        {
            libera = tmp->next;
            free(tmp);
        }
    }
    if(liberou == N - 1)
    {
        return true;
    }

    return false;
}
