#include <stdlib.h>
#include <string.h>
#include "player.h"

int load_data_from_row(char *row, struct player *p) {
  char *col;
  int cols_index = 0;
  while((col = strsep(&row, ",")) != NULL) {
    switch(cols_index) {
      case 0: {
        // Normalize name
        char *last_char = &col[strlen(col)-1];
        if (*last_char == '*' || *last_char == '#') {
          *last_char = '\0';
        }
        strncpy(p->name, col, strlen(col));
        break;
      }
      case 2:
        strncpy(p->team, col, strlen(col));
        break;
      case 6:
        p->at_bats = atoi(col);
        break;
      case 8:
        p->hits = atoi(col);
        break;
      case 9:
        p->doubles = atoi(col);
        break;
      case 10:
        p->triples = atoi(col);
        break;
      case 11:
        p->home_runs = atoi(col);
        break;
      case 15:
        p->base_on_balls = atoi(col);
        break;
      case 16:
        p->strikeouts = atoi(col);
        break;
      case 28: {
        // Normalize position
        char *last_char = &col[strlen(col)-1];
        if (*last_char == '\n') {
          *last_char = '\0';
        }
        strncpy(p->positions, col, strlen(col));
        break;
      }
    }

    cols_index += 1;
  }

  return 0;
};

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
