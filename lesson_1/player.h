#ifndef player_h
#define player_h

struct player {
  char name[100];
  int base_on_balls;
  int at_bats;
  int strikeouts;
};

int epa(struct player);
float strikeout_percentage(struct player);


#endif /* player_h */
