#include "player.h"

int effective_plate_appearances(struct player *pp) {
  return pp->at_bats + pp->base_on_balls;
};

float strikeout_percentage(struct player *pp) {
  return 100.0 * pp->strikeouts / effective_plate_appearances(pp);
};

float hit_out_percentage(struct player *pp) {
  return 100.0 * (pp->at_bats - (pp->hits + pp->strikeouts)) / effective_plate_appearances(pp);
};

float walk_percentage(struct player *pp) {
  return 100.0 * pp->base_on_balls / effective_plate_appearances(pp);
};

float single_percentage(struct player *pp) {
  return 100.0 * (pp->hits - (pp->doubles + pp->triples + pp->home_runs)) / effective_plate_appearances(pp);
};

float double_percentage(struct player *pp) {
  return 100.0 * pp->doubles / effective_plate_appearances(pp);
};

float triple_percentage(struct player *pp) {
  return 100.0 * pp->triples / effective_plate_appearances(pp);
};

float home_run_percentage(struct player *pp) {
  return 100.0 * pp->home_runs / effective_plate_appearances(pp);
};

float average_base_rating(struct player *pp) {
  return walk_percentage(pp) + single_percentage(pp) + (2 * double_percentage(pp)) + (3 * triple_percentage(pp)) + (4 * home_run_percentage(pp));
};
