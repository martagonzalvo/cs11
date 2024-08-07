/*
 * FILE: memcheck.c
 *
 *       Simple-minded memory leak checker for C programs.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMCHECK_C
#include "memcheck.h"

#define DEBUG 0

/*
 * Definition of data structure to keep memory allocation information.
 */

typedef
struct _mem_node
{
    void   *addr;       /* Address of allocated memory.                   */
    size_t  nbytes;     /* Number of bytes allocated.                     */
    char   *filename;   /* Name of file where allocation occurred.        */
    int     lineno;     /* Line number of file where allocation occurred. */
    struct _mem_node *next;     /* Next node in linked list. */
}
mem_node;


/*
 * Function prototypes.
 */

void        allocate_mem_node(void *addr, size_t nbytes,
                              char *filename, int lineno);
void        free_mem_node(mem_node *n);
void        free_mem_node_and_adjust_pool(mem_node *n);
void        free_all_mem_nodes(void);
mem_node   *find_node(void *addr);
void       *checked_malloc_fn(size_t size, char *filename, int lineno);
void       *checked_calloc_fn(size_t nmemb, size_t size,
                              char *filename, int lineno);
void        checked_free_fn(void *ptr, char *filename, int lineno);
void        print_memory_leaks(void);
void        dump_pool(void);


/*
 * Initialize the memory pool linked list as a global variable.
 */

mem_node *pool = NULL;


/**********************************************************************
 *
 * Low-level functions for managing the memory pool linked list.
 *
 **********************************************************************/

/*
 * Allocate a memory node, set its values and link it into the memory
 * pool linked list.
 */

void
allocate_mem_node(void *addr, size_t nbytes, char *filename, int lineno)
{
    mem_node *n;
    char *fn;

    /* Create the node and set its fields. */
    n = (mem_node *)malloc(sizeof(mem_node));

    if (n == NULL)
    {
        fprintf(stderr, "ERROR: memory allocation failed!  Aborting...\n");
        exit(1);
    }

#if DEBUG == 1
    fprintf(stderr, "Allocating %d bytes of memory at %p\n",
            nbytes, addr);
#endif

    /* Copy the filename, which is statically allocated (I think). */
    fn = (char *)malloc((strlen(filename) + 1) * sizeof(char));
    strcpy(fn, filename);

    n->addr     = addr;
    n->nbytes   = nbytes;
    n->filename = fn;
    n->lineno   = lineno;

    /* Add it to the front of the memory pool. */
    n->next = pool;
    pool    = n;
}


/*
 * Free a memory node from the pool.
 */

void
free_mem_node(mem_node *n)
{
    if (n != NULL)
    {
        if (n->addr == NULL)
        {
            fprintf(stderr, "ERROR: invalid node at: %p\n", n->addr);
            return;
        }

#if DEBUG == 1
        fprintf(stderr, "Freeing memory at %p\n", n->addr);
#endif

        free(n->addr);
        free(n->filename);
        free(n);
    }
}


/*
 * Free a memory node from the pool.  Adjust the 'next' pointer of the
 * previous node (if any) to skip over this node.
 */

void
free_mem_node_and_adjust_pool(mem_node *n)
{
    mem_node *p, *prev;

    prev = NULL;

    for (p = pool; p != NULL; p = p->next)
    {
        if (p->addr == n->addr)
        {
            if (prev == NULL)
            {
                /* The node to be removed is the first node. */
                pool = p->next;
                free_mem_node(p);
                break;   /* Nothing left to do. */
            }
            else
            {
                /*
                 * The node is in the interior of the memory pool
                 * linked list.  Adjust the 'next' pointer of the
                 * previous node and free the node.
                 */
                prev->next = p->next;
                free_mem_node(p);
                break;   /* Nothing left to do. */
            }
        }
        else
        {
            prev = p;
        }
    }
}


/*
 * Free all the memory nodes from the pool.
 */

void
free_all_mem_nodes(void)
{
    mem_node *n, *next;

    n = pool;

    while (n != NULL)
    {
        next = n->next;
        free_mem_node(n);
        n = next;
    }
}


/*
 * Return the node that corresponds to the address 'addr', or NULL if
 * the address isn't found.
 */

mem_node *
find_node(void *addr)
{
    mem_node *n;

    for (n = pool; n != NULL; n = n->next)
    {
        if (n->addr == addr)
        {
            return n;
        }
    }

    return NULL;
}


/*
 * A debugging function to print the contents of the memory pool
 * linked list.
 */

void
dump_pool(void)
{
    mem_node *n;

    for (n = pool; n != NULL; n = n->next)
    {
        fprintf(stderr, "NODE --------\n");
        fprintf(stderr, "location: %p\n", (void *)n);
        fprintf(stderr, "addr: %p\n", n->addr);
        fprintf(stderr, "nbytes: %d\n", (int)n->nbytes);
        fprintf(stderr, "filename: %s\n", n->filename);
        fprintf(stderr, "line number: %d\n", n->lineno);
        fprintf(stderr, "next: %p\n", (void *)n->next);
        fprintf(stderr, "\n");
    }
}


/**********************************************************************
 *
 * User-level functions.
 *
 * NOTE: Normally, the user will not use these functions, but will
 *       use 'malloc' and 'calloc' wrappers defined in "memcheck.h".
 *
 **********************************************************************/


/*
 * Allocate 'size' bytes of memory.  Also add the address, filename, and line
 * number as a new node in the memory pool linked list.
 */

void *
checked_malloc_fn(size_t size, char *filename, int lineno)
{
    void *mem;

    mem = malloc(size);

    if (mem == NULL)
    {
        fprintf(stderr, "ERROR: memory allocation failed!  Aborting...\n");
        exit(1);
    }

    allocate_mem_node(mem, size, filename, lineno);
    return mem;
}


/*
 * This function is the same as 'checked_malloc' except that it has
 * a different signature (corresponding to 'calloc' in the first two
 * arguments) and zeroes out all the allocated memory.
 */

void *
checked_calloc_fn(size_t nmemb, size_t size, char *filename, int lineno)
{
    void *mem;

    mem = calloc(nmemb, size);

    if (mem == NULL)
    {
        fprintf(stderr, "ERROR: memory allocation failed!  Aborting...\n");
        exit(1);
    }

    allocate_mem_node(mem, (nmemb * size), filename, lineno);
    return mem;
}


/*
 * Free a pointer that was previously allocated by 'checked_malloc()'.  If
 * the memory being freed is not found in the memory pool, print an error
 * message and abort.
 */

void
checked_free_fn(void *ptr, char *filename, int lineno)
{
    mem_node *n = find_node(ptr);

    if (n == NULL)
    {
        fprintf(stderr,
                "ERROR: invalid attempt to free unallocated memory at %p "
                "in file: %s, line: %d\n", ptr, filename, lineno);
        fprintf(stderr, "Aborting...\n");
        free_all_mem_nodes();
        exit(1);
    }
    else
    {
        free_mem_node_and_adjust_pool(n);
    }
}


/*
 * This function is intended to be called at the end of a program only.
 * It goes through the memory pool node-by-node and prints out information
 * on the contents of the node.  Any nodes that exist at the end of the
 * program represent leaked memory.
 */

void
print_memory_leaks(void)
{
    mem_node *n;

    for (n = pool; n != NULL; n = n->next)
    {
        fprintf(stderr,
                "Memory leak: %d bytes allocated at %p in "
                "file: %s, line: %d.\n",
                (int)n->nbytes, n->addr, n->filename, n->lineno);
    }

    free_all_mem_nodes();
}

