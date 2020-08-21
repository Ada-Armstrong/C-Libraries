#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H


/* binary_search: Returns the index to item if it exists in array.
 * 	array must be sorted in ascending order by cmp_func.
 * 	len is the length of the array. cmp_func must use the same
 * 	convention as strcmp, returns -1, 0, 1 if the first argument
 * 	is greater than, equal to, or less than the second argument 
 * 	respectively.
 * Runtime: O(log(n))
 */
int binary_search(void *item, void *array[], int len,
		int (*cmp_func)(void *, void *)); 

#endif
