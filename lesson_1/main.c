//
//  main.c
//  lesson_1
//
//  Created by Isaac Noda on 5/25/18.
//  Copyright © 2018 Isaac Noda. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "player.h"
#include "player.c"

int main(int argc, const char * argv[]) {
  const char * file_location = argv[1];
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
  while (fgets(row, 1000, fp) != NULL) {
    row_count += 1;

    // Skip header
    if (row_count == 1) { continue; }

    // Split row into columns
    char *col;
    char *rp = row;
    char cols[29][1000];
    int cols_index = 0;
    while((col = strsep(&rp, ",")) != NULL) {
      strcpy(cols[cols_index], col);
      cols_index += 1;
    }

    // Normalize name
    char *last_char = &cols[0][(strlen(cols[0])-1)];
    if (strcmp(last_char, "*") == 0 || strcmp(last_char, "#") == 0) {
      *last_char = '\0';
    }

    // Load data into struct
    struct player p;
    strcpy(p.name, cols[0]);
    p.at_bats = atoi(cols[6]);
    p.base_on_balls = atoi(cols[15]);
    p.strikeouts = atoi(cols[16]);

    // Print stats
    printf("%s, %d, %.1f%%\n", p.name, epa(p), strikeout_percentage(p));
  }

  // Close file
  int status = fclose(fp);
  if (status != 0) {
    printf("Failed to close file\n");
    return 1;
  }

  return 0;
}
