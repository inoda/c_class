#include <stdlib.h>
#include "linked_list.h"

struct linked_list new_linked_list(void *first_item_data) {
  struct linked_list list;
  struct linked_list_item first_item;
  first_item.next_item = NULL;
  first_item.item_data = first_item_data;
  list.head = &first_item;
  return list;
};


// struct linked_list * new_linked_list(void *first_item_data);
// int add_item(struct linked_list *linked_list, void *item_data);
