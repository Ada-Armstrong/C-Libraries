#ifndef CONTAINER_HEAP_H
#define CONTAINER_HEAP_H

/* An implemenation of a generic heap. The heap is stored as a max-heap
 * according to cmp_func. cmp_func must use the same convention as strcmp,
 * returns -1, 0, 1 if the first argument is greater than, equal to, or less
 * than the second argument respectively. Reversing the return values of 
 * cmp_func allow you to use it as a min-heap.
 */

#include <stdlib.h>
#include <assert.h>

typedef struct heap *Heap;


/* create_heap: Allocates memory on the heap for a Heap and returns a pointer.
 * 	If memory allocation fails, returns NULL. Client must call destroy_heap
 * 	to free the memory. cmp_func must use the same convention as strcmp,
 * 	returns -1, 0, 1 if the first argument is greater than, equal to, or
 * 	less than the second argument respectively.
 * Runtime: O(1)
 */
Heap create_heap(int (*cmp_func)(void *, void *), void (*free_func)(void *),
		void *(*cpy_func)(void *));

/* destroy_heap: Frees the memory allocated by create_heap.
 * Runtime: O(n)
 */
void destroy_heap(Heap h);

/* copy_heap: Creates a deep copy of h. Returns NULL if unsuccessful.
 * Runtime: O(n)
 */
Heap copy_heap(Heap h);

/* insert_heap: Inserts item into the Heap according to cmp_fun, item must be
 * 	heap allocated. Returns 0 if successful.
 * Runtime: O(log(n))
 */
int insert_heap(Heap h, void *item);

/* extract_heap: Returns the top item on the Heap, if empty returns NULL. The
 * 	item is removed from the heap.
 * Runtime: O(log(n))
 */
void *extract_heap(Heap h);

#endif
