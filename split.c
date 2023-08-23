#include "main.h"
/* Function to split a line into arguments */
char **split_line(char *line)
{
  int bufsize = BUFSIZE; /* The buffer size, initialized to a constant value */
  int position = 0; /* The current position in the buffer */
  char **tokens = malloc(bufsize * sizeof(char*)); /* The array of tokens (arguments) */
  char *token; /* The current token */

  if (!tokens) { /* If the memory allocation fails */
	fprintf(stderr, "split_line: allocation error\n"); /* Print the error message */
	exit(EXIT_FAILURE); /* Exit with failure */
  }

  token = strtok(line, DELIM); /* Get the first token from the line */

  while (token != NULL) { /* While there are more tokens */
	tokens[position] = token; /* Store the token in the array */
	position++; /* Increment the position */

	if (position >= bufsize) { /* If the buffer is full */
	  bufsize += BUFSIZE; /* Increase the buffer size by a constant value */
	  tokens = realloc(tokens, bufsize * sizeof(char*)); /* Reallocate more memory for the array */

	  if (!tokens) { /* If the memory allocation fails */
		fprintf(stderr, "split_line: allocation error\n"); /* Print the error message */
		exit(EXIT_FAILURE); /* Exit with failure */
	  }
	}

	token = strtok(NULL, DELIM); /* Get the next token from the line */
  }

  tokens[position] = NULL; /* Terminate the array with a NULL pointer */

  return tokens; /* Return the array of tokens */
}