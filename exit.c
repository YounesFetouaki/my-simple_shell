#include "main.h"

/**
 * built_in_exit - Function to exit from the shell
 * @args: The arguments parsed from the input line
 *
 * Return: 0 to terminate the loop in main function
 */
int built_in_exit(char **args)
{
	(void)args;
	return (0); /* Return 0 to terminate the loop in main function */
}

/**
 * built_in_env - Function to print the environment variables
 * @args: The arguments parsed from the input line
 *
 * Return: 1 to continue the loop in main function
 */
int built_in_env(char **args)
{
	int i;

	for (i = 0; environ[i] != NULL; i++) /* Loop through the environ array */
	{/* Print each environment variable with a new line */
		printf("%s\n", environ[i]);
	}
	(void)args;
	return (1); /* Return 1 to continue the loop in main function */
}
