#ifndef __GEN_STACK_H_
#define __GEN_STACK_H_
/* 
 * An implementation of a generic stack.
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
 * Runtime: O(1)
 */
void destroy_stack(Stack s);

/* copy_stack: Makes a deep copy of the Stack s and returns a pointer. If memory
 * 	allocation fails, returns NULL. Client must call destroy_stack on the copy.
 * Runtime: O(n), where n is the size of the Stack s.
 */
Stack copy_stack(Stack s);

/* push_stack: Places item on the top of the Stack, item must be heap allocated. 
 * 	Returns 0 if successful, 1 if resizing failed, and 2 if copying failed.
 * Runtime: O(1)
 */
int push_stack(void *item, Stack s);

/* top_stack: Returns a copy of the top item on the Stack. Returns NULL if the
 * 	Stack is empty or copying the item failed. Client is responsible for
 * 	freeing the copied items memory.
 * Runtime: O(1), amortized
 */
void *top_stack(Stack s);

/* pop_stack: Returns the top item on the Stack. Client is responsible for freeing
 * 	this items memory.
 * Runtime: O(1), amortized
 */
void *pop_stack(Stack s);

/* get_size_stack: Returns the number of items in the Stack. Can be used to check
 * 	if Stack is empty.
 * Runtime: O(1)
 */
unsigned int get_size_stack(Stack s);

#endif
