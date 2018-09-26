/* list.c
 * Heath Gerrald
 * hgerral
 * ECE 2230 Fall 2018
 * MP3
 *
 * Propose: This is an updated version of the MP2 list.c with new sorting
 * algorithms using recursion.
 *
 * Assumptions: I'm going to have to show proficiency in recursion to
 * write the correct code for these algorithms
 *
 * Bugs: None to my knowledge
 */

#include <stdlib.h>
#include <assert.h>

#include "datatypes.h"   // defines data_t
#include "list.h"        // defines public functions for list ADT

// definitions for private constants used in list.c only
#define SORTED_LIST   0xCACACAC
#define UNSORTED_LIST 0x3535353

// prototypes for private functions used in list.c only
void list_debug_validate(list_t *L);

/* ----- below are the functions  ----- */

/* Allocates a new, empty list
 *
 * By convention, the list is initially assumed to be sorted.  The field sorted
 * can only take values SORTED_LIST or UNSORTED_LIST
 *
 * The inital empty list must have
 *  1. current_list_size = 0
 *  2. list_sorted_state = SORTED_LIST
 *
 * Use list_destruct to remove and deallocate all elements on a list
 * and the header block.
 */
list_t *list_construct(int (*fcomp)(const data_t *, const data_t *))
{
    list_t *L;

    L = (list_t *) malloc(sizeof(list_t));
    L->head = NULL;
    L->tail = NULL;
    L->current_list_size = 0;
    L->list_sorted_state = SORTED_LIST;
    L->comp_proc = fcomp;

    // the last line of this function must call validate
    list_debug_validate(L);
    return L;
}

/* Purpose: sorts the list using one of the following algorithms:
 *   1 - Insertion sort
 *   2 - Recursive Selection sort
 *   3 - Iterative Selection Sort
 *   4 - Merge Sort
 *
 * The parameter sort_type will reflect which algorithm to call
*/
void list_sort(ListPtr list_ptr, int sort_type)
{
 // Insertion sort
   if (sort_type == 1) {  Insertion_Sort(list_ptr); }

 // Recursive Selection Sort
   else if (sort_type == 2)
   {
     Recursive_Selection_Sort(list_ptr, list_iter_front(list_ptr), list_iter_back(list_ptr));
   }

   else if (sort_type == 3)
   {
     Iterative_Selection_Sort(list_ptr, list_iter_front(list_ptr), list_iter_back(list_ptr));
   }

}

/* Purpose: sorts the list using the Insertion sort algorithm
 *
 * Will create a new list and adjust the head & tail points of the list_ptr
 * input to point to this new sorted list.
 */

void Insertion_Sort(ListPtr list_ptr)
{
  data_t* elem;
  list_node_t* current = list_iter_front(list_ptr);
  int node_count = 0; // find the current_list_size after while loop
  // create the new sorted list
  ListPtr sorted_list = list_construct(list_ptr->comp_proc);

  while (current != NULL)
  {
    elem = list_remove(list_ptr, current);
    list_insert_sorted(sorted_list, elem);
    current = list_iter_front(list_ptr);
    node_count++;
  }

  list_ptr->head = list_iter_front(sorted_list);
  list_ptr->tail = list_iter_back(sorted_list);
  list_ptr->current_list_size = node_count;
  free(sorted_list);
}

/* Purpose: Sorts the list using the recursive selection sort algorithm
 *
 * Finds the max value by calling the FindMax() function and swaps it with
 * the last value in the list
 */
void Recursive_Selection_Sort(ListPtr list_ptr, list_node_t* front, list_node_t* back)
{
  data_t* temp;
  list_node_t* MaxPosition;

  if (front != back)
  {
 // Find max su_id and place at back of list
    MaxPosition = FindMax(list_ptr, front, back);
    temp = back->data_ptr;
    back->data_ptr = MaxPosition->data_ptr;
    MaxPosition->data_ptr = temp;

    Recursive_Selection_Sort(list_ptr, front, back->prev);
  }

}

/* Purpose: finds the largest integer in the list from node a to b
 *
 * Takes a list and pointers to its head and tail (or range to sort)
 * as parameters
 *
 * Returns the data_t* containing max su_id
 */
list_node_t* FindMax(ListPtr list_ptr, list_node_t* a, list_node_t* b)
{
   list_node_t* i = a;  // visits all nodes from a to b
   list_node_t* j = a;  // j saves the position of the max value

   do{
     i = list_iter_next(i);
     if ((i->data_ptr->su_id) > j->data_ptr->su_id)
     {
      j = i;
     }
   } while(i != b);

   return j;
}

/* Purpose: Uses the selection sort algorithm implemented on pg 171 in
 * the textbook.
 *
 * Had to make changes to sort the list using a linked list instead of array
 * and to sort in increasing order, not decreasing
 *
 */
void Iterative_Selection_Sort(ListPtr list_ptr, list_node_t* front, list_node_t* back)
{
  data_t* temp;
  list_node_t *i, *MaxPosition;

  while (front != back)
  {
      i = back;
      MaxPosition = back;

      do {
        i = i->prev;
        if(i->data_ptr->su_id > MaxPosition->data_ptr->su_id)
            MaxPosition = i;
      } while(i != front);

      temp = back->data_ptr;
      back->data_ptr = MaxPosition->data_ptr;
      MaxPosition->data_ptr = temp;

      back = back->prev;
  }

}

/* Purpose: return the count of number of elements in the list.
 *
 * list_ptr: pointer to list-of-interest.
 *
 * Return: the number of elements stored in the list.
 */
int list_size(list_t *list_ptr)
{
    assert(NULL != list_ptr);
    assert(list_ptr->current_list_size >= 0);
    return list_ptr->current_list_size;
}

/* Deallocates the contents of the specified list, releasing associated memory
 * resources for other purposes.
 *
 * Free all elements in the list and the header block.
 */
void list_destruct(list_t *list_ptr)
{
    // the first line must validate the list
    list_debug_validate(list_ptr);
    // add your code after this line
    // check to see if list has any values
    if(list_ptr->current_list_size == 0)
    {
      free(list_ptr);
      list_ptr = NULL;
    }

    // check to see if list has one value
    else if(list_ptr->current_list_size == 1)
    {
      free(list_ptr->head->data_ptr);
      list_ptr->head->data_ptr = NULL;
      free(list_ptr->head);
      list_ptr->head = NULL;
      list_ptr->tail = NULL;
      free(list_ptr);
      list_ptr = NULL;
    }

    else
    {
      // current will serve as the back part of the list, previous the front
      list_node_t * current = list_ptr->head;
      list_node_t * previous = list_ptr->head;
      while(current->next != NULL)
        current = current->next;

      previous = current->prev;

      while(previous != NULL)
      {
        // free the data_ptr
        free(current->data_ptr);
        current->data_ptr = NULL;
        current = previous;
        // free the node
        free(current->next);
        current->next = NULL;
        previous = previous->prev;
      }
      // free the last node and data_t
      free(current->data_ptr);
      current->data_ptr = NULL;
      free(current);
      current = NULL;
      // free the list_t
      free(list_ptr);
      list_ptr = NULL;
    }

}

/* Return an Iterator that points to the last list_node_t. If the list is empty
 * then the pointer that is returned is NULL.
 */
list_node_t * list_iter_back(list_t *list_ptr)
{
    assert(NULL != list_ptr);
    list_debug_validate(list_ptr);
    return list_ptr->tail;
}

/* Return an Iterator that points to the first element in the list.  If the
 * list is empty the value that is returned in NULL.
 */
list_node_t * list_iter_front(list_t *list_ptr)
{
    assert(NULL != list_ptr);
    list_debug_validate(list_ptr);
    return list_ptr->head;
}

/* Advance the Iterator to the next item in the list.
 * If the iterator points to the last item in the list, then
 * this function returns NULL to indicate there is no next item.
 *
 * It is a catastrophic error to call this function if the
 * iterator, idx_ptr, is null.
 */
list_node_t * list_iter_next(list_node_t * idx_ptr)
{
    assert(idx_ptr != NULL);
    return idx_ptr->next;
}

/* Finds an element in a list and returns a pointer to it.
 *
 * list_ptr: pointer to list-of-interest.
 *
 * elem_ptr: element against which other elements in the list are compared.
 *           Note: uses the comp_proc function pointer found in the list_t
 *           header block.
 *
 * The function returns an Iterator pointer to the list_node_t that contains
 * the first matching element if a match if found.  If a match is not found
 * the return value is NULL.
 *
 * Note: to get a pointer to the matching data_t memory block pass the return
 *       value from this function to the list_access function.
 */
list_node_t * list_elem_find(list_t *list_ptr, data_t *elem_ptr)
{
    list_debug_validate(list_ptr);
  // MY CODE
    if (list_ptr->current_list_size == 0)
        return NULL;

    list_node_t * current = list_ptr->head;

    while(current != NULL)
    {
      if (list_ptr->comp_proc(elem_ptr, current->data_ptr) == 0)
        return current;
      current = current->next;
    }
  // END MY CODE
    return NULL;
}

/* Inserts the element into the specified sorted list at the proper position,
 * as defined by the comparison function, comp_proc.
 *
 * list_ptr: pointer to list-of-interest.
 *
 * elem_ptr: pointer to the element to be inserted into list.
 *
 * If you use list_insert_sorted, the list preserves its sorted nature.
 *
 * If you use list_insert, the list will be considered to be unsorted, even
 * if the element has been inserted in the correct position.
 *
 * If the list is not sorted and you call list_insert_sorted, this subroutine
 * must generate a system error and the program should immediately stop.
 *
 * The comparison procedure must accept two arguments (A and B) which are both
 * pointers to elements of type data_t.  The comparison procedure returns an
 * integer code which indicates the precedence relationship between the two
 * elements.  The integer code takes on the following values:
 *    1: A should be closer to the front of the list than B
 *   -1: B should be closer to the front of the list than A
 *    0: A and B are equal in rank
 *
 * Note: if the element to be inserted is equal in rank to an element already
 * in the list, the newly inserted element will be placed after all the
 * elements of equal rank that are already in the list.
 */
void list_insert_sorted(list_t *list_ptr, data_t *elem_ptr)
{
    assert(NULL != list_ptr);
    assert(SORTED_LIST == list_ptr->list_sorted_state);

  // MY CODE
    list_node_t *newNode = (list_node_t*)malloc(sizeof(list_node_t));
  // check to see if list is empty
    if(list_ptr->current_list_size == 0)
    {
      list_ptr->head = newNode;
      list_ptr->tail = newNode;
      newNode->next = NULL;
      newNode->prev = NULL;
      newNode->data_ptr = elem_ptr;
    }

    else
    {
      // insert newNode at front of list, then sort
      list_node_t * first = list_ptr->head;
      list_node_t * second;
      first->prev = newNode;
      newNode->next = first;
      newNode->prev = NULL;
      newNode->data_ptr = elem_ptr;
      list_ptr->head = newNode;

      int size = list_size(list_ptr);
      int compVal;
      first = list_ptr->head;
      second = first->next;
      data_t * tempData;
      for(int i = 0; i < size; i++)
      {
        compVal = list_ptr->comp_proc(first->data_ptr,second->data_ptr);
        if (compVal == 1)
        {
          // leave how is
          first=first->next;
          second=second->next;
        }
        else if(compVal == -1)
        {
          // swap the data values
          tempData = first->data_ptr;
          first->data_ptr = second->data_ptr;
          second->data_ptr = tempData;
          first=first->next;
          second=second->next;
        }
        else
        {
          // get to the end of all the data_t's of equal rank
          while(list_ptr->comp_proc(first->data_ptr,second->data_ptr) == 0)
          {
            second=second->next;
            // move newNode to after second
            tempData = first->data_ptr;
            first->data_ptr = second->data_ptr;
            second->data_ptr = tempData;
          }
        }
      }
    }


    list_ptr->current_list_size++;
  // END MY CODE
    // the last line of this function must be the following
    list_debug_validate(list_ptr);
}

/* Inserts the data element into the list in front of the iterator
 * position.
 *
 * list_ptr: pointer to list-of-interest.
 *
 * elem_ptr: pointer to the memory block to be inserted into list.
 *
 * idx_ptr: pointer to a list_node_t.  The element is to be inserted as a
 *          member in the list at the position that is immediately in front
 *          of the position of the provided Iterator pointer.
 *
 *          If the idx_ptr pointer is NULL, the the new memory block is
 *          inserted after the last element in the list.  That is, a null
 *          iterator pointer means make the element the new tail.
 *
 * If idx_ptr is set using
 *    -- list_iter_front, then the new element becomes the first item in
 *       the list.
 *    -- list_iter_back, then the new element is inserted before the last item
 *       in the list.
 *    -- for any other idx_ptr, the new element is insert before the
 *       Iterator
 *
 * For example, to insert at the tail of the list do
 *      list_insert(mylist, myelem, NULL)
 * to insert at the front of the list do
 *      list_insert(mylist, myelem, list_iter_front(mylist))
 *
 * Note that use of this function results in the list to be marked as unsorted,
 * even if the element has been inserted in the correct position.  That is, on
 * completion of this subroutine the list_ptr->list_sorted_state must be equal
 * to UNSORTED_LIST.
 */
void list_insert(list_t *list_ptr, data_t *elem_ptr, list_node_t * idx_ptr)
{
    assert(NULL != list_ptr);

    // MY CODE
    list_node_t *newNode = (list_node_t*)malloc(sizeof(list_node_t));
  // check to see if list is empty
    if(list_ptr->current_list_size == 0)
    {
      list_ptr->head = newNode;
      list_ptr->tail = newNode;
      newNode->next = NULL;
      newNode->prev = NULL;
    }

  // if idx_ptr == NULL, insert at back of list
    else if(idx_ptr == NULL)
    {
      list_node_t * temp = list_ptr->tail;
      newNode->prev = list_ptr->tail;
      newNode->next = NULL;
      temp->next = newNode;
      list_ptr->tail = newNode;
    }

    else
    {
      // check to see if iterator is front of list
      if(list_ptr->head == idx_ptr)
      {
        newNode->prev = NULL;
        newNode->next = list_ptr->head;
        list_ptr->head = newNode;
        idx_ptr->prev = newNode;
      }
      else
      {
        list_node_t * temp = idx_ptr->prev;
        newNode->next = idx_ptr;
        newNode->prev = idx_ptr->prev;
        idx_ptr->prev = newNode;
        temp->next = newNode;
      }
    }

    newNode->data_ptr = elem_ptr;
    list_ptr->current_list_size++;
    // END MY CODE

    // the last two lines of this function must be the following
    if (list_ptr->list_sorted_state == SORTED_LIST)
	list_ptr->list_sorted_state = UNSORTED_LIST;
    list_debug_validate(list_ptr);
}

/* Removes the element from the specified list that is found at the
 * iterator pointer.  A pointer to the data element is returned.
 *
 * list_ptr: pointer to list-of-interest.
 *
 * idx_ptr: pointer to position of the element to be accessed.  This pointer
 *          must be obtained from list_elem_find, list_iter_front, or
 *          list_iter_next, or list_iter_back.
 *
 *          If the idx_ptr is null, then assume that the first item
 *          at the head is to be removed.
 *
 * If the list is empty, then the function should return NULL.  Note: if
 *    the list is empty, then the iterator should be a NULL pointer.
 *
 * Note to remove the element at the front of the list use either
 *     list_remove(mylist, list_iter_front(mylist))
 *  or
 *     list_remove(mylist, NULL);
 *
 * Note: a significant danger with this function is that once
 * an element is removed from the list, the idx_ptr is dangling.  That
 * is, the idx_ptr now points to memory that is no longer valid.
 * You should not call list_iter_next on an iterator after there
 * has been a call to list_remove with the same iterator.
 *
 * When you remove the list_node_t in this function, you should null the next
 * and prev pointers before you free the memory block to avoid accidental use
 * of these now invalid pointers.
 */
data_t * list_remove(list_t *list_ptr, list_node_t * idx_ptr)
{
    assert(NULL != list_ptr);
    if (0 == list_ptr->current_list_size)
  	assert(idx_ptr == NULL);

    // MY CODE
    if (idx_ptr==NULL || list_ptr->current_list_size == 0)
        return NULL;

    data_t * su_data = idx_ptr->data_ptr;
    // check to see if there is only one node
      if(list_ptr->current_list_size == 1)
      {
        idx_ptr->prev = NULL;
        idx_ptr->next = NULL;
        list_ptr->head = NULL;
        list_ptr->tail = NULL;
        free(idx_ptr);
      }
    // check if this is the head or tail
      else if (list_ptr->head == idx_ptr)
      {
        list_node_t * idxNext = idx_ptr->next;
        idx_ptr->prev = NULL;
        idx_ptr->next = NULL;
        free(idx_ptr);
        list_ptr->head = idxNext;
        idxNext->prev = NULL;
      }
      else if(list_ptr->tail == idx_ptr)
      {
        list_node_t * idxPrev = idx_ptr->prev;
        idx_ptr->prev = NULL;
        idx_ptr->next = NULL;
        free(idx_ptr);
        list_ptr->tail = idxPrev;
        idxPrev->next = NULL;
      }
      else
      {
        list_node_t * idxPrev = idx_ptr->prev;
        list_node_t * idxNext = idx_ptr->next;
        idx_ptr->prev = NULL;
        idx_ptr->next = NULL;
        free(idx_ptr);
        idxPrev->next = idxNext;
        idxNext->prev = idxPrev;
      }

    list_ptr->current_list_size--;
    // END MY CODE

    // the last line should verify the list is valid after the remove
    list_debug_validate(list_ptr);
    return su_data;  // fix the return value
}

/* Return a pointer to an element stored in the list, at the Iterator position
 *
 * list_ptr: pointer to list-of-interest.  A pointer to an empty list is
 *           obtained from list_construct.
 *
 * idx_ptr: pointer to position of the element to be accessed.  This pointer
 *          must be obtained from list_elem_find, list_iter_front,
 *          list_iter_back, or list_iter_next.
 *
 * return value: pointer to the data_t element found in the list at the
 * iterator position. A value NULL is returned if
 *     a:  the idx_ptr is NULL.
 *     b:  the list is empty
 */
data_t * list_access(list_t *list_ptr, list_node_t * idx_ptr)
{
    assert(NULL != list_ptr);
    if (idx_ptr == NULL)
	return NULL;
    // debugging function to verify that the structure of the list is valid
    list_debug_validate(list_ptr);

    return idx_ptr->data_ptr;   // you have to fix the return value
}

/* This function verifies that the pointers for the two-way linked list are
 * valid. It checks if the list size equals the number of items in the list.
 *
 * YOU MUST NOT CHANGE THIS FUNCTION.  WE USE IT DURING GRADING TO VERIFY THAT
 * YOUR LIST IS CONSISTENT.
 *
 * No output is produced if the two-way linked list is correct.
 * The program terminates and prints a line beginning with "Assertion
 * failed:" if an error is detected.
 *
 * The checks are not exhaustive. An error may still exist in the list even
 * if these checks pass.
 *
 * If the linked list is sorted it also checks that the elements in the list
 * appear in the proper order.
 *
 */
void list_debug_validate(list_t *L)
{
    assert(NULL != L);
    assert(SORTED_LIST == L->list_sorted_state || UNSORTED_LIST == L->list_sorted_state);
    if (0 == L->current_list_size) assert(NULL == L->head && L->tail == NULL);
    if (NULL == L->tail)
	assert(NULL == L->head && 0 == L->current_list_size);
    else
	assert(NULL == L->tail->next);
    if (NULL == L->head)
	assert(NULL == L->tail && 0 == L->current_list_size);
    else
	assert(NULL == L->head->prev);
    if (NULL != L->tail && L->tail == L->head) assert(1 == L->current_list_size);
    if (1 == L->current_list_size) {
        assert(L->head == L->tail && NULL != L->tail);
        assert(NULL != L->tail->data_ptr);
        assert(NULL == L->tail->next && NULL == L->head->prev);
    }
    if (1 < L->current_list_size) {
        assert(L->head != L->tail && NULL != L->tail && NULL != L->head);
        list_node_t *R = L->head;
        int tally = 0;
        while (NULL != R) {
            if (NULL != R->next) assert(R->next->prev == R);
            else assert(R == L->tail);
            assert(NULL != R->data_ptr);
            ++tally;
            R = R->next;
        }
        assert(tally == L->current_list_size);
    }
    if (NULL != L->head && SORTED_LIST == L->list_sorted_state) {
        list_node_t *R = L->head;
        while (NULL != R->next) {
            assert(-1 != L->comp_proc(R->data_ptr, R->next->data_ptr));
            R = R->next;
        }
    }
}
/* commands for vim. ts: tabstop, sts: softtabstop sw: shiftwidth */
/* vi:set ts=8 sts=4 sw=4 et: */
