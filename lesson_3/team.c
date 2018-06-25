#include <stdlib.h>
#include "team.h"
#include "player.h"

int sort_players_by_abr_asc(struct team *t) {
  struct linked_list *players = t->players;
  int sorted = 0;
  while (sorted != 1) {
    struct linked_list_item *previous = NULL;
    struct linked_list_item *current = players->head;
    struct linked_list_item *next = NULL;
    struct player *current_p = NULL;
    struct player *next_p = NULL;
    sorted = 1;

    while (current != NULL) {
      current_p = (struct player *)(current->item_data);
      next = current->next_item;
      if (next != NULL) {
        next_p = (struct player *)(next->item_data);

        if (average_base_rating(current_p) > average_base_rating(next_p)) {
          sorted = 0;
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
  }

  return 0;
};

int sort_teams_by_avg_abr_asc(struct linked_list *teams) {
  int sorted = 0;
  while (sorted != 1) {
    struct linked_list_item *previous = NULL;
    struct linked_list_item *current = teams->head;
    struct linked_list_item *next = NULL;
    struct team *current_t = NULL;
    struct team *next_t = NULL;
    sorted = 1;

    while (current != NULL) {
      current_t = (struct team *)(current->item_data);
      next = current->next_item;
      if (next != NULL) {
        next_t = (struct team *)(next->item_data);

        if (current_t->average_abr > next_t->average_abr) {
          sorted = 0;
          if (teams->head == current) {
            teams->head = next;
          } else {
            previous->next_item = next;
          }

          if (teams->tail == next) {
            teams->tail = current;
          }

          current->next_item = next->next_item;
          next->next_item = current;
        }
      }

      previous = current;
      current = next;
    }
  }

  return 0;
};

float calculate_average_abr(struct team *t) {
  struct linked_list_item *i = t->players->head;
  struct player *p = NULL;
  float sum_abr = 0;
  int num_players = length(t->players);
  while (i != NULL) {
    p = (struct player *)(i->item_data);
    sum_abr += average_base_rating(p);
    i = i->next_item;
  }

  t->average_abr = sum_abr / num_players;
  return t->average_abr;
}
