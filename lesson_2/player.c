#include "player.h"

int effective_plate_appearances(struct player p) {
  return p.at_bats + p.base_on_balls;
};

float strikeout_percentage(struct player p) {
  return 100.0 * p.strikeouts / effective_plate_appearances(p);
};

float hit_out_percentage(struct player p) {
  return 100.0 * (p.at_bats - (p.hits + p.strikeouts)) / effective_plate_appearances(p);
};

float walk_percentage(struct player p) {
  return 100.0 * p.base_on_balls / effective_plate_appearances(p);
};

float single_percentage(struct player p) {
  return 100.0 * (p.hits - (p.doubles + p.triples + p.home_runs)) / effective_plate_appearances(p);
};

float double_percentage(struct player p) {
  return 100.0 * p.doubles / effective_plate_appearances(p);
};

float triple_percentage(struct player p) {
  return 100.0 * p.triples / effective_plate_appearances(p);
};

float home_run_percentage(struct player p) {
  return 100.0 * p.home_runs / effective_plate_appearances(p);
};

float average_base_rating(struct player p) {
  return walk_percentage(p) + single_percentage(p) + (2 * double_percentage(p)) + (3 * triple_percentage(p)) + (4 * home_run_percentage(p));
};
