#ifndef linked_list_h
#define linked_list_h

#include "linked_list_item.h"

struct linked_list {
  struct linked_list_item *head;
};

struct linked_list new_linked_list(void *first_item_data);
int add_item(struct linked_list *linked_list, void *item_data);
int length(struct linked_list *linked_list);
struct linked_list_item next_item(struct linked_list *linked_list, struct linked_list_item *current_item);

#endif /* linked_list_h */
