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

  // Init array of player pointers
  const int player_pointer_size = sizeof(struct player *);
  struct player **players = malloc(10 * player_pointer_size);

  // Read rows
  char row[1000];
  int row_count = 0;
  while (fgets(row, 1000, fp) != NULL) {
    row_count += 1;

    // Skip header
    if (row_count == 1) { continue; }

    // Reallocate bigger array size every 10 players after the first 10
    if (row_count % 10 == 1 && row_count > 10) {
      players = realloc(players, sizeof(players) + (10 * player_pointer_size));
    }

    // Load row into struct
    char *rp = row;
    struct player *p = malloc(sizeof(struct player));
    load_player_data(rp, p);
    players[row_count - 2] = p; // - 2 from row_count as the first player starts on row 2 (row 1 is the CSV header)

    // free(p);
  }

  int a;
  int player_count = row_count - 1;
  for(a = 0; a < player_count; a += 1) {
     printf("%s\n", players[a]->name);
  }


  // Close file
  int status = fclose(fp);
  if (status != 0) {
    printf("Failed to close file\n");
    return 1;
  }

  return 0;
}
