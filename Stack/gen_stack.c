#include "gen_stack.h"

struct stack {
	void **data;
	unsigned int len;
	unsigned int max;
	void (*free_func)(void *);
	void *(*cpy_func)(void *);
};


Stack create_stack(void (*free_func)(void *), void *(*cpy_func)(void *))
{
	assert(free_func);
	assert(cpy_func);
	Stack s = malloc(sizeof(struct stack));
	if (!s)
		return NULL;

	s->data = malloc(sizeof(void *));
	if (!s->data) {
		free(s);
		return NULL;
	}
	s->len = 0;
	s->max = 1;
	s->free_func = free_func;
	s->cpy_func = cpy_func;
	return s;
}

void destroy_stack(Stack s)
{
	assert(s);
	if (s->data && s->free_func != NULL) {
		for (int i = 0; i < s->len; ++i) {
			s->free_func(s->data[i]);
		}
		free(s->data);
	} else if (s->data) {
		free(s->data);
	}
	free(s);
}

Stack copy_stack(Stack s)
{
	assert(s);
	void *tmp = NULL;
	Stack cpy = malloc(sizeof(struct stack));
	if (cpy == NULL || !s->cpy_func) {
		return NULL;
	}
	cpy->data = NULL;
	cpy->len = s->len;
	cpy->max = s->max;
	cpy->free_func = s->free_func;
	cpy->cpy_func = s->cpy_func;
	if (!s->data) {
		return cpy;
	}
	cpy->data = malloc(cpy->max * sizeof(void *));
	if (cpy->data == NULL) {
		destroy_stack(cpy);
		return NULL;
	}
	for (int i = 0; i < s->len; ++i) {
		tmp = cpy->cpy_func(s->data[i]); 
		if (!tmp) {
			/* clean up if cpy_func returns NULL */
			for (int j = i - 1; j >= 0; --j) {
				cpy->free_func(cpy->data[j]);
			}
			free(cpy);
			return NULL;
		}
		cpy->data[i] = tmp;
	}
	return cpy;
}

int push_stack(void *item, Stack s)
{
	assert(s);
	assert(item);
	void **tmp = NULL;
	if (s->len == s->max) {
		s->max *= 2;
		tmp = realloc(s->data, s->max * sizeof(void *));
		if (!tmp) {
			s->max /= 2;
			return 1;
		}
		s->data = tmp;
	}
	s->data[s->len] = item;
	s->len += 1;
	return 0;
}

void *top_stack(Stack s)
{
	assert(s);
	if (s->len == 0)
		return NULL;
	void *item_cpy = NULL;
	item_cpy = s->cpy_func(s->data[s->len - 1]);
	if (!item_cpy)
		return NULL;
	return s->data[s->len - 1];
}

void *pop_stack(Stack s)
{
	assert(s);
	if (s->len == 0)
		return NULL;
	void **tmp = NULL;
	if (s->len < s->max / 2) {
		s->max /= 2;
		tmp = realloc(s->data, s->max * sizeof(void *));
		if (!tmp)
			return NULL;
	}
	s->len -= 1;
	return s->data[s->len];
}

unsigned int get_size_stack(Stack s)
{
	assert(s);
	return s->len;
} 

