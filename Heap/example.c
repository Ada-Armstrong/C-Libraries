#include <stdio.h>
#include "heap.h"

int array[] = {4, -11, 33, 7, 8, -43, 5};

int min_heap(void *x, void *y);

void nothing(void *a);


int main(void)
{
	Heap h = create_heap(min_heap, nothing, NULL);

	for (int i = 0; i < 7; ++i) {
		printf("inserting %d\n", array[i]);
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
