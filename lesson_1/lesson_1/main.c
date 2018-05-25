//
//  main.c
//  lesson_1
//
//  Created by Isaac Noda on 5/25/18.
//  Copyright © 2018 Isaac Noda. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
  const char * fileLocation = argv[1];
  const char filePermission[2] = "r\0";
    
  // Try to open file
  FILE *fp = fopen(fileLocation, filePermission);
  if (fp == NULL) {
      printf("No file found for location %s and permission %s\n", fileLocation, filePermission);
      return 1;
  } else {
    printf("File %s found\n", fileLocation);

    // Read lines
    int size = 1000;
    char line[size];
    printf("%s\n", fgets(line, size, fp));
    while (fgets(line, size, fp) != NULL) {
      printf("%s\n", line);
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
