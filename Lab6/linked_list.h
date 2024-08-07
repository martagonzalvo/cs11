/*
 * FILE: linked_list.h
 */

#ifndef LINKED_LIST_H
#define LINKED_LIST_H


/*
 * Declaration of the 'node' struct.  An individual list element is
 * often called a "node".  A linked list is a series of nodes linked
 * together through their 'next' pointers.
 */

typedef struct _node
{
  int data;           /* each node stores a number */
  struct _node *next; /* and a pointer to the next node in the chain */
} node;


/* Create a single node and link it to the node called 'n'. */
node *create_node(int data, node *n);

/* Free all the nodes of a linked list. */
void free_list(node *list);

/* Return a copy of a list. */
node *copy_list(node *list);

/* Append two lists non-destructively.  The input lists are not altered. */
node *append_lists(node *list1, node *list2);

/* Make a reversed copy of a list.  The input list is not altered. */
node *reverse_list(node *list);

/* Print the elements of a list. */
void print_list(node *list);

/* Return 1 if a list is sorted, otherwise 0. */
int is_sorted(node *list);

#endif  /* LINKED_LIST_H */

