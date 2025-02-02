#ifndef CONTAINER_DLINKEDLIST_H
#define CONTAINER_DLINKEDLIST_H

/* An implementation of a generic doubly linked list.
 */

#include <stdlib.h>

typedef struct dlinked_list *DLL;


/* create_dll: Allocates memory on the heap for a doubly linked list and
 * 	returns a pointer. If memory allocation fails returns NULL. Client
 * 	must call destroy_dll to free the memory.
 * Runtime: O(1)
 */
DLL create_dll(void (*free_func)(void *), void *(*cpy_func)(void *));

/* destroy_dll: Frees the memory allocated by create_dll.
 * Runtime: O(n)
 */
void destroy_dll(DLL l);

/* insert_front_dll: Inserts item to the front of the list.
 * Runtime: O(1)
 */
int insert_front_dll(void *item, DLL l);

/* insert_back)dll: Inserts item to the back of the list.
 * Runtime: O(1)
 */
int insert_back_dll(void *item, DLL l);

/* find_node: Returns the node that contains item with respect to cmp_func.
 * 	cmp_func returns 0 if the two arguments are the same.
 * Runtime: O(n)
 */
struct dll_node *find_node(void *item, DLL l, int (*cmp_func)(void *, void *));

/* pop_front_dll: Returns the front item in the list. If the list is empty
 * 	returns NULL.
 * Runtime: O(1)
 */
void *pop_front_dll(DLL l);

/* pop_back_dll: Returns the back item in the list. If the list is empty
 * 	returns NULL.
 * Runtime: O(1)
 */
void *pop_back_dll(DLL l);

/* size_dll: Returns the number of elements in the list.
 * Runtime: O(1)
 */
unsigned int size_dll(DLL l);

#endif
