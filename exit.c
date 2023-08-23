#include "main.h"
/* Function to exit from the shell */
int built_in_exit(char **args)
{
	(void)args;
  return 0; /* Return 0 to terminate the loop in main function */
}

/* Function to print the environment variables */
int built_in_env(char **args)
{
  int i;

  for (i = 0; environ[i] != NULL; i++) { /* Loop through the environ array */
	printf("%s\n", environ[i]); /* Print each environment variable with a new line */
  }
(void)args;.
  return 1; /* Return 1 to continue the loop in main function */
}