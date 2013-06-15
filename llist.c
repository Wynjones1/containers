#include <containers/llist.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

static node_t *get_node(llist_t *l, int index)
{
	node_t *out = l->front;

	for(int i = 0; i < index; i++)
	{
		out = out->next;
	}

	return out;
}

static node_t *node_new(void *elem, int size)
{
	node_t *out = malloc(sizeof(node_t) + size);
	out->next = NULL;
	memcpy(NODE_DATA(out), elem, size);
	return out;
}

static void node_delete(node_t *node)
{
	free(node);
}

llist_t *llist_new(int elem_size)
{
	llist_t *out = malloc(sizeof(llist_t));
	out->elem_size = elem_size;
	out->front = NULL;
	out->back  = NULL;
	out->size = 0;
	return out;
}

void  llist_free(llist_t *l)
{}

void   llist_front(llist_t *l, void *elem)
{
	memcpy(elem, NODE_DATA(l->front), l->elem_size);	
}
void   llist_back(llist_t *l, void *elem)
{
	memcpy(elem, NODE_DATA(l->back), l->elem_size);	
}

void   llist_push_front(llist_t *l,void *elem)
{
	node_t *temp = node_new(elem, l->elem_size);
	temp->next = l->front;
	l->front = temp;
	if(l->size == 0)
	{
		l->back = l->front;
	}
	l->size++;
}
void   llist_push_back(llist_t *l,void *elem)
{
	node_t *temp = node_new(elem, l->elem_size);
	if(l->back == NULL)
	{
		l->front = temp;
		l->back  = temp;
	}
	else
	{
		l->back->next = temp;
		l->back = temp;
	}
	l->size++;
}

int llist_pop_front(llist_t *l,void *elem)
{
	if(l->size == 0)
	{
		return 0;
	}
	if(elem != NULL)
	{
		memcpy(elem, NODE_DATA(l->front), l->elem_size);
	}
	node_t *temp = l->front->next;
	node_delete(l->front);
	l->front = temp;
	l->size--;
	return 1;
}

int llist_pop_back(llist_t *l,void *elem)
{
	if(l->size == 0)
	{
		return 0;
	}
	node_t *to_pop = NULL;
	if(l->size == 1)
	{
		to_pop = l->front;	
		l->front = NULL;
		l->back  = NULL;
	}
	else
	{
		node_t *before = get_node(l, l->size - 2);
		to_pop = before->next;
		before->next = NULL;
		l->back = before;
	}
	if(elem != NULL)
	{
		memcpy(elem, NODE_DATA(to_pop), l->elem_size);	
	}
	l->size--;
	return 1;
}

void llist_get(llist_t *l,int index,void *elem)
{
	node_t *temp = get_node(l, index);
	memcpy(elem, NODE_DATA(temp), l->elem_size);
}

void llist_set(llist_t *l,int index,void *elem)
{
	node_t *temp = get_node(l, index);
	memcpy(NODE_DATA(temp), elem, l->elem_size);
}


void llist_insert(llist_t *l, int index, void *elem)
{
	if(index < 0 || index >= l->size)
	{
		fprintf(stderr,
			"llist: index out of bounds %s:%d\n",
			__FILE__,
			__LINE__);
		abort();
	}
	node_t *new = node_new(elem, l->elem_size);
	//find the element before the new one.
	if(index == 0)
	{
		new->next = l->front;	
		l->front = new;
	}
	else
	{
		node_t *before = get_node(l, index - 1);
		new->next = before->next;
		before->next = new;
	}
	l->size++;
}

void llist_reset(llist_t *l)
{}

int llist_size(llist_t *l)
{
	return l->size;
}

//void *llist_data(llist_t *l);

void llist_print(llist_t *l, void(*print_fun)(void*))
{
	node_t *temp = l->front;
	while(temp != NULL)
	{
		print_fun(NODE_DATA(temp));
		temp = temp->next;
	}
}
