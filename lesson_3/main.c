#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "player.h"
#include "team.h"
#include "linked_list.h"

int main(int argc, const char * argv[]) {
  const char *file_location = argv[1];
  const char mode[2] = "r";

  // Try to open file
  FILE *fp = fopen(file_location, mode);
  if (fp == NULL) {
      printf("No file found for location %s and mode %s\n", file_location, mode);
      return 1;
  }

  // Read rows
  char row[1000];
  int row_count = 0;
  int player_count = 0;
  struct team **teams;
  struct linked_list *l;
  while (fgets(row, 1000, fp) != NULL) {
    row_count += 1;

    // Skip header
    if (row_count == 1) { continue; }

    // Load row into struct
    char *rp = row;
    struct player *p = malloc(sizeof(struct player));
    load_data_from_row(rp, p);
    player_count += 1;

    // TODO: Find or init team

    // TODO: Find or init players

    if (player_count == 1) {
      l = new_linked_list(p);
    } else {
      add_item(l, p);
    }
    printf("%d\n", length(l));
  }

  // Close file
  int status = fclose(fp);
  if (status != 0) {
    printf("Failed to close file\n");
    return 1;
  }

  // TODO: Free up memory

  return 0;
}
