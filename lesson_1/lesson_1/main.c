//
//  main.c
//  lesson_1
//
//  Created by Isaac Noda on 5/25/18.
//  Copyright © 2018 Isaac Noda. All rights reserved.
//

#include <stdio.h>
#include <string.h>
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

    while (fgets(row, size, fp) != NULL) {
      char *col;
      char *rp = &row[0];
      while((col = strsep(&rp, delimiter)) != NULL) {
        printf("%s\n", col);
      }
      
      printf("%s\n", row);
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
