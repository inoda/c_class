#include <stdlib.h>
#include <stdio.h>
#include "player.h"
#include "player_list.h"

int sort_by_abr_desc(struct linked_list *players) {
  struct linked_list_item *previous = NULL;
  struct linked_list_item *current = players->head;
  struct linked_list_item *next = NULL;
  struct player *current_p = NULL;
  struct player *next_p = NULL;

  while (current != NULL) {
    current_p = (struct player *)(current->item_data);
    next = current->next_item;

    if (next != NULL) {
      next_p = (struct player *)(next->item_data);
      if (average_base_rating(current_p) < average_base_rating(next_p)) {
        if (players->head == current) {
          players->head = next;
        }
        if (players->tail == current) {
          players->tail = next;
        }

        current->next_item = next->next_item;
        next->next_item = current;
        if (previous != NULL) {
          previous->next_item = next;
        }
      }
    }

    previous = current;
    current = next;
  }

  return 0;
};

// HEAD -> a -> x -> y -> z -> NULL
