#ifndef team_h
#define team_h

#include "linked_list.h"

struct team {
  char name[5];
  struct linked_list *players;
};

#endif /* team_h */
