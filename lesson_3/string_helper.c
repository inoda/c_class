#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char * trim_trailing_whitespace(char *str) {
  char *last_char = &str[strlen(str)-1];
  if (*last_char == ' ' || *last_char == '\t' || *last_char == '\n' || *last_char == '\v' || *last_char == '\f' || *last_char == '\r' || *last_char == 127) {
    *last_char = '\0';
  }
  return 0;
}
