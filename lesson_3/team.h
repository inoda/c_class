#ifndef team_h
#define team_h

#include "linked_list.h"

struct team {
  char name[5];
  struct linked_list *players;
  float average_abr;
};

int sort_players_by_abr_asc(struct team *);
float calculate_average_abr(struct team *);

#endif /* team_h */
