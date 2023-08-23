#include "main.h"





/* Main function */
int main(void)
{
  char *line; /* The input line */
  char **args; /* The arguments parsed from the input line */
  int status; /* The status of the execution */

  do {
    printf("$ "); /* Print the prompt */
    line = read_line(); /* Read the input line */
    args = split_line(line); /* Split the input line into arguments */
    status = execute(args); /* Execute the arguments */

    free(line); /* Free the allocated memory for the input line */
    free(args); /* Free the allocated memory for the arguments */
  } while (status); /* Loop until the status is zero */

  return EXIT_SUCCESS;
}











