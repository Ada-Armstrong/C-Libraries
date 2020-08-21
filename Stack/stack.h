#ifndef CONTAINER_STACK_H
#define CONTAINER_STACK_H

/* An implementation of a generic stack.
 */

#include <stdlib.h>
#include <assert.h>

typedef struct stack *Stack;


/* create_stack: Allocates memory on the heap for a Stack and returns a pointer.
 * 	If memory allocation fails, returns NULL. Client must call destroy_stack
 * 	to free the memory.
 * Runtime: O(1) 
 */
Stack create_stack(void (*free_func)(void *), void *(*cpy_func)(void *));

/* destroy_stack: Frees the memory allocated by create_stack.
 * Runtime: O(n)
 */
void destroy_stack(Stack s);

/* copy_stack: Makes a deep copy of the Stack s and returns a pointer. If memory
 * 	allocation fails, returns NULL. Client must call destroy_stack on the copy.
 * Runtime: O(n), where n is the size of the Stack s.
 */
Stack copy_stack(Stack s);

/* push_stack: Places item on the top of the Stack, item must be heap allocated. 
 * 	Returns 0 if successful and 1 if resizing failed.
 * Runtime: O(1)
 */
int push_stack(Stack s, void *item);

/* top_stack: Returns the top item on the Stack. Returns NULL if the
 * 	Stack is empty or copying the item failed.
 * Runtime: O(1), amortized
 */
void *top_stack(Stack s);

/* pop_stack: Returns the top item on the Stack. Client is responsible for
 * 	freeing this items memory.
 * Runtime: O(1), amortized
 */
void *pop_stack(Stack s);

/* size_stack: Returns the number of items in the Stack. Can be used to
 * 	check if Stack is empty.
 * Runtime: O(1)
 */
unsigned int size_stack(Stack s);

#endif
