/* Expects integers as command line arguments and sorts them
 * in non-decreasing order.
 * Uses a min-heap to sort.
 */

#include <stdio.h>
#include "heap.h"

int min_heap(void *x, void *y);

void nothing(void *a);

int main(int argc, char *argv[])
{
	int *array = malloc(sizeof(*array) * argc);
	if (!array)
		return -1;

	int n;
	for (int i = 1; i < argc; ++i) {
		n = atoi(argv[i]);
		array[i-1] = n;
	}

	Heap h = create_heap(min_heap, nothing, NULL);

	for (int i = 0; i < argc - 1; ++i) {
		if (insert_heap(h, array + i) != 0) {
			return 1;
		}
	}

	int *ptr;

	while(1) {
		ptr = extract_heap(h);
		if (!ptr)
			break;
		printf("%d ", *ptr);
	}
	printf("\n");

	destroy_heap(h);
	return 0;
}

int min_heap(void *x, void *y)
{
	int *a = x;
	int *b = y;
	if (*a == *b)
		return 0;
	return *a < *b ? -1 : 1;
}

void nothing(void *a)
{
}
