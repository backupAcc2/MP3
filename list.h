/* list.h
 *
 * Public functions for two-way linked list
 *
 * You should not need to change any of the code this file.  If you do, you
 * must get permission from the instructor.
 */

typedef struct list_node_tag {
    // private members for list.c only
    data_t *data_ptr;
    struct list_node_tag *prev;
    struct list_node_tag *next;
} list_node_t;

typedef struct list_tag {
    // private members for list.c only
    list_node_t *head;
    list_node_t *tail;
    int current_list_size;
    int list_sorted_state;
    // Private method for list.c only
    int (*comp_proc) (const data_t *, const data_t *);
} list_t;

// public definition of pointer into linked list
typedef list_node_t * IteratorPtr;
typedef list_t * ListPtr;

// public prototype definitions for list.c

// My New Functions for MP3
void input_su(su_info_t*, int); // Helper function
void list_quick_insert(ListPtr, su_info_t*); // Helper Function
void list_sort(ListPtr list_ptr, int sort_type);
void Insertion_Sort(ListPtr);
void Recursive_Selection_Sort(ListPtr, list_node_t*, list_node_t*);
list_node_t* FindMax(ListPtr, list_node_t*, list_node_t*);
void Iterative_Selection_Sort(ListPtr, list_node_t*, list_node_t*);
void Merge_Sort(ListPtr);

// build and cleanup lists
ListPtr list_construct(int (*fcomp)(const data_t *, const data_t *));
void list_destruct(ListPtr list_ptr);

// iterators into positions in the list
IteratorPtr list_iter_front(ListPtr list_ptr);
IteratorPtr list_iter_back(ListPtr list_ptr);
IteratorPtr list_iter_next(IteratorPtr idx_ptr);

data_t * list_access(ListPtr list_ptr, IteratorPtr idx_ptr);
IteratorPtr list_elem_find(ListPtr list_ptr, data_t *elem_ptr);

void list_insert(ListPtr list_ptr, data_t *elem_ptr, IteratorPtr idx_ptr);
void list_insert_sorted(ListPtr list_ptr, data_t *elem_ptr);

data_t * list_remove(ListPtr list_ptr, IteratorPtr idx_ptr);

int list_size(ListPtr list_ptr);


/* commands for vim. ts: tabstop, sts: soft tabstop sw: shiftwidth */
/* vi:set ts=8 sts=4 sw=4 et: */
