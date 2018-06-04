#ifndef player_h
#define player_h

struct player {
  char name[500];
  char team[100];
  char positions[500];
  int base_on_balls;
  int at_bats;
  int strikeouts;
  int hits;
  int doubles;
  int triples;
  int home_runs;
};

int effective_plate_appearances(struct player);
float strikeout_percentage(struct player);
float hit_out_percentage(struct player);
float walk_percentage(struct player);
float single_percentage(struct player);
float double_percentage(struct player);
float triple_percentage(struct player);
float home_run_percentage(struct player);
float average_base_rating(struct player);

#endif /* player_h */
