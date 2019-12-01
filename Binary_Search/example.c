#include <stdio.h>
#include <string.h>
#include "binary_search.h"

int main()
{
	char *strings[] = {"aplha", "apple", "comb", "fight",
			"tight", "tree", "vector", "vectorization",
			"zebra", "zeta"};
	int len = 10; 
	
	int index = 0;
	for (int i = 0; i < len; i += 2) {
		index = binary_search(strings[i], (void **)strings, len, strcmp);
		printf("'%s' is the %d item\n", strings[i], index);
	}

	return 0;
}
