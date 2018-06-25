#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "player.h"
#include "linked_list.h"
#include "team.h"
#include "string_helper.h"

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

  sort_players_by_abr_asc(t);
  if (length(t->players) == 10) { // Only keep top 9
    remove_front(t->players);
  }
  return t;
};

int main(int argc, const char * argv[]) {
  // Try to open file
  FILE *fp = fopen(argv[1], "r");
  if (fp == NULL) {
      printf("No file found for location %s and mode %s\n", argv[1], "r");
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

    // Load row into player struct
    char *rp = row;
    struct player *p = malloc(sizeof(struct player));
    load_data_from_row(rp, p);
    player_count += 1;

    // Find/init team in teams list
    find_or_add_team_by_name(&teams, p);
  }

  // Close file
  int status = fclose(fp);
  if (status != 0) {
    printf("Failed to close file\n");
    return 1;
  }

  // Calculate average ABR for each team
  struct linked_list_item *i = teams->head;
  struct team *t = NULL;
  while (i != NULL) {
    t = (struct team *)(i->item_data);
    calculate_average_abr(t);
    i = i->next_item;
  }

  // Sort teams then print team name and average ABR
  sort_teams_by_avg_abr_asc(teams);
  i = teams->head;
  t = NULL;
  while (i != NULL) {
    t = (struct team *)(i->item_data);
    printf("%s: %f\n", t->name, t->average_abr);
    i = i->next_item;
  }

  // Free memory
  wipe(teams);

  return 0;
}
