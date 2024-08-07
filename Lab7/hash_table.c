/*
 * CS 11, C Track, lab 7
 *
 * FILE: hash_table.c
 *     Implementation of the hash table functionality.
 *
 */

/*
 * Include the declaration of the hash table data structures
 * and the function prototypes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include "memcheck.h"


/*** Hash function. ***/

int hash(char *s)
{
    int i;
    int sum;
    int index;

    /* Summing over values of all characters in string key. */
    sum = 0;
    i = 0;
    while (s && s[i])
    {
        sum += s[i++];
    }

    /* 
     * Taking sum modulo 128 (length of the hash table), to get the index
     * between 0 and 127. 
     */
    index = sum % NSLOTS;

    return index;
}


/*** Linked list utilities. ***/

/* Create a single node. */
node *create_node(char *key, int value)
{
    node *new_node;

    new_node = (node *) malloc(sizeof(node));

    /* Checking memorry allocation did not fail. */
    if (new_node == NULL)
    {
        fprintf(stderr, "Error! Memory allocation failed!\n");
        exit(1);
    }

    new_node->key = key; 
    new_node->value = value;
    new_node->next = NULL;

    return new_node;
}


/* Free all the nodes of a linked list. */
void free_list(node *list)
{
    node *curr;
    node *temp;

    curr = list;

    while (curr != NULL)
    {
        temp = curr->next;
        free(curr->key);
        free(curr);
        curr = temp;
    }
}


/*** Hash table utilities. ***/

/* Create a new hash table. */
hash_table *create_hash_table()
{
    hash_table *ht;

    ht = (hash_table *) malloc(sizeof(hash_table));
    /* Checking memorry allocation did not fail. */
    if (ht == NULL)
    {
        fprintf(stderr, "Error! Memory allocation failed!\n");
        exit(1);
    }

    /* Creating the node pointer array in the hash table structure. */
    ht->slot = (node **) malloc(sizeof(node)*NSLOTS);
    /* Checking memorry allocation did not fail. */
    if (ht->slot == NULL)
    {
        fprintf(stderr, "Error! Memory allocation failed!\n");
        exit(1);
    }
    
    return ht;
}


/* Free a hash table. */
void free_hash_table(hash_table *ht)
{
    int i;

    /* 
     * Using `free_list` function to free each linked list in every position
     * of the hash table.
     */
    for(i = 0; i < NSLOTS; i++)
    {
        free_list(ht->slot[i]);
    }
    free(ht->slot);
    free(ht);
}


/*
 * Look for a key in the hash table.  Return 0 if not found.
 * If it is found return the associated value.
 */
int get_value(hash_table *ht, char *key)
{
    int index;
    node *curr;

    index = hash(key);
    curr = ht->slot[index];

    while (curr !=NULL)
    {
        if (strcmp(curr->key, key) == 0)
        {
            return curr->value;
        }
        curr = curr->next;
    }
    return 0;
}


/*
 * Set the value stored at a key.  If the key is not in the table,
 * create a new node and set the value to 'value'.  Note that this
 * function alters the hash table that was passed to it.
 */
void set_value(hash_table *ht, char *key, int value)
{
    int index;
    node *curr;
    node *start;
    node *new;

    /* 
     * Find hash value of key and look at all the keys in the linked 
     * list at the slot. 
     */
    index = hash(key);
    start = ht->slot[index];

    
    curr = start;
    while (curr != NULL)
    {
        /* If key exists, change the value to `value` and return. */
        if (strcmp(curr->key, key) == 0)
        {
            curr->value = value;
            free(key);
            return;
        }
        curr = curr->next;
    }

    /* 
     * Create a new node at the beginning of the linked list if key did
     *  not exist. 
     */
    new = create_node(key, value);
    new->next = start;

    ht->slot[index] = new;
}


/* Print out the contents of the hash table as key/value pairs. */
void print_hash_table(hash_table *ht)
{
    node *curr;
    int i;

    /* Loop through each slot in the hash table. */
    for (i = 0; i < NSLOTS; i++)
    {
        /* Print each key/value pair in the linked list in the slot. */
        curr = ht->slot[i];
        while (curr != NULL)
        {
            printf("%s %d\n", curr->key, curr->value);
            curr = curr-> next;
        }
    }
}


