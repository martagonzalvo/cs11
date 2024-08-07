/*
 * FILE: linked_list.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "memcheck.h"
#include "linked_list.h"


/*
 * create_node:
 *     Create a single node and link it to the node called 'n'.
 */

node *
create_node(int data, node *n)
{
    node *result = (node *)malloc(sizeof(node));

    if (result == NULL)
    {
        fprintf(stderr, "Fatal error: out of memory. "
                "Terminating program.\n");
        exit(1);
    }

    result->data = data;  /* Fill in the new node with the given value. */
    result->next = n;

    return result;
}


/*
 * free_list:
 *     Free all the nodes of a linked list.
 */

void
free_list(node *list)
{
    node *n;     /* a single node of the list */

    while (list != NULL)
    {
        n = list;
        list = list->next;

        /*
         * 'n' now points to the first element of the list, while
         * 'list' now points to everything but the first element.
         * Since nothing points to 'n', it can be freed.
         */

        free(n);
    }
}


/*
 * copy_list:
 *     Return a copy of a list.
 */

node *
copy_list(node *list)
{
    if (list == NULL)
    {
        return list;
    }
    else
    {
        node *new_list;

        new_list = (node *)malloc(sizeof(node));

        if (new_list == NULL)
        {
            fprintf(stderr, "Fatal error: out of memory. "
                    "Terminating program.\n");
            exit(1);
        }

        new_list->data = list->data;
        new_list->next = copy_list(list->next);
        return new_list;
    }
}



/*
 * append_lists:
 *     Return a list which is a copy of the concatenation of the two
 *     input lists.
 */

node *
append_lists(node *list1, node *list2)
{
    node *item;

    if (list1 == NULL)
    {
        return copy_list(list2);
    }
    else if (list2 == NULL)
    {
        return copy_list(list1);
    }
    else
    {
        node *new_list1 = copy_list(list1);
        node *new_list2 = copy_list(list2);

        /*
         * Find the end of 'new_list1' and change its 'next' pointer
         * to point to 'new_list2'.
         */

        for (item = new_list1; item != NULL; item = item->next)
        {
            if (item->next == NULL)  /* We're on the last node. */
            {
                item->next = new_list2;

                /*
                 * Now 'new_list1' contains the copy of both lists
                 * appended together.
                 */

                break;
            }
        }

        return new_list1;
    }
}


/*
 * Make a reversed copy of a list.
 */

node *
reverse_list(node *list)
{
    node *item;
    node *reversed_list = NULL;

    for (item = list; item != NULL; item = item->next)
    {
        reversed_list = create_node(item->data, reversed_list);
    }

    return reversed_list;
}


/*
 * Print the elements of a list.
 */

void
print_list(node *list)
{
    node *item;

    for (item = list; item != NULL; item = item->next)
    {
        printf("%d\n", item->data);
    }
}


/*
 * Return 1 if a list is sorted, otherwise 0.
 * Useful for debugging.
 */

int
is_sorted(node *list)
{
    node *item;

    /* An empty list is sorted by definition. */
    if (list == NULL)
    {
        return 1;
    }

    /*
     * Compare consecutive list data elements to make sure they're in the
     * right order.  If not, then the list is not sorted and return 0.
     */

    for (item = list; item->next != NULL; item = item->next)
    {
        if (item->data > item->next->data)  /* wrong order */
        {
            return 0;
        }
    }

    return 1;  /* The list is sorted. */
}


