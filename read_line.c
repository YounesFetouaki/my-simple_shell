#include "main.h"
/* Function to read a line from stdin */
char *read_line(void)
{
  char *line = NULL; /* The input line */
  size_t bufsize = 0; /* The buffer size, initialized to zero */
  ssize_t nread; /* The number of characters read */

  nread = getline(&line, &bufsize, stdin); /* Read a line from stdin */

  if (nread == -1) { /* If there is an error or EOF */
    if (feof(stdin)) { /* If it is EOF */
      printf("\n"); /* Print a new line */
      exit(EXIT_SUCCESS); /* Exit with success */
    }
    else { /* If it is an error */
      perror("read_line"); /* Print the error message */
      exit(EXIT_FAILURE); /* Exit with failure */
    }
  }

  return line; /* Return the input line */
}