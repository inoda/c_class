#include "player.h"

int effective_plate_appearances(struct player p) {
  return p.at_bats + p.base_on_balls;
};

float strikeout_percentage(struct player p) {
  return 100.0 * p.strikeouts / effective_plate_appearances(p);
};
