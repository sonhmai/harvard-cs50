// Implements a dictionary's functionality
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1;

// Hash table
node *table[N]; 

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // get hash of the input word
    unsigned int h = hash(word);
    // then traverse the linked list at dict[hash] and compare ignoring case
    node *list = table[h];
    while (list != NULL) {
        if (strcasecmp(list->word, word) == 0) {
            return true;
        }
        list = list->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    return 0;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *f = fopen(dictionary, "r");
    if (f == NULL) {
        return false;
    }
    char word[LENGTH + 1];
    int nValuesRead;
    unsigned int h;
    node *head;
    node *currentNode;

    while (1) {
        // TODO - create node and assign to hash table
        // TODO - in case of EOF, how to free mem?
        currentNode = malloc(sizeof(node));
        if (currentNode == NULL) {
            printf("Cannot allocate mem for currentNode");
            unload();
            return -1;
        }

        nValuesRead = fscanf(f, "%s", currentNode->word);
        if (nValuesRead == EOF) break;

        h = hash(currentNode->word);
        head = table[h];
        if (head == NULL) {
            currentNode->next = NULL;    
            table[h] = currentNode;
        }
        else {
            // push node to beginning of linked list to avoid traversing to end
            currentNode->next = head;
            table[h] = currentNode;
        }
    }
    fclose(f);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // One way is to keep a global var and increment it whenever a word is added
    // to the dict, then getting size takes O(1). However, here we implement
    // an O(n) approach which checks the dict everytime to get the size
    // because we are not sure the load() method is correct and I want to
    // practive traversing the dict.
    int count = 0;
    node *cursor;
    for (int i=0; i<N; i++) {
        cursor = table[i];
        while (cursor != NULL) {
            count++;
            cursor = cursor->next;
        }
    }
    return count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    node *cursor;
    node *temp;
    printf("\nDELETING\n");
    for (unsigned int i=0; i<N; i++) {
        cursor = table[i];
        while (cursor != NULL) {
            temp = cursor->next;
            free(cursor);
            cursor = temp;
        }
    }
    return true;
}
