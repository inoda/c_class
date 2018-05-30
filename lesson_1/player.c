int epa(struct player p) {
  return p.at_bats + p.base_on_balls;
};

float strikeout_percentage(struct player p) {
  return 100.0 * p.strikeouts / epa(p);
};
