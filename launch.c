#include "main.h"

/**
 * launch - Function to launch a program
 * @args: The arguments parsed from the input line
 *
 * Return: 1 to continue the loop in main function
 */
int launch(char **args)
{
	pid_t pid; /* The process ID */
	int status; /* The status of the execution */

	pid = fork(); /* Fork a child process */

	if (pid == 0) /* If it is the child process */
	{
		char *path; /* The path of the executable */

		path = find_path(args[0]); /* Find the path of the executable */

		if (path == NULL) /* If the path is not found */
		{
			/* Print the error message */
			fprintf(stderr, "%s: command not found\n", args[0]);
			exit(EXIT_FAILURE); /* Exit with failure */
		}
		/* Execute the program with the arguments and the environment */
		if (execve(path, args, environ) == -1)
		{
			perror("launch"); /* Print the error message */
			exit(EXIT_FAILURE); /* Exit with failure */
		}
	}
	else if (pid < 0) /* If the fork fails */
	{
		perror("launch"); /* Print the error message */
		exit(EXIT_FAILURE); /* Exit with failure */
	}
	else /* If it is the parent process */
	{
		do {
			/* Wait for the child process to change state */
			waitpid(pid, &status, WUNTRACED);
		/* Loop until the child process exits normally or by a signal */
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return (1); /* Return 1 to continue the loop in main function */
}
