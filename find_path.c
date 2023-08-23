#include "main.h"

/**
 * find_path - Function to find the path of an executable
 * @command: The command to find the path of
 *
 * Return: (1) The full path of the executable, otherwise (2) NULL
 */
char *find_path(char *command)
{
	char *path = getenv("PATH");
	char *token = strtok(path, ":");
	struct stat st;

	/* Check if the provided command is an absolute path */
	if (command[0] == '/')
	{
		if (stat(command, &st) == 0 && st.st_mode & S_IXUSR)
			return (strdup(command));
		return (NULL); /* Return NULL if the absolute path is not executable */
	}

	if (path == NULL) /* If the PATH is not set */
		return (NULL); /* Return NULL */
	path = strdup(path); /* Duplicate the PATH value */
	if (path == NULL) /* If the memory allocation fails */
		return (NULL); /* Return NULL */
	/* While there are more tokens (directories) in the PATH */
	while (token != NULL)
	{/* Allocate memory for the buffer */
		char *buffer = malloc(strlen(token) + strlen(command) + 2);

		if (buffer == NULL) /* If the memory allocation fails */
		{
			free(path); /* Free the allocated memory for the PATH value */
			return (NULL); /* Return NULL */
		}
		strcpy(buffer, token); /* Copy the token (directory) to the buffer */
		strcat(buffer, "/"); /* Append a slash to the buffer */
		strcat(buffer, command); /* Append the command to the buffer */
		if (stat(buffer, &st) == 0 && st.st_mode & S_IXUSR)
		{
			free(path); /* Free the allocated memory for the PATH value */
			return (buffer); /* Return the buffer as the full path of the executable */
		}
		free(buffer); /* Free the allocated memory for the buffer */
		token = strtok(NULL, ":"); /* Get the next token (directory) in the PATH */
	}
	free(path); /* Free the allocated memory for the PATH value */
	return (NULL); /* Return NULL if no path is found */
}
