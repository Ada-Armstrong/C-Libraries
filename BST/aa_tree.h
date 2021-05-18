#ifndef CONTAINER_AA_TREE_H
#define CONTAINER_AA_TREE_H

#include <stdlib.h>
#include <assert.h>


struct aa_node {
	void *data;
	unsigned int level;
	struct aa_node *left;
	struct aa_node *right;
};

struct aa_tree {
	struct aa_node *root;
	int (*cmp_func)(void *a, void *b);
	void (*free_func)(void *data);
};

struct aa_tree *create_aa_tree(int (*cmp_func)(void *a, void *b), void (*free_func)(void *data));

void destroy_aa_tree(struct aa_tree *tree);

int insert_aa_tree(void *data, struct aa_tree *tree);

int delete_aa_tree(void *data, struct aa_tree *tree);

void *search_aa_tree(void *key, struct aa_tree *tree);

#endif
