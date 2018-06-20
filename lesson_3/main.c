#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "player.h"
#include "team.h"
#include "linked_list.h"
#include "string_helper.h"

struct team * find_or_add_team_by_name(struct linked_list *teams, struct player *p, char * searched_name) {
  struct linked_list_item *i = teams->head;
  struct team *t = NULL;

  // Look for item in existing list
  while (i != NULL) {
    t = (struct team *)(i->item_data);
    if (strcmp(searched_name, t->name) == 0) {
      add_item(t->players, p);
      return t;
    }
    i = i->next_item;
  }

  // Add new item if not found by this point
  t = malloc(sizeof(struct team));
  t->players = new_linked_list(p);
  strncpy(t->name, searched_name, strlen(searched_name));
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
    char * team_name = p->team;
    trim_trailing_whitespace(team_name);
    if (teams == NULL) {
      t = malloc(sizeof(struct team));
      strncpy(t->name, team_name, strlen(team_name));
      t->players = new_linked_list(p);
      teams = new_linked_list(t);
    } else {
      t = find_or_add_team_by_name(teams, p, team_name);
    }

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
  struct linked_list_item *i = teams->head;
  struct team *x = NULL;
  while (i != NULL) {
    x = (struct team *)(i->item_data);
    printf("%s\n", x->name);

    struct linked_list_item *i2 = x->players->head;
    struct player *p = NULL;
    while (i2 != NULL) {
      p = (struct player *)(i2->item_data);
      printf("%s\n", p->name);
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
