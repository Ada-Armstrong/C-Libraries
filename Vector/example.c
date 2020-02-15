#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "vector.h"

struct record {
	int id;
	char *name;
};

typedef struct record *Record;


Record create_record(int id, char *name);
void destroy_record(void *r);
void *copy_record(void *r);
void print_record(Record r);

char *Names[] = {"Chuck", "Foo", "Bar", "Bohr", NULL}; 

int main(void)
{
	Record r;
	Vector records = create_vector(destroy_record, copy_record);

	for (int i = 0; Names[i] != NULL; ++i) {
		r = create_record(i, Names[i]);
		append_vector(records, r);
	}

	Vector cpy = copy_vector(records);

	/* replace all even entries */
	for (unsigned int j = 0; j < size_vector(cpy); ++j) {
		if (j % 2 == 0) {
			r = create_record(1729, "Hardy");
			index_replace_vector(cpy, j, r);
		}
	}

	/* print vector */
	printf("Originals:\n");
	for (unsigned int k = 0; k < size_vector(records); ++k) {
		r = index_vector(records, k);
		print_record(r);
	}

	printf("\nCopy:\n");
	for (unsigned int m = 0; m < size_vector(cpy); ++m) {
		r = index_vector(cpy, m);
		print_record(r);
	}

	resize_vector(cpy, 1);

	printf("\nCopy Resized:\n");
	for (unsigned int m = 0; m < size_vector(cpy); ++m) {
		r = index_vector(cpy, m);
		print_record(r);
	}

	resize_vector(records, size_vector(records) + 3);

	printf("\nOriginal Resized:\n");
	for (unsigned int k = 0; k < size_vector(records); ++k) {
		r = index_vector(records, k);
		print_record(r);
	}

	destroy_vector(records);
	destroy_vector(cpy);
	
	return 0;
}

Record create_record(int id, char *name)
{
	Record r = malloc(sizeof(*r));
	if (!r)
		return NULL;

	r->name = malloc(sizeof(*(r->name)) * (strlen(name) + 1));
	if (!r->name) {
		free(r);
		return NULL;
	}

	strcpy(r->name, name);
	r->id = id;

	return r;
}

void destroy_record(void *r)
{
	if (!r)
		return;
	Record rec = (Record)r;

	free(rec->name);
	free(rec);
}

void *copy_record(void *r)
{
	Record rec = (Record)r;
	void *cpy = create_record(rec->id, rec->name);
	return cpy;
}

void print_record(Record r)
{
	if (!r) {
		printf("NULL record!\n");
	} else {
		printf("----------------\n");
		printf("id: %d\nname: %s\n", r->id, r->name);
		printf("----------------\n");
	}
}
