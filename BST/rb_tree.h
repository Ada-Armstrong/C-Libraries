#ifndef CONTAINER__RB_TREE_H
#define CONTAINER__RB_TREE_H

#include <stdlib.h>

struct rb_node {
	void *data;
	// black is 0, red is 1
	char colour;
	struct rb_node *left;
	struct rb_node *right;
};

struct rb_tree {
	struct rb_node *root;
	int (*cmp_func)(void *a, void *b);
	void (*free_func)(void *data);
};

#endif
