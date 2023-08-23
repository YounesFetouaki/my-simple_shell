#include "main.h"
/* The number of built-in commands */

char *built_in_str[] = {
  "exit",
  "env"
};
int (*built_in_func[]) (char **) = {
  &built_in_exit,
  &built_in_env
};
int num_built_ins() {
  return sizeof(built_in_str) / sizeof(char *);
}