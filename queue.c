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
    if (!q) {
        return;
    }
    for (; q->head != NULL;) {
        free(q->head->value);
        list_ele_t *delete_node = q->head;
        q->head = q->head->next;
        free(delete_node);
    }

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

    s_new = malloc(sizeof(char) * (strlen(s) + 1));
    if (!s_new) {
        free(newh);
        return false;
    }
    if (!q->head) {
        q->tail = newh;
    }
    newh->next = q->head;
    q->head = newh;
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
    s_new = malloc(sizeof(char) * (strlen(s) + 1));
    if (!s_new) {
        free(newh);
        return false;
    }

    newh->next = NULL;
    if (q->tail) {
        q->tail->next = newh;
    } else {
        q->head = newh;
    }
    q->tail = newh;
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
    if (sp) {
        memcpy(sp, q->head->value, bufsize);
        sp[bufsize - 1] = '\0';
    }
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

void list_insert_tail(list_ele_t **head, list_ele_t **tail, list_ele_t *node)
{
    if (*tail == NULL) {
        *tail = node;
        *head = node;
    } else {
        (*tail)->next = node;
        (*tail) = node;
    }
}

list_ele_t *merge(list_ele_t *first, list_ele_t *second)
{
    list_ele_t *result_head = NULL, *result_tail = NULL;
    while (first && second) {
        // compare and put the smaller one in result
        if (strcmp(first->value, second->value) <= 0) {
            list_insert_tail(&result_head, &result_tail, first);
            first = first->next;
        } else {
            list_insert_tail(&result_head, &result_tail, second);
            second = second->next;
        }
    }
    // Find the list that still have data, and add it in result
    if (first) {
        list_insert_tail(&result_head, &result_tail, first);
    }
    if (second) {
        list_insert_tail(&result_head, &result_tail, second);
    }
    return result_head;
}

list_ele_t *mergesort(list_ele_t *list)
{
    if (!list->next) {
        return list;
    }
    list_ele_t *slow = list, *fast = list->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    list_ele_t *tmp = slow->next;
    slow->next = NULL;
    return merge(mergesort(list), mergesort(tmp));
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
    list_ele_t *i;
    q->head = mergesort(q->head);
    for (i = q->head; i->next != NULL; i = i->next)
        ;
    q->tail = i;
}