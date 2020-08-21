#include "dlinked_list.h"

struct dll_node {
	void *data;
	struct dll_node *next;
	struct dll_node *prev;
};

struct dlinked_list {
	struct dll_node *head;
	struct dll_node *tail;
	unsigned int size;
	void (*free_func)(void *);
	void *(*cpy_func)(void *);
};

DLL create_dll(void (*free_func)(void *), void *(*cpy_func)(void *))
{
	DLL l = malloc(sizeof(*l));
	if (!l)
		return NULL;

	l->head = NULL;
	l->tail = NULL;
	l->size = 0;
	l->free_func = free_func;
	l->cpy_func = cpy_func;

	return l;
}

static void destroy_node(struct dll_node *node, void (*free_func)(void *))
{
	if (!node)
		return;
	if (node->data)
		free_func(node->data);
	free(node);
}

void destroy_dll(DLL l)
{
	if (!l)
		return;

	struct dll_node *ptr;

	while (l->head) {
		ptr = l->head->next;
		destroy_node(l->head, l->free_func);
		l->head = ptr;
	}

	free(l);
}

static struct dll_node *create_dll_node(void *item)
{
	struct dll_node *node = malloc(sizeof(*node));
	if (!node)
		return NULL;

	node->data = item;
	node->next = NULL;
	node->prev = NULL;

	return node;
}

int insert_front_dll(void *item, DLL l)
{
	if (!l)
		return -1;

	struct dll_node *node = create_dll_node(item);
	if (!node)
		return 1;

	if (!l->head) {
		l->head = node;
		l->tail = node;
	} else {
		l->head->prev = node;
		node->next = l->head;
		l->head = node;
	}
	l->size += 1;

	return 0;
}

int insert_back_dll(void *item, DLL l)
{
	if (!l)
		return -1;

	struct dll_node *node = create_dll_node(item);
	if (!node)
		return 1;

	if (!l->head) {
		l->head = node;
		l->tail = node;
	} else {
		l->tail->next = node;
		node->prev = l->tail;
		l->tail = node;
	}
	l->size += 1;

	return 0;
}

/* linear search */
struct dll_node *find_node(void *item, DLL l, int (*cmp_func)(void *, void *))
{
	struct dll_node *curr = l->head;
	while(curr) {
		if (cmp_func(curr->data, item) == 0)
			return curr;
		curr = curr->next;
	}

	return NULL;
}

void *pop_front_dll(DLL l)
{
	if (!l || !l->head)
		return NULL;
	void *ret = l->head->data;
	l->head->data = NULL;

	struct dll_node *tmp = l->head;
	l->size -= 1;

	if (l->head == l->tail) {
		l->head = NULL;
		l->tail = NULL;
	} else {
		l->head = l->head->next;
		l->head->prev = NULL;
	}
	destroy_node(tmp, l->free_func);

	return ret;
}

void *pop_back_dll(DLL l)
{
	if (!l || !l->head)
		return NULL;
	void *ret = l->tail->data;
	l->tail->data = NULL;

	struct dll_node *tmp = l->tail;
	l->size -= 1;

	if (l->head == l->tail) {
		l->head = NULL;
		l->tail = NULL;
	} else {
		l->tail = l->tail->prev;
		l->tail->next = NULL;
	}
	destroy_node(tmp, l->free_func);

	return ret;
}

unsigned int size_dll(DLL l)
{
	return l->size;
}
