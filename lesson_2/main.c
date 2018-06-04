#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "player.h"

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

    // Split row and load data into struct
    char *col;
    char *rp = row;
    int cols_index = 0;
    struct player p;
    while((col = strsep(&rp, ",")) != NULL) {
      switch(cols_index) {
        case 0: {
          // Normalize name
          char *last_char = &col[strlen(col)-1];
          if (*last_char == '*' || *last_char == '#') {
            *last_char = '\0';
          }
          strcpy(p.name, col);
        }
        case 6:
          p.at_bats = atoi(col);
        case 15:
          p.base_on_balls = atoi(col);
        case 16:
          p.strikeouts = atoi(col);
      }

      cols_index += 1;
    }

    // Print stats
    printf("%s, %d, %.1f%%\n", p.name, effective_plate_appearances(p), strikeout_percentage(p));
  }

  // Close file
  int status = fclose(fp);
  if (status != 0) {
    printf("Failed to close file\n");
    return 1;
  }

  return 0;
}
