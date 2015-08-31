#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "listlib.h"

#define TRAV_INT_SIZE 8

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
    int i;
    list_t **newptrs;
    /* can't access a completely empty list */
    if (headptr == NULL) {
        errno = EINVAL;
        return -1;
    }
    if (travptrs_size == 0) {
        travptrs = (list_t **) calloc(TRAV_INT_SIZE, sizeof(list_t *));
        /* couldn't allocate space for traversal keys */
        if (travptrs == NULL)
            return -1;
        travptrs[0] = headptr;
        travptrs_size = TRAV_INT_SIZE;
        return 0;
    }
    /* look for an empty slot for key */
    for (i = 0; i < travptrs_size; i++) {
        if (travptrs[i] == NULL) {
            travptrs[i] = headptr;
            return i;
        }
    }
    newptrs = realloc(travptrs, 2 * travptrs_size * sizeof(list_t *));
    /* couldn't expand the array of traversal keys */
    if (newptrs == NULL)
        return -1;
    travptrs = newptrs;
    travptrs[travptrs_size] = headptr;
    travptrs_size *= 2;
    return travptrs_size / 2;
}

/* allocate node for data and add to end of list */
int adddata(data_t data) {
    list_t *newnode;
    int nodesize;

    nodesize = sizeof(list_t) + strlen(data.string) + 1;
    /* couldn't add node */
    if ((newnode = (list_t *) malloc(nodesize)) == NULL)
        return -1;

    newnode->item.time = data.time;
    newnode->item.string = (char *) newnode + sizeof(list_t);
    strcpy(newnode->item.string, data.string);
    newnode->next = NULL;
    if (headptr == NULL)
        headptr = newnode;
    else
        tailptr->next = newnode;
    tailptr = newnode;
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