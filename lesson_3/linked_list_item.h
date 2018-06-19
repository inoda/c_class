#ifndef linked_list_item_h
#define linked_list_item_h

struct linked_list_item {
  void *item_data;
  struct linked_list_item *next_item;
};

#endif /* linked_list_item_h */
