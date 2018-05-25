//
//  player.h
//  lesson_1
//
//  Created by Isaac Noda on 5/25/18.
//  Copyright © 2018 Isaac Noda. All rights reserved.
//

#ifndef player_h
#define player_h

struct player {
  char name[100];
  int base_on_balls;
  int at_bats;
  int strikeouts;
};

int epa(struct player p) {
  return p.at_bats + p.base_on_balls;
};

float strikeout_percentage(struct player p) {
  return 100.0 * p.strikeouts / epa(p);
};

#endif /* player_h */
