#include <stdlib.h>
#include "linked_list.h"

struct linked_list * new_linked_list(void *first_item_data) {
  struct linked_list *list = malloc(sizeof(struct linked_list));
  struct linked_list_item *first_item = malloc(sizeof(struct linked_list_item));
  first_item->next_item = NULL;
  first_item->item_data = first_item_data;
  list->head = first_item;
  list->tail = first_item;
  return list;
};

int length(struct linked_list *lp) {
  int count = 0;
  struct linked_list_item *i = lp->head;
  while (i != NULL) {
    count++;
    i = i->next_item;
  }
  return count;
};

int add_item(struct linked_list *list, void *item_data) {
  struct linked_list_item *last = list->tail;
  struct linked_list_item *next = malloc(sizeof(struct linked_list_item));
  next->next_item = NULL;
  next->item_data = item_data;
  last->next_item = next;
  list->tail = next;
  return 0;
};

// struct linked_list_item item next_item(struct linked_list *linked_list, struct linked_list_item *current_item);
