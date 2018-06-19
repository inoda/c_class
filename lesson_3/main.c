#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "player.h"
#include "linked_list.h"

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
        break;
      }
      case 2:
        strcpy(p->team, col);
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
        strcpy(p->positions, col);
        break;
      }
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

  // Read rows
  char row[1000];
  int row_count = 0;
  int player_count = 0;
  struct linked_list *l;
  while (fgets(row, 1000, fp) != NULL) {
    row_count += 1;

    // Skip header
    if (row_count == 1) { continue; }

    // Load row into struct
    char *rp = row;
    struct player *p = malloc(sizeof(struct player));
    load_player_data(rp, p);
    player_count += 1;

    // struct linked_list_item *li = l.head;
    // struct player *from_list = (struct player *)(li->item_data);
    // printf("%s\n", from_list->name);

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
