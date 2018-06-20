#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "player.h"
#include "team.h"
#include "linked_list.h"
#include "string_helper.h"
#include "player_list.h"

struct team * find_or_add_team_by_name(struct linked_list **teams_p, struct player *p) {
  char * team_name = p->team;
  trim_trailing_whitespace(team_name);
  struct linked_list *teams = *teams_p;
  struct team *t = NULL;

  // Create team list and add first team if NULL
  if (teams == NULL) {
    t = malloc(sizeof(struct team));
    strncpy(t->name, team_name, strlen(team_name));
    t->players = new_linked_list(p);
    *teams_p = new_linked_list(t);
  }

  if (teams != NULL) {
    // Look for team in existing list and add player
    int found = 0;
    struct linked_list_item *i = teams->head;
    while (i != NULL && found != 1) {
      t = (struct team *)(i->item_data);
      if (strcmp(team_name, t->name) == 0) {
        add_item(t->players, p);
        found = 1;
      }
      i = i->next_item;
    }

    // Init and add new team if not found by this point
    if (found != 1) {
      t = malloc(sizeof(struct team));
      t->players = new_linked_list(p);
      strncpy(t->name, team_name, strlen(team_name));
      add_item(teams, t);
    }
  }

  sort_by_abr_desc(t->players);
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
    find_or_add_team_by_name(&teams, p);
  }
  printf("%d\n", length(teams));
  struct linked_list_item *i = teams->head;
  struct team *x = NULL;
  while (i != NULL) {
    x = (struct team *)(i->item_data);
    printf("%s\n", x->name);

    struct linked_list_item *i2 = x->players->head;
    struct player *p = NULL;
    while (i2 != NULL) {
      p = (struct player *)(i2->item_data);
      printf("%s, %f\n", p->name, average_base_rating(p));
      i2 = i2->next_item;
    }

    i = i->next_item;
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
