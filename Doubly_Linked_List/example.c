#include <stdio.h>
#include "dlinked_list.h"

void *cpy_int(void *a)
{
	int *i = (int *)a;
	int *n = malloc(sizeof(*n));
	if (!n)
		return NULL;
	*n = *i;
	return n;
}

int cmp(void *a, void *b)
{
	int *x = (int *)a;
	int *y = (int *)b;
	return *y - *x;
}

int main(void)
{
	DLL list = create_dll(free, cpy_int);
	int *item;
	const int n = 5;
	for (int i = 0; i < n; ++i) {
		item = malloc(sizeof(*item));
		*item = i;
		if (insert_back_dll(item, list) != 0) {
			/* insertion error */
			return 1;
		}
	}

	int look_for = n;
	struct dll_node *found = find_node(&look_for, list, cmp);
	if (found)
		printf("True\n");
	else
		printf("False\n");

	for (int i = 0; i < n; ++i) {
		if (i % 2)
			item = (int *)pop_front_dll(list);
		else
			item = (int *)pop_back_dll(list);
		printf("%d ", *item);
	}
	printf("\n");

	destroy_dll(list);
	return 0;
}
