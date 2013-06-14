#ifndef LIST_H
#define LIST_H

typedef struct list_t list_t;

#define list(type) (list_new(sizeof(type)))
list_t *list_new(int elem_size);
void  list_free(list_t *l);

void   list_front(list_t *l, void *elem);
void   list_back(list_t *l, void *elem);

void   list_push_front(list_t *l,void *elem);
void   list_push_back(list_t *l,void *elem);

int   list_pop_front(list_t *l,void *elem);
int   list_pop_back(list_t *l,void *elem);

int   list_get(list_t *l,int index,void *elem);
int   list_set(list_t *l,int index,void *elem);

void  list_insert(list_t *l, int index, void *elem);

void  list_reset(list_t *l);
int   list_size(list_t *l);
void *list_data(list_t *l);

void list_print(list_t *l, void(*print_fun)(void*));

#endif
