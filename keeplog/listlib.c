#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "listlib.h"

#define TRAV_INT_SIZE 8

/*
 * list_struct holds a pointer to an instance of itself (*next)
 * and is thus implemented as a linked list data structure.
 * It's data is held in another type: data_t.
 */
typedef struct list_struct {
    data_t item;
    struct list_struct *next;
} list_t;

static list_t endlist;
static list_t *headptr = NULL;
static list_t *tailptr = NULL;
static list_t **travptrs = NULL;

static int travptrs_size = 0;

/* return a nonnegative key if successful */
int accessdata(void) {
    list_t **newptrs;

    /* If the root (or head) pointer is NULL,
     * we know the list is empty, and return an error
     * since the user cannot access data on an empty list.
     */
    if (headptr == NULL) {
        /* Set global errno to indicate an invalid argument. */
        errno = EINVAL;
        /* Return -1 to indicate an error occurred. */
        return -1;
    }

    /* This is our first time executing */
    if (travptrs_size == 0) {
        /* Allocate enough space in travptrs
         * to contain TRAV_INIT_SIZE number of pointers to nodes.
         */
        travptrs = (list_t **) calloc(TRAV_INT_SIZE, sizeof(list_t *));
        /* couldn't allocate space for traversal keys */
        if (travptrs == NULL) {
            return -1;
        }

        /* Set the head pointer, and size. */
        travptrs[0] = headptr;
        travptrs_size = TRAV_INT_SIZE;

        return 0;
    }

    /* Look for an empty slot for key */
    for (int i = 0; i < travptrs_size; i++) {
        if (travptrs[i] == NULL) {
            travptrs[i] = headptr;
            return i;
        }
    }

    /* If we made it here, the list is filled.
     * Double the list size.
     */
    newptrs = realloc(travptrs, 2 * travptrs_size * sizeof(list_t *));

    /* couldn't expand the array of traversal keys */
    if (newptrs == NULL) {
        return -1;
    }

    /* Set the global to our resized list. */
    travptrs = newptrs;
    /* Move up the head pointer */
    travptrs[travptrs_size] = headptr;
    /* Adjust the size global to account for realloc() */
    travptrs_size *= 2;
    return travptrs_size / 2;
}

/* Allocate a node for the new data, and add it to
 * the end of the list.
 *
 * If we encounter an error, return -1.
 */
int adddata(data_t data) {
    /* A pointer to the new node we're adding to the list */
    list_t *newnode;

    /* Compute how much memory we need to allocate
     * for the new node.
     *
     * Note: strlen() can be a dangerous function because
     * it assumes the string is NULL ('\0') terminated.
     */
    int nodesize = sizeof(list_t) + strlen(data.string) + 1;

    /* Allocate memory from the heap with malloc(), cast it
     * appropriately, and assign it to our new node's variable.
     *
     * If malloc() returns a NULL pointer, then we are probably
     * out of memory, and should report the error condition.
     */
    if ((newnode = (list_t *) malloc(nodesize)) == NULL) {
        return -1;
    }

    /* Copy the time_t from the data passed in into our new node. */
    newnode->item.time = data.time;

    /* Initialize the string pointer to point to the position
     * in the newly allocated memory where the argument string
     * will be copied to.
     */
    newnode->item.string = (char *) newnode + sizeof(list_t);

    /* Copy the argument string to the address computed.
     *
     * Note: strcpy() has a similar vulnerability as strlen()
     * because it is dependent on the NULL character ('\0').
     */
    strcpy(newnode->item.string, data.string);

    /* Since this new node will go at the end of the list,
     * we need to set its next pointer to NULL, so that
     * we will know when we're at the end of the list.
     */
    newnode->next = NULL;

    /* If this is a new list, headptr will be NULL,
     * and we can use our new node as the head.
     */
    if (headptr == NULL) {
        headptr = newnode;
    }
    else {
        /* Otherwise, set the tail node's next node
         * to point to our new node.
         */
        tailptr->next = newnode;
    }

    /* The tail node is now our new node, so we set
     * it accordingly.
     */
    tailptr = newnode;

    /* Everything went okay, so return 0 to indicate successful execution. */
    return 0;
}

/* copy next item and set datap->string */
int getdata(int key, data_t *datap) {
    list_t *t;

    if ((key < 0) || (key >= travptrs_size) || (travptrs[key] == NULL)) {
        errno = EINVAL;
        return -1;
    }
    /* end of list, set datap->string to NULL */
    if (travptrs[key] == &endlist) {
        datap->string = NULL;
        travptrs[key] = NULL;
        /* reaching end of list natural condition, not an error */
        return 0;
    }
    t = travptrs[key];
    datap->string = (char *) malloc(strlen(t->item.string) + 1);
    /* couldn't allocate space for returning string */
    if (datap->string == NULL)
        return -1;
    datap->time = t->item.time;
    strcpy(datap->string, t->item.string);
    if (t->next == NULL)
        travptrs[key] = &endlist;
    else
        travptrs[key] = t->next;
    return 0;
}

/* free list entry corresponding to key */
int freekey(int key) {
    /* key out of range */
    if ((key < 0) || (key >= travptrs_size)) {
        errno = EINVAL;
        return -1;
    }
    travptrs[key] = NULL;
    return 0;
}