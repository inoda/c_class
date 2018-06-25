#ifndef linked_list_h
#define linked_list_h

#include "linked_list_item.h"

struct linked_list {
  struct linked_list_item *head;
  struct linked_list_item *tail;
};

struct linked_list * new_linked_list(void *first_item_data);
int add_item(struct linked_list *, void *item_data);
int length(struct linked_list *);
int remove_front(struct linked_list *);

#endif /* linked_list_h */
