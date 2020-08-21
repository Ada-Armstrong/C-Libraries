#include "heap.h"

struct heap {
	void **data;
	unsigned int len;
	unsigned int max_len;
	int (*cmp_func)(void *, void *);
	void (*free_func)(void *);
	void *(*cpy_func)(void *);
};


Heap create_heap(int (*cmp_func)(void *, void *), void (*free_func)(void *),
		void *(*cpy_func)(void *))
{
	assert(cmp_func);
	assert(free_func);

	Heap h = malloc(sizeof(*h));
	if (!h)
		return NULL;

	h->data = malloc(sizeof(*h->data));
	if (!h->data) {
		free(h);
		return NULL;
	}

	h->len = 0;
	h->max_len = 1;
	h->cmp_func = cmp_func;
	h->free_func = free_func;
	h->cpy_func = cpy_func;

	return h;
}

void destroy_heap(Heap h)
{
	assert(h);
	assert(h->data);

	for (unsigned int i = 0; i < h->len; ++i) {
		h->free_func(h->data[i]);
	}

	free(h->data);
	free(h);
}

Heap copy_heap(Heap h)
{
	assert(h);
	assert(h->data);

	Heap cpy = create_heap(h->cmp_func, h->free_func, h->cpy_func);
	if (!cpy)
		return NULL;

	cpy->max_len = h->max_len;
	void **tmp = realloc(cpy->data, sizeof(*(cpy->data)) * cpy->max_len);
	if (!tmp) {
		destroy_heap(cpy);
		return NULL;
	}

	cpy->data = tmp;

	for (unsigned int i = 0; i < h->len; ++i) {
		cpy->data[i] = h->cpy_func(h->data[i]);
		if (cpy->data[i] == NULL) {
			destroy_heap(cpy);
			return NULL;
		}
		cpy->len += 1;
	}

	return cpy;
}

static void swap(void **a, void **b)
{
	void *tmp = *a;
	*a = *b;
	*b = tmp;
}

int insert_heap(Heap h, void *item)
{
	assert(h);
	assert(h->data);
	assert(item);

	if (h->len >= h->max_len) {
		h->max_len *= 2;
		void **tmp = realloc(h->data, sizeof(*(h->data)) * h->max_len);
		if (!tmp) {
			h->max_len /= 2;
			return -1;
		}
		h->data = tmp;
	}

	unsigned int index = h->len;
	unsigned int p_index;

	h->data[index] = item;
	h->len += 1;

	while(index != 0) {
		p_index = index % 2 ? (index - 1) / 2 : (index - 2) / 2;
		if (h->cmp_func(h->data[index], h->data[p_index]) >= 0)
				break;
		swap(&(h->data[index]), &(h->data[p_index]));
		index = p_index;
	}

	return 0;	
}

void *extract_heap(Heap h)
{
	assert(h);
	assert(h->data);
	
	if (h->len == 0)
		return NULL;
	if (h->len == 1) {
		h->len -= 1;
		return h->data[0];
	}

	void *extract = h->data[0];
	h->data[0] = h->data[--(h->len)];

	unsigned int index = 0;
	unsigned int left;
	unsigned int right;
	unsigned int largest;

	while(1) {
		left = 2 * index + 1;
		right = 2 * index + 2;
		largest = index;

		if (left < h->len && h->cmp_func(h->data[left], h->data[largest]) == -1)
			largest = left;

		if (right < h->len && h->cmp_func(h->data[right], h->data[largest]) == -1)
			largest = right;

		if (largest != index) {
			swap(&(h->data[index]), &(h->data[largest]));
			index = largest;
		} else {
			break;
		}
	}

	return extract;
}
