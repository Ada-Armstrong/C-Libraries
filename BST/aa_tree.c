#include "aa_tree.h"

static struct aa_node *create_node(void *data, unsigned int level)
{
	struct aa_node *node = malloc(sizeof(*node));
	if (!node)
		return NULL;

	node->data = data;
	node->level = level;
	node->left = NULL;
	node->right = NULL;
	
	return node;
}

static void destroy_node(struct aa_node *node, struct aa_tree *tree)
{
	if (!node)
		return;

	if (node->data && tree->free_func)
		tree->free_func(node->data);

	free(node);
}

static void destroy_nodes(struct aa_node *node, struct aa_tree *tree)
{
	if (!node)
		return;

	destroy_nodes(node->left, tree);
	destroy_nodes(node->right, tree);

	destroy_node(node, tree);
}

struct aa_tree *create_aa_tree(int (*cmp_func)(void *a, void *b), void (*free_func)(void *data))
{
	assert(cmp_func);

	struct aa_tree *tree = malloc(sizeof(*tree));
	if (!tree)
		return NULL;

	tree->root = NULL;
	tree->cmp_func = cmp_func;
	tree->free_func = free_func;

	return tree;
}

void destroy_aa_tree(struct aa_tree *tree)
{
	if (!tree)
		return;

	destroy_nodes(tree->root, tree);
	free(tree);
}

static struct aa_node *skew(struct aa_node *node)
{
	if (!node || !node->left)
		return node;

	if (node->left->level == node->level) {
		struct aa_node *l = node->left;

		node->left = l->right;
		l->right = node;

		return l;
	}

	return node;
}

static struct aa_node *split(struct aa_node *node)
{

	if (!node || !node->right || !node->right->right)
		return node;

	if (node->level == node->right->right->level) {
		struct aa_node *r = node->right;

		node->right = r->left;
		r->left = node;
		r->level += 1;

		return r;
	}

	return node;
}

static struct aa_node *insert(struct aa_node *cur, void *data, struct aa_tree *tree)
{
	if (!cur) {
		struct aa_node *new_node = create_node(data, 1);
		if (!new_node) {
			// propogate error msg
		}

		return new_node;
	}

	const int cmp = tree->cmp_func(data, cur->data); 

	if (cmp == 1) {
		cur->left = insert(cur->left, data, tree);
	} else if (cmp == -1) {
		cur->right = insert(cur->right, data, tree);
	} else {
		// value is already in tree, need to decide either to not insert
		// and let user know or replace the old value
		assert(0);
	}

	return split(skew(cur));
}

int insert_aa_tree(void *data, struct aa_tree *tree)
{
	assert(tree);

	tree->root = insert(tree->root, data, tree);

	return 0;
}

static unsigned int u_min(unsigned int a, unsigned int b)
{
	return a < b ? a : b;
}

static void update_level(struct aa_node *node)
{
	if (!node)
		return;

	const unsigned int left_level = node->left ? node->left->level : 0;
	const unsigned int right_level = node->right ? node->right->level : 0;

	const unsigned int ideal_level = u_min(left_level, right_level) + 1;

	if (node->level > ideal_level) {
		node->level = ideal_level;
		if (node->right && node->right->level > ideal_level) {
			node->right->level = ideal_level;
		}
	}
}

static struct aa_node *fixup_after_del(struct aa_node *node)
{
	if (!node)
		return node;

	update_level(node);
	node = skew(node);
	node->right = skew(node->right);

	if (node->right)
		node->right->right = skew(node->right->right);

	node = split(node);
	node->right = split(node->right);

	return node;
}

static struct aa_node *successor(struct aa_node *node)
{
	node = node->right;

	if (!node)
		return node;

	while(node->left) {
		node = node->left;
	}

	return node;
}

static struct aa_node *predecessor(struct aa_node *node)
{
	node = node->left;

	if (!node)
		return node;

	while(node->right) {
		node = node->right;
	}

	return node;
}

static struct aa_node *delete(struct aa_node *cur, void *data, struct aa_tree *tree)
{
	if (!cur) {
		// value not in tree, return error msg
		assert(0);
	}

	struct aa_node *r;
	const int cmp = tree->cmp_func(data, cur->data); 

	if (cmp == 1) {
		cur->left = delete(cur->left, data, tree);
	} else if (cmp == -1) {
		cur->right = delete(cur->right, data, tree);
	} else {
		if (!cur->right && !cur->left) {
			destroy_node(cur, tree);
			return NULL;
		} else if (!cur->left) {
			r = successor(cur);

			if (cur->data && tree->free_func)
				tree->free_func(cur->data);
			cur->data = r->data;

			cur->right = delete(r->data, cur->right, tree);
		} else {
			r = predecessor(cur);

			if (cur->data && tree->free_func)
				tree->free_func(cur->data);
			cur->data = r->data;

			cur->left = delete(r->data, cur->left, tree);
		}
	}

	return fixup_after_del(cur);
}

int delete_aa_tree(void *data, struct aa_tree *tree)
{
	assert(tree);

	tree->root = delete(tree->root, data, tree);

	return 0;
}

static void *search(struct aa_node *cur, void *key, struct aa_tree *tree)
{
	if (!cur)
		return cur;

	const int cmp = tree->cmp_func(tree, cur->data); 

	if (cmp == 1)
		return search(cur->left, key, tree);
	else if (cmp == -1)
		return search(cur->right, key, tree);
	else
		return cur->data;
}

void *search_aa_tree(void *key, struct aa_tree *tree)
{
	assert(tree);

	return search(tree->root, key, tree);
}
