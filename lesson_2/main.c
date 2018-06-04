#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "player.h"

int load_player_data(char *row, struct player *p) {
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
        strcpy(p->name, col);
      }
      case 2:
        strcpy(p->team, col);
      case 6:
        p->at_bats = atoi(col);
      case 8:
        p->hits = atoi(col);
      case 9:
        p->doubles = atoi(col);
      case 10:
        p->triples = atoi(col);
      case 11:
        p->home_runs = atoi(col);
      case 15:
        p->base_on_balls = atoi(col);
      case 16:
        p->strikeouts = atoi(col);
      case 28:
        strcpy(p->positions, col);
    }

    cols_index += 1;
  }

  return 0;
}

int main(int argc, const char * argv[]) {
  const char *file_location = argv[1];
  const char mode[2] = "r";

  // Try to open file
  FILE *fp = fopen(file_location, mode);
  if (fp == NULL) {
      printf("No file found for location %s and mode %s\n", file_location, mode);
      return 1;
  }

  // Init data
  // struct player **players = NULL;

  // Read rows
  char row[1000];
  int row_count = 0;
  while (fgets(row, 1000, fp) != NULL) {
    row_count += 1;

    // Skip header
    if (row_count == 1) { continue; }

    // Reallocate bigger array size every 10 players
    // if (row_count % 10 == 1) {
    //   *players = realloc(*players, sizeof(*players) + (10 * sizeof(struct player *)));
    // }

    // Load row into struct
    char *rp = row;
    struct player *p = malloc(sizeof(struct player));
    load_player_data(rp, p);

    // Print stats
    printf("%s, %s, %d, %d, %d, %d, %d, %d, %d, %s\n", p->name, p->team, p->at_bats, p->hits, p->doubles, p->triples, p->home_runs, p->base_on_balls, p->strikeouts, p->positions);

    free(p);
  }

  // Close file
  int status = fclose(fp);
  if (status != 0) {
    printf("Failed to close file\n");
    return 1;
  }

  return 0;
}
