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

int main(int argc, const char * argv[]) {
  const char * file_location = argv[1];
  const char file_permission[2] = "r\0";
    
  // Try to open file
  FILE *fp = fopen(file_location, file_permission);
  if (fp == NULL) {
      printf("No file found for location %s and permission %s\n", file_location, file_permission);
      return 1;
  } else {
    printf("File %s found\n", file_location);

    // Read lines
    int size = 1000;
    char row[size];
    const char delimiter[2] = ",\0";
    const char *headerIndicator = "Name";

    while (fgets(row, size, fp) != NULL) {
      char *col;
      char *rp = row;
      char cols[29][1000];

      // Split row into columns
      int index = 0;
      while((col = strsep(&rp, delimiter)) != NULL) {
        strcpy(cols[index], col);
        index += 1;
      }
      
      // Skip header
      int isHeader = 0;
      if (strcmp(cols[0], headerIndicator) == 0) {
        isHeader = 1;
      }
      if (isHeader == 1) {
        continue;
      }
      
      // Normalize name
      char *lastChar = &cols[0][(strlen(cols[0])-1)];
      if (strcmp(lastChar, "*") == 0 || strcmp(lastChar, "#") == 0) {
        *lastChar = '\0';
      }

      // Load data into struct
      struct player p;
      strcpy(p.name, cols[0]);
      p.at_bats = atoi(cols[6]);
      p.base_on_balls = atoi(cols[15]);
      p.strikeouts = atoi(cols[16]);
      printf("%s, %d, %.1f%%\n", p.name, epa(p), strikeout_percentage(p));
      printf("\n");
    }
  
    // Close file
    int status = fclose(fp);
    if (status != 0) {
      printf("Failed to close file\n");
      return 1;
    }
  }

  return 0;
}
