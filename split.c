#include "main.h"

/**
 * split_line - Function to split a line into arguments
 * @line: The line to split
 *
 * Return: The array of tokens (arguments)
 */
char **split_line(char *line)
{
	int bufsize = BUFSIZE; /* The buffer size, initialized to a constant value */
	int position = 0; /* The current position in the buffer */
	/* The array of tokens (arguments) */
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token; /* The current token */

	if (!tokens) /* If the memory allocation fails */
	{
		/* Print the error message */
		fprintf(stderr, "split_line: allocation error\n");
		exit(EXIT_FAILURE); /* Exit with failure */
	}

	token = strtok(line, DELIM); /* Get the first token from the line */

	while (token != NULL) /* While there are more tokens */
	{
		tokens[position] = token; /* Store the token in the array */
		position++; /* Increment the position */

		if (position >= bufsize) /* If the buffer is full */
		{
			bufsize += BUFSIZE; /* Increase the buffer size by a constant value */
			/* Reallocate more memory for the array */
			tokens = realloc(tokens, bufsize * sizeof(char *));

			if (!tokens) /* If the memory allocation fails */
			{
				/* Print the error message */
				fprintf(stderr, "split_line: allocation error\n");
				exit(EXIT_FAILURE); /* Exit with failure */
			}
		}

		token = strtok(NULL, DELIM); /* Get the next token from the line */
	}

	tokens[position] = NULL; /* Terminate the array with a NULL pointer */

	return (tokens); /* Return the array of tokens */
}
