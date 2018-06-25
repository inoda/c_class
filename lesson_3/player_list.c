#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "player.h"
#include "player_list.h"

int sort_by_abr_desc(struct linked_list *players) {
  struct linked_list_item *previous = NULL;
  struct linked_list_item *current = players->head;
  struct linked_list_item *next = NULL;
  struct player *current_p = NULL;
  struct player *next_p = NULL;

  // struct linked_list_item *ix = players->head;
  // struct player *sp = NULL;
  // printf("%s\n", "***************************");
  // while (ix != NULL) {
  //   sp = (struct player *)(ix->item_data);
  //   printf("%s\n", sp->name);
  //   ix = ix->next_item;
  // }
  // printf("%s\n", "***************************");

  int count = 0;
  while (current != NULL) {
    count++;
    current_p = (struct player *)(current->item_data);
    next = current->next_item;
    if (next != NULL) {
      next_p = (struct player *)(next->item_data);


      // struct linked_list_item *i2 = players->head;
      // struct player *tp = NULL;
      // printf("%s\n", "-------------- sorting iteration -------------");
      // while (i2 != NULL) {
      //   tp = (struct player *)(i2->item_data);
      //   printf("%s\n", tp->name);
      //   struct linked_list_item *tz = players->tail;
      //   struct player * wh = (struct player *)(tz->item_data);
      //   printf("TAIL: %s\n", wh->name);
      //   i2 = i2->next_item;
      // }
      // printf("%s\n", "-------------------------------");
      // printf("%s\n", "-------------- next/last -------------");
      // printf("%s\n", current_p->name);
      // printf("%s\n", next_p->name);
      // printf("%s\n", "-------------------------------");


      if (average_base_rating(current_p) < average_base_rating(next_p)) {
        if (players->head == current) {
          players->head = next;
        } else {
          previous->next_item = next;
        }

        if (players->tail == next) {
          players->tail = current;
        }

        current->next_item = next->next_item;
        next->next_item = current;
      }
    }

    previous = current;
    current = next;
  }

  return 0;
};
