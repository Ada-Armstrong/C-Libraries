#include "rb_tree.h"

static struct rb_node *create_node(void *data, char colour)
{
	struct rb_node *n = malloc(sizeof(*n));
	if (!n)
		return NULL;

	n->data = data;
	n->colour = colour;
	return n;
}

static void destroy_node(struct rb_node *n)
{
	if (!n)
		return;

	if (n->data)
		n->free_func(n->data);
	free(n);
}

static void destroy_nodes(struct rb_node *n)
{
	destroy_nodes(n->left);
	destroy_nodes(n->right);
	destroy_node(n);
}

struct rb_tree *create_rb_tree(int (*cmp_func)(void *a, void *b),
		void (*free_func)(void *data))
{
	struct rb_tree *t = malloc(sizeof(*t));
	if (!t)
		return NULL;

	t->root = NULL;
	t->cmp_func = cmp_func;
	t->free_func = free_func;
	return t;
}

void destroy_rb_tree(struct rb_tree *t)
{
	if (!t)
		return;

	destroy_nodes(t->root);
	free(t);
}

int insert_rb_tree(struct rb_tree *t, void *data)
{
	if (!t)
		return -1;
	if (!data)
		return -2;

	struct rb_node *n = create_node(data, 0);
	if (!n)
		return 0;

	if (!t->root) {
		t->root = n;
		return 1;
	}

	return insert_node(t->root);
}
