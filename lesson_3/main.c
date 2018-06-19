#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "player.h"
#include "team.h"
#include "linked_list.h"

struct team * find_or_add_team_by_name(struct linked_list *teams, char * name) {
  struct linked_list_item *i = teams->head;
  struct team *t = NULL;
  while (i != NULL) {
    t = (struct team *)(i->item_data);
    if (strcmp(name, t->name) == 1) {
      return t;
    }
    i = i->next_item;
  }
  printf("%s\n", "New one");
  t = malloc(sizeof(struct team));
  strncpy(t->name, name, strlen(name));
  add_item(teams, t);
  return t;
};

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
  struct linked_list *teams = NULL;
  while (fgets(row, 1000, fp) != NULL) {
    row_count += 1;

    // Skip header
    if (row_count == 1) { continue; }

    // Load row into struct
    char *rp = row;
    struct player *p = malloc(sizeof(struct player));
    load_data_from_row(rp, p);
    player_count += 1;

    // Find/init team in teams list
    struct team *t = NULL;
    if (teams == NULL) {
      t = malloc(sizeof(struct team));
      char * team_name = p->team;
      strncpy(t->name, team_name, strlen(team_name));
      teams = new_linked_list(t);
    } else {
      t = find_or_add_team_by_name(teams, p->team);
    }
    printf("%s\n", t->name);

    // TODO: Find or init players
    // if (player_count == 1) {
    //   l = new_linked_list(p);
    // } else {
    //   add_item(l, p);
    // }
    // struct player *sup = (struct player *)find(l, p);
    // printf("%s\n", sup->name);
  }
  printf("%d\n", length(teams));

  // Close file
  int status = fclose(fp);
  if (status != 0) {
    printf("Failed to close file\n");
    return 1;
  }

  // TODO: Free up memory

  return 0;
}
