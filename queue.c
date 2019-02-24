/*
 * Code for bmaleloped for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = (queue_t *) malloc(sizeof(queue_t *));

    if (q != NULL) {
        q->head = NULL;
        q->tail = NULL;
        q->size = 0;
    }
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (q != NULL) {
        list_ele_t *temp;

        while ((q->head) != NULL) {
            temp = q->head;
            q->head = temp->next;
            free(temp->value);
            free(temp);
        }
    }
    free(q);
    return;
}


/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (q == NULL) {
        return false;
    }
    list_ele_t *newnode = (list_ele_t *) malloc(sizeof(list_ele_t *));
    if (newnode == NULL) {
        return false;
        // free(newnode);
    }

    if (q->size == 0) {
        q->tail = newnode;
    }
    // newnode->value = strdup(s);
    newnode->value = malloc(strlen(s) + 1);
    strcpy(newnode->value, s);
    newnode->next = q->head;
    q->head = newnode;
    q->size++;

    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    if (q == NULL) {
        return false;
    }

    list_ele_t *newinsert = (list_ele_t *) malloc(sizeof(list_ele_t *));
    if (newinsert == NULL) {
        return false;
    }
    newinsert->value = malloc(strlen(s) + 1);
    strcpy(newinsert->value, s);

    newinsert->next = NULL;
    if (q->size == 0) {
        q->head = newinsert;
    }
    q->tail->next = newinsert;
    q->tail = newinsert;
    q->size++;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (q == NULL || (q->size) == 0) {
        return false;
    }
    list_ele_t *remove;
    remove = q->head;
    q->head = q->head->next;

    if (sp != NULL) {
        memset(sp, '\0', bufsize);
        strncpy(sp, remove->value, bufsize - 1);
    }
    free(remove->value);
    free(remove);
    q->size--;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if (q == NULL || q->size == 0) {
        return 0;
    } else {
        return q->size;
    }
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    list_ele_t *current = NULL;
    list_ele_t *before = NULL;
    list_ele_t *nextnode;
    if (q != NULL && q->size > 1) {
        current = q->head;
        q->tail = current;
        while (current != NULL) {
            nextnode = current->next;
            current->next = before;
            before = current;
            current = nextnode;
            q->head = before;
        }
        return;
    }
}
