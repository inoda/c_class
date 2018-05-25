//
//  csv.h
//  lesson_1
//
//  Created by Isaac Noda on 5/25/18.
//  Copyright © 2018 Isaac Noda. All rights reserved.
//

#ifndef csv_h
#define csv_h

struct csv {
  char file_location[1000];
  FILE *file;
};

int read_csv(struct csv c) {
  c.file = fopen(c.file_location, "r");
  if (c.file == NULL) {
    return 1;
  } else {
    return 0;
  }
};

#endif /* csv_h */
