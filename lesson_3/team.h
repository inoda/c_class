#ifndef team_h
#define team_h

#include "linked_list.h"

struct team {
  char name[50];
  struct linked_list *players;
};

#endif /* team_h */
