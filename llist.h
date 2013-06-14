#ifndef LLIST_H
#define LLIST_H

typedef struct llist_t llist_t;

typedef struct node_s
{
	struct node_s *next;
}node_t;

struct llist_t
{
	int size;
	int elem_size;
	node_t *front;
	node_t *back;
};

#define NODE_DATA(node_in) ((void*) ((node_t*)(node_in) + 1))

#define llist(type) (llist_new(sizeof(type)))

llist_t *llist_new(int elem_size);
void  llist_free(llist_t *l);

void   llist_front(llist_t *l, void *elem);
void   llist_back(llist_t *l, void *elem);

void   llist_push_front(llist_t *l,void *elem);
void   llist_push_back(llist_t *l,void *elem);

int   llist_pop_front(llist_t *l,void *elem);
int   llist_pop_back(llist_t *l,void *elem);

void  llist_get(llist_t *l,int index,void *elem);
void  llist_set(llist_t *l,int index,void *elem);

void  llist_insert(llist_t *l, int index, void *elem);

void  llist_reset(llist_t *l);
int   llist_size(llist_t *l);
void *llist_data(llist_t *l);

void llist_print(llist_t *l, void(*print_fun)(void*));

#endif
