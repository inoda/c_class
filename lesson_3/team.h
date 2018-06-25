#ifndef team_h
#define team_h

#include "linked_list.h"

struct team {
  char name[5];
  struct linked_list *players;
  float average_abr;
};

int sort_players_by_abr_asc(struct team *);
int sort_teams_by_avg_abr_asc(struct linked_list *teams);
float calculate_average_abr(struct team *);
int wipe_teams(struct linked_list *teams);

#endif /* team_h */
