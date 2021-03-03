#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* TODO: What if malloc returned NULL? */
    if (!q) {
        return q;
    }
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* TODO: How about freeing the list elements and the strings? */
    /* Free queue structure */
    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    char *s_new;
    /* TODO: What should you do if the q is NULL? */
    if (!q) {
        return false;
    }
    newh = malloc(sizeof(list_ele_t));

    if (!newh) {
        return false;
    }
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    if (!q->head) {
        q->tail = newh;
    }

    newh->next = q->head;
    q->head = newh;

    s_new = malloc(sizeof(char) * (strlen(s) + 1));
    if (!s_new) {
        return false;
    }
    newh->value = s_new;
    memcpy(s_new, s, strlen(s) + 1);
    q->size++;
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* TODO: You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    list_ele_t *newh;
    char *s_new;
    if (!q) {
        return false;
    }
    newh = malloc(sizeof(list_ele_t));
    if (!newh) {
        return false;
    }
    newh->next = NULL;
    q->tail->next = newh;
    q->tail = newh;

    s_new = malloc(sizeof(char) * (strlen(s) + 1));
    if (!s_new) {
        return false;
    }
    newh->value = s_new;
    memcpy(s_new, s, strlen(s) + 1);
    q->size++;


    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* TODO: You need to fix up this code. */
    /* TODO: Remove the above comment when you are about to implement. */
    list_ele_t *delete_ptr;
    if (!q) {
        return false;
    }
    if (!q->head) {
        return false;
    }
    memcpy(sp, q->head->value, bufsize);
    sp[bufsize - 1] = '\0';
    free(q->head->value);
    delete_ptr = q->head;
    q->head = q->head->next;
    free(delete_ptr);
    q->size--;
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q) {
        return 0;
    }
    return q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
    list_ele_t *prev = NULL, *current, *next, *swap;
    if (!q) {
        return;
    }
    for (current = q->head; current != NULL;) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    swap = q->head;
    q->head = q->tail;
    q->tail = swap;
}


void list_add(list_ele_t **list, list_ele_t *node)
{
    node->next = *list;
    *list = node;
}

void list_concat(list_ele_t **left, list_ele_t *right)
{
    while (*left) {
        left = &((*left)->next);
    }
    *left = right;
}

void quicksort(list_ele_t **list)
{
    if (!*list) {
        return;
    }

    list_ele_t *pivot = *list;
    char *value = pivot->value;
    list_ele_t *p = pivot->next;
    pivot->next = NULL;

    list_ele_t *left = NULL, *right = NULL;
    while (p) {
        list_ele_t *n = p;
        p = p->next;
        list_add(strcmp(n->value, value) > 0 ? &right : &left, n);
    }

    quicksort(&left);
    quicksort(&right);

    list_ele_t *result = NULL;
    list_concat(&result, left);
    list_concat(&result, pivot);
    list_concat(&result, right);
    *list = result;
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q || !q->head || !q->head->next) {
        return;
    }

    quicksort(&q->head);
}