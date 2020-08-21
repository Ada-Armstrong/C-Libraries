#include "binary_search.h"

int binary_search(void *item, void *array[], int len,
		int (*cmp_func)(void *, void *))
{
	if (!item || !array || len < 0 || !cmp_func)
		return -1;

	void *low = array[0];
	void *mid = array[len / 2];
	void *high = array[len - 1];

	int retval = 0;
	int l = 0;
       	int m = len / 2;
	int h = len - 1;

	while (cmp_func(low, high) < 0) {
		retval = cmp_func(item, mid);
		if (retval == 0) {
			return m;
		} else if (retval < 0) {
			high = mid;
			h = m;	
		} else {
			low = mid;
			l = m;
		}
		m = ((h - l) / 2) + l; 
		mid = array[m];
	}

	return -1;
}
