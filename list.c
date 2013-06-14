#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
	int   capacity;
	int   size;
	int   elem_size;
	void *data;
}list_t;

void list_print(list_t *l, void(*print_fun)(void*))
{
	for(int i = 0;i < l->size; i++)
	{
		void *elem = l->data + l->elem_size * i;	
		print_fun(elem);
	}
}

void list_front(list_t *l, void *elem)
{
	if(l->size < 1)
	{
		fprintf(stderr, "list is empty %s:%d\n", __FILE__, __LINE__);
		abort();
	}
	memcpy(elem, l->data, l->elem_size);
}

void list_back(list_t *l, void *elem)
{
	if(l->size < 1)
	{
		fprintf(stderr, "list is empty %s:%d\n", __FILE__, __LINE__);
		abort();
	}
	memcpy(elem, l->data + l->elem_size * (l->size - 1), l->elem_size);
}

list_t *list_new(int elem_size)
{
	assert(elem_size > 0);
	list_t *l = malloc(sizeof(list_t));	
	l->size = 0;
	l->capacity = 1;
	l->data = malloc(elem_size);
	l->elem_size = elem_size;
	return l;
}

void list_free(list_t *l)
{
	assert(l != NULL);
	free(l->data);
	free(l);
}

void list_double_capacity(list_t *l)
{
	l->capacity *= 2;
	l->data = realloc(l->data,l->capacity * l->elem_size);
}

void  list_insert(list_t *l, int index, void *elem)
{
	if(index < 0 || index >= l->size)
	{
		fprintf(stderr, "index out of bounds %s:%d\n", __FILE__, __LINE__);
		abort();
	}

	if(l->capacity == l->size)
	{
		list_double_capacity(l);
	}
	memmove(l->data + l->elem_size * (index + 1), 
			l->data + l->elem_size * index, 
			l->elem_size * (l->size - index));

	memcpy(l->data + index * l->elem_size, elem, l->elem_size);
	l->size++;
}

void list_push_back(list_t *l,void *elem)
{
	assert(l != NULL && elem != NULL);
	if(l->capacity == l->size)
	{
		list_double_capacity(l);
	}
	memcpy(l->data + l->size * l->elem_size,elem,l->elem_size);
	l->size++;
}

void list_push_front(list_t *l, void *elem)
{
	if(l->capacity == l->size)
	{
		list_double_capacity(l);
	}
	memmove(l->data + l->elem_size, l->data, l->elem_size * l->size);
	memcpy(l->data, elem, l->elem_size);
	l->size++;
}

int list_pop_back(list_t *l,void *elem)
{
	if(l->size == 0)
	{
		return 0;
	}
	l->size--;
	if(elem != NULL)
	{
		memcpy(elem,l->data + (l->size * l->elem_size),l->elem_size);
	}
	return 1;
}

int list_pop_front(list_t *l, void *elem)
{
	if(elem != NULL)
	{
		memcpy(elem, l->data, l->elem_size);
	}

	if(l->size == 0)
	{
		return 0;
	}

	memmove(l->data, l->data + l->elem_size, (l->size - 1) * l->elem_size);
	l->size--;
	return 1;
}

int list_get(list_t *l,int index,void *elem)
{
	assert(l != NULL && elem != NULL);
	if(index < 0 || l->size <= index)
	{
		fprintf(stderr,"list index out of bounds\n");
		abort();
	}
	memcpy(elem,l->data + (index * l->elem_size),l->elem_size);
	return 1;
}

int list_set(list_t *l,int index,void *elem)
{
	assert(l != NULL && elem != NULL);
	if(index < 0 || l->size <= index)
	{
		fprintf(stderr,"list index out of bounds\n");
		abort();
	}
	memcpy(l->data + (index * l->elem_size),elem,l->elem_size);
	return 1;
}

void list_reset(list_t *l)
{
	l->size = 0;	
}

int list_size(list_t *l)
{
	return l->size;
}

void *list_data(list_t *l)
{
	return l->data;
}

